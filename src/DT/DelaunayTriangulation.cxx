/*
 * Filename:    DelaunayTriangulation.cxx
 *
 * Description: Source file of DelaunayTriangulation class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include <algorithm>
#include <random>
#include "DelaunayTriangulation.hxx"


DelaunayTriangulation::DelaunayTriangulation() : TrianglesDAG()
{

}

DelaunayTriangulation::~DelaunayTriangulation()
{
    for (auto& vertex : meshVertices) {
        delete vertex;
    }
    meshVertices.clear();
}

void DelaunayTriangulation::setInputPoints(std::vector<Point>& points)
{
    std::cout << std::endl << "Sort lexicographically, Remove possible duplicates, and Shuffle Points..." << std::endl;

    //  sort vertices lexicographically in descending order. Cost: O(n log n)
    std::sort(points.begin(), points.end(), std::greater<>());

    //  remove duplicate points. Cost: O(n)
    points.erase(std::unique(points.begin(), points.end()), points.end());

    //  compute a random permutation of the points
    //  Note: if this is not activated, the complexity of the algorithm becomes: O(n^2).
    //  Note: this step could be skipped if the input is already shuffled
    auto randomGenerator = std::default_random_engine(std::random_device{}());
    std::shuffle(points.begin(), points.end(), randomGenerator);

    meshVertices.clear();
    //  convert points to Vertices (a.k.a Point*): Cost O(n)
    for (const auto& point : points) {
        meshVertices.push_back(new Vertex(point));
    }
}

void DelaunayTriangulation::createBoundingTriangle()
{
    std::cout << std::endl << "Compute Bounding Triangle..." << std::endl;

    computeBoundaryTriangleTimer.startTimer();

    double minX = (*meshVertices[0])[0];
    double minY = (*meshVertices[0])[1];
    double maxX = minX;
    double maxY = minY;

    for (auto& vertex : meshVertices) {
        Vertex testedVertex = *vertex;
        if (testedVertex[0] < minX) {
            minX = testedVertex[0];
        }
        if (testedVertex[1] < minY) {
            minY = testedVertex[1];
        }
        if (testedVertex[0] > maxX) {
            maxX = testedVertex[0];
        }
        if (testedVertex[1] > maxY) {
            maxY = testedVertex[1];
        }
    }

    const double dx = maxX - minX;
    const double dy = maxY - minY;
    const double deltaMax = std::max(dx, dy);

    const double multiplier = 20;
    const double midX = (minX + maxX) / 2;
    const double midY = (minY + maxY) / 2;

    auto vertex0 = new Vertex({midX - multiplier * deltaMax, midY - deltaMax});
    vertex0->id = -3;
    auto vertex1 = new Vertex({midX, midY + multiplier * deltaMax});
    vertex1->id = -2;
    auto vertex2 = new Vertex({midX + multiplier * deltaMax, midY - deltaMax});
    vertex2->id = -1;

    auto edge0 = new Edge({vertex0->id, vertex1->id});
    auto edge1 = new Edge({vertex1->id, vertex2->id});
    auto edge2 = new Edge({vertex2->id, vertex0->id});

    computeBoundaryTriangleTimer.stopTimer();

    auto boundingTriangle = new Triangle({vertex0, vertex1, vertex2});
    boundingTriangle->setEdges({edge0, edge1, edge2});

    edge0->addAdjacentTriangle(TrianglePair(boundingTriangle, 0));
    edge1->addAdjacentTriangle(TrianglePair(boundingTriangle, 1));
    edge2->addAdjacentTriangle(TrianglePair(boundingTriangle, 2));

    //  initialize root triangle of DAG
    setRootTriangle(boundingTriangle);
}

void DelaunayTriangulation::legalizeEdge(EdgeHandle& PiPj, const VertexHandle& Pr)
{
    //  PiPj is not a boundary edge
    if (PiPj->getNumberOfAdjacentTriangles() != 1) {
        //  find adjacent triangles of edge PiPj
        TrianglePair PiPkPjPermutationTrianglePair, PiPjPrPermutationTrianglePair;
        if (PiPj->adjacentTrianglesWithEdgeIds[0].first->containsVertex(Pr)) {
            PiPjPrPermutationTrianglePair = PiPj->adjacentTrianglesWithEdgeIds[0];
            PiPkPjPermutationTrianglePair = PiPj->adjacentTrianglesWithEdgeIds[1];
        } else {
            PiPjPrPermutationTrianglePair = PiPj->adjacentTrianglesWithEdgeIds[1];
            PiPkPjPermutationTrianglePair = PiPj->adjacentTrianglesWithEdgeIds[0];
        }

        //  find Pk point
        VertexHandle Pk;
        if (PiPkPjPermutationTrianglePair.second == 0) {
            Pk = PiPkPjPermutationTrianglePair.first->vertices[2];
        } else if (PiPkPjPermutationTrianglePair.second == 1) {
            Pk = PiPkPjPermutationTrianglePair.first->vertices[0];
        } else {
            Pk = PiPkPjPermutationTrianglePair.first->vertices[1];
        }

        //  Check if PiPj is illegal
        if (predicates.inCircle(PiPjPrPermutationTrianglePair.first, Pk)) {
            ////////////////////////////////////////////////////////////////
            //                      Flip Edge Started                     //
            ////////////////////////////////////////////////////////////////

            //  Find vertices and edges in order to create the new triangles in the correct order
            VertexHandle Pi, Pj;
            EdgeHandle PrPi, PjPr;

            //  retrieve information from triangle PiPjPr
            if (PiPjPrPermutationTrianglePair.second == 0) {
                Pi = PiPjPrPermutationTrianglePair.first->vertices[0];
                Pj = PiPjPrPermutationTrianglePair.first->vertices[1];

                PrPi = PiPjPrPermutationTrianglePair.first->edges[2];
                PjPr = PiPjPrPermutationTrianglePair.first->edges[1];
            } else if (PiPjPrPermutationTrianglePair.second == 1) {
                Pi = PiPjPrPermutationTrianglePair.first->vertices[1];
                Pj = PiPjPrPermutationTrianglePair.first->vertices[2];

                PrPi = PiPjPrPermutationTrianglePair.first->edges[0];
                PjPr = PiPjPrPermutationTrianglePair.first->edges[2];
                std::cout << " I am here 1" << std::endl;
            } else {
                Pi = PiPjPrPermutationTrianglePair.first->vertices[2];
                Pj = PiPjPrPermutationTrianglePair.first->vertices[0];

                PrPi = PiPjPrPermutationTrianglePair.first->edges[1];
                PjPr = PiPjPrPermutationTrianglePair.first->edges[0];
                std::cout << " I am here 2" << std::endl;
            }

            EdgeHandle PiPk, PkPj;
            //  retrieve information from triangle PiPkPj
            if (PiPkPjPermutationTrianglePair.second == 0) {
                PiPk = PiPkPjPermutationTrianglePair.first->edges[1];
                PkPj = PiPkPjPermutationTrianglePair.first->edges[2];
            } else if (PiPkPjPermutationTrianglePair.second == 1) {
                PiPk = PiPkPjPermutationTrianglePair.first->edges[2];
                PkPj = PiPkPjPermutationTrianglePair.first->edges[0];
            } else {
                PiPk = PiPkPjPermutationTrianglePair.first->edges[0];
                PkPj = PiPkPjPermutationTrianglePair.first->edges[1];
            }

            //  remove the PiPj edge because we are gonna flip it
            delete PiPj;

            //  remove the PiPjPr triangle as an adjacent triangle of its edges (except PiPj)
            PrPi->removeAdjacentTriangle(PiPjPrPermutationTrianglePair.first);
            PjPr->removeAdjacentTriangle(PiPjPrPermutationTrianglePair.first);

            //  remove the PiPkPj triangle as an adjacent triangle of its edges (except PiPj)
            PkPj->removeAdjacentTriangle(PiPkPjPermutationTrianglePair.first);
            PiPk->removeAdjacentTriangle(PiPkPjPermutationTrianglePair.first);

            //  create the new triangles
            auto PiPkPr = new Triangle({Pi, Pk, Pr});
            auto PkPjPr = new Triangle({Pk, Pj, Pr});

            //  create the new edge for the new triangles and assign it its adjacent triangles
            auto PkPr = new Edge({Pk->id, Pr->id});
            PkPr->addAdjacentTriangle(TrianglePair(PiPkPr, 1));
            PkPr->addAdjacentTriangle(TrianglePair(PkPjPr, 2));

            //  assign adjacent triangles of the old edges
            PrPi->addAdjacentTriangle(TrianglePair(PiPkPr, 2));
            PiPk->addAdjacentTriangle(TrianglePair(PiPkPr, 0));

            PkPj->addAdjacentTriangle(TrianglePair(PkPjPr, 0));
            PjPr->addAdjacentTriangle(TrianglePair(PkPjPr, 1));

            //  set edges of new triangles
            PiPkPr->setEdges({PiPk, PkPr, PrPi});
            PkPjPr->setEdges({PkPj, PjPr, PkPr});

            // update the DAG
            PiPkPjPermutationTrianglePair.first->childrenTriangles.push_back(PiPkPr);
            PiPkPjPermutationTrianglePair.first->childrenTriangles.push_back(PkPjPr);

            PiPjPrPermutationTrianglePair.first->childrenTriangles.push_back(PiPkPr);
            PiPjPrPermutationTrianglePair.first->childrenTriangles.push_back(PkPjPr);

            ////////////////////////////////////////////////////////////////
            //                       Flip Edge Ended                      //
            ////////////////////////////////////////////////////////////////

            legalizeEdge(PiPk, Pr);
            legalizeEdge(PkPj, Pr);
        }
    }
}

void DelaunayTriangulation::generateMesh()
{
    createBoundingTriangle();

    std::cout << std::endl << "Compute Delaunay Triangulation..." << std::endl;

    meshingTimer.startTimer();

    int verticesCounter = 1;

    //  iterate over the meshVertices and insert them in the current triangulation. Cost: O(n)
    for (auto& Pr : meshVertices) {
        //  initialize vertex id
        Pr->id = verticesCounter++;

        //  locate a triangle that includes Pr. Cost: O(log n)

        //  This complexity is accurate because our points are shuffled uniformly,
        //  therefore the depth of the History DaG is almost uniformly distributed.
        //  Since the max number of triangles created by this algorithm is 9n + 1,
        //  and assuming almost uniformly distributed DAG, we can say that: log(9n + 1) = O (log n)
        std::array<double, 3> orientationTests{};
        auto PiPjPk = locateTriangle(Pr, orientationTests);

        //  check if the vertex Pr lies on one of the edges of the bad triangle
        int edgeId;
        if (orientationTests[0] == 0) { //  lies on first edge
            edgeId = 0;
        } else if (orientationTests[1] == 0) {  //  lies on second edge
            edgeId = 1;
        } else if (orientationTests[2] == 0) {  //  lies on third edge
            edgeId = 2;
        } else {    //  does not lie on any edge
            edgeId = -1;
        }

        //  if vertex Pr lies in the interior of the triangle
        if (edgeId == -1) {
            auto Pi = PiPjPk->vertices[0];
            auto Pj = PiPjPk->vertices[1];
            auto Pk = PiPjPk->vertices[2];

            auto PiPj = PiPjPk->edges[0];
            auto PjPk = PiPjPk->edges[1];
            auto PkPi = PiPjPk->edges[2];

            ////////////////////////////////////////////////////////////////
            //                    Split Triangle Started                  //
            ////////////////////////////////////////////////////////////////

            //  remove PiPjPk as an adjacent triangle of the edges of the triangle
            PiPj->removeAdjacentTriangle(PiPjPk);
            PjPk->removeAdjacentTriangle(PiPjPk);
            PkPi->removeAdjacentTriangle(PiPjPk);

            //  create the new triangles
            auto PiPjPr = new Triangle({Pi, Pj, Pr});
            auto PjPkPr = new Triangle({Pj, Pk, Pr});
            auto PkPiPr = new Triangle({Pk, Pi, Pr});

            //  create the new edges for the new triangles
            auto PiPr = new Edge({Pi->id, Pr->id});
            auto PjPr = new Edge({Pj->id, Pr->id});
            auto PkPr = new Edge({Pk->id, Pr->id});

            //  assign adjacent triangles of the PiPjPk Edges
            PiPj->addAdjacentTriangle(TrianglePair(PiPjPr, 0));
            PjPk->addAdjacentTriangle(TrianglePair(PjPkPr, 0));
            PkPi->addAdjacentTriangle(TrianglePair(PkPiPr, 0));

            //  assign adjacent triangles of the new edges
            PiPr->addAdjacentTriangle(TrianglePair(PkPiPr, 1));
            PiPr->addAdjacentTriangle(TrianglePair(PiPjPr, 2));

            PjPr->addAdjacentTriangle(TrianglePair(PiPjPr, 1));
            PjPr->addAdjacentTriangle(TrianglePair(PjPkPr, 2));

            PkPr->addAdjacentTriangle(TrianglePair(PjPkPr, 1));
            PkPr->addAdjacentTriangle(TrianglePair(PkPiPr, 2));

            //  set edges of new triangles
            PiPjPr->setEdges({PiPj, PjPr, PiPr});
            PjPkPr->setEdges({PjPk, PkPr, PjPr});
            PkPiPr->setEdges({PkPi, PiPr, PkPr});

            // update the DAG
            PiPjPk->childrenTriangles.push_back(PiPjPr);
            PiPjPk->childrenTriangles.push_back(PjPkPr);
            PiPjPk->childrenTriangles.push_back(PkPiPr);

            ////////////////////////////////////////////////////////////////
            //                    Split Triangle ended                    //
            ////////////////////////////////////////////////////////////////

            //  legalize the edges of the old triangle
            legalizeEdge(PiPj, Pr);
            legalizeEdge(PjPk, Pr);
            legalizeEdge(PkPi, Pr);
        } else {
            //  retrieve information from triangle PiPjPk
            std::cout << "Same edge test, badEdge = " << edgeId << std::endl;
            VertexHandle Pi;
            VertexHandle Pj;
            VertexHandle Pk;

            EdgeHandle PiPj;
            EdgeHandle PjPk;
            EdgeHandle PkPi;

            //  define the above variables to treat each edge the same way
            if (edgeId == 0) {  //  lies on first edge
                Pi = PiPjPk->vertices[0];
                Pj = PiPjPk->vertices[1];
                Pk = PiPjPk->vertices[2];

                PiPj = PiPjPk->edges[0];
                PjPk = PiPjPk->edges[1];
                PkPi = PiPjPk->edges[2];
            } else if (edgeId == 1) {   //  lies on second edge
                Pi = PiPjPk->vertices[2];
                Pj = PiPjPk->vertices[0];
                Pk = PiPjPk->vertices[1];

                PiPj = PiPjPk->edges[2];
                PjPk = PiPjPk->edges[0];
                PkPi = PiPjPk->edges[1];
            } else {    //  lies on third edge
                Pi = PiPjPk->vertices[1];
                Pj = PiPjPk->vertices[2];
                Pk = PiPjPk->vertices[0];

                PiPj = PiPjPk->edges[1];
                PjPk = PiPjPk->edges[2];
                PkPi = PiPjPk->edges[0];
            }

            VertexHandle Pm;

            EdgeHandle PiPm;
            EdgeHandle PmPj;

            TriangleHandle PiPmPj;

            TrianglePair PiPmPjPermutationTrianglePair = PiPj->getAdjacentTriangle(PiPjPk);
            PiPmPj = PiPmPjPermutationTrianglePair.first;

            //  retrieve information from triangle PiPmPj
            if (PiPmPjPermutationTrianglePair.second == 0) {
                Pm = PiPmPj->vertices[2];

                PiPm = PiPmPj->edges[1];
                PmPj = PiPmPj->edges[2];
            } else if (PiPmPjPermutationTrianglePair.second == 1) {
                Pm = PiPmPj->vertices[0];

                PiPm = PiPmPj->edges[2];
                PmPj = PiPmPj->edges[0];
            } else {
                Pm = PiPmPj->vertices[1];

                PiPm = PiPmPj->edges[0];
                PmPj = PiPmPj->edges[1];
            }

            ////////////////////////////////////////////////////////////////
            //                   Split Triangles Started                  //
            ////////////////////////////////////////////////////////////////

            //  remove the badTriangles as an adjacent triangle of the edges of the triangles
            PiPm->removeAdjacentTriangle(PiPmPj);
            PmPj->removeAdjacentTriangle(PiPmPj);

            PjPk->removeAdjacentTriangle(PiPjPk);
            PkPi->removeAdjacentTriangle(PiPjPk);

            //  remove the bad edge PiPj
            delete PiPj;

            //  create the new triangles
            auto PiPmPr = new Triangle({Pi, Pm, Pr});
            auto PmPjPr = new Triangle({Pm, Pj, Pr});
            auto PjPkPr = new Triangle({Pj, Pk, Pr});
            auto PkPiPr = new Triangle({Pk, Pj, Pr});

            //  create the new edges for the new triangles
            auto PmPr = new Edge({Pm->id, Pr->id});
            auto PjPr = new Edge({Pj->id, Pr->id});
            auto PkPr = new Edge({Pk->id, Pr->id});
            auto PiPr = new Edge({Pi->id, Pr->id});

            //  assign adjacent triangles of the badTriangles Edges
            PiPm->addAdjacentTriangle(TrianglePair(PiPmPr, 0));
            PmPj->addAdjacentTriangle(TrianglePair(PmPjPr, 0));
            PjPk->addAdjacentTriangle(TrianglePair(PjPkPr, 0));
            PkPi->addAdjacentTriangle(TrianglePair(PkPiPr, 0));

            //  assign adjacent triangles of the new edges
            PmPr->addAdjacentTriangle(TrianglePair(PiPmPr, 1));
            PmPr->addAdjacentTriangle(TrianglePair(PmPjPr, 2));

            PjPr->addAdjacentTriangle(TrianglePair(PmPjPr, 1));
            PjPr->addAdjacentTriangle(TrianglePair(PjPkPr, 2));

            PkPr->addAdjacentTriangle(TrianglePair(PjPkPr, 1));
            PkPr->addAdjacentTriangle(TrianglePair(PkPiPr, 2));

            PiPr->addAdjacentTriangle(TrianglePair(PkPiPr, 1));
            PiPr->addAdjacentTriangle(TrianglePair(PiPmPr, 2));

            //  set edges of new triangles
            PiPmPr->setEdges({PiPm, PmPr, PiPr});
            PmPjPr->setEdges({PmPj, PjPr, PmPr});
            PjPkPr->setEdges({PjPk, PkPr, PjPr});
            PkPiPr->setEdges({PkPi, PiPr, PkPr});

            // update the DAG
            PiPjPk->childrenTriangles.push_back(PjPkPr);
            PiPjPk->childrenTriangles.push_back(PkPiPr);

            PiPmPj->childrenTriangles.push_back(PiPmPr);
            PiPmPj->childrenTriangles.push_back(PmPjPr);

            ////////////////////////////////////////////////////////////////
            //                   Split Triangles Ended                    //
            ////////////////////////////////////////////////////////////////

            legalizeEdge(PiPm, Pr);
            legalizeEdge(PmPj, Pr);
            legalizeEdge(PjPk, Pr);
            legalizeEdge(PkPi, Pr);
        }
    }

    meshingTimer.stopTimer();
}

bool DelaunayTriangulation::validateDelaunayTriangulation(const std::vector<TriangleHandle>& meshTriangles)
{
    std::cout << std::endl << "Validating Delaunay property..." << std::endl;
    bool validDelaunay = true;
    for (auto meshTriangle : meshTriangles) {
        for (auto meshVertex : meshVertices) {
            if (predicates.inCircle(meshTriangle, meshVertex)) {
                // std::cout << "Triangle " << *meshTriangle->vertices[0] << *meshTriangle->vertices[1]
                //           << *meshTriangle->vertices[2] << " is not Delaunay." << std::endl;
                validDelaunay = false;
            }
        }
    }
    return validDelaunay;
}

Mesh DelaunayTriangulation::getCleanMesh(bool validateDelaunayProperty)
{
    std::cout << std::endl << "Compute Mesh Results..." << std::endl;

    computeMeshResultsTimer.startTimer();

    Mesh mesh = Mesh();

    mesh.numberOfPoints = meshVertices.size();

    std::vector<TriangleHandle> meshTriangles = getTriangulation();

    if (validateDelaunayProperty) {
        if (!this->validateDelaunayTriangulation(meshTriangles)) {
            std::cout << "Triangulation is not Delaunay" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            std::cout << "Triangulation is Delaunay" << std::endl;
        }
    }

    // size_t visitedTrianglesCounter = 1;
    // for (auto& triangle : meshTriangles) {
    //     for (int j = 0; j < 3; ++j) {
    //         //  if vertex of triangle has not been traversed
    //         if (triangle->vertices[j]->id == std::numeric_limits<size_t>::max()) {
    //             triangle->vertices[j]->id = visitedTrianglesCounter++;
    //             mesh.points.emplace_back(*triangle->vertices[j]);
    //         }
    //     }
    // }

    for (auto& meshVertex : meshVertices) {
        mesh.points.emplace_back((Point) *meshVertex);
    }

    for (auto triangle : meshTriangles) {
        Mesh::Triangle newTriangle = Mesh::Triangle();
        for (int d = 0; d < 3; ++d) {
            newTriangle.indices[d] = triangle->vertices[d]->id;
        }

        mesh.triangles.push_back(newTriangle);
    }

    std::cout << std::endl << "Mesh Vertices: " << mesh.points.size() << std::endl;
    std::cout << "Mesh Triangles: " << mesh.triangles.size() << std::endl;

    computeMeshResultsTimer.stopTimer();

    return mesh;
}
