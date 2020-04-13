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


DelaunayTriangulation::DelaunayTriangulation(bool robustPredicates) : HistoryDAG()
{
    GeometricPredicates::initialize(robustPredicates);
}

DelaunayTriangulation::~DelaunayTriangulation()
{
    for (auto& vertex : meshVertices) {
        delete vertex;
    }
    meshVertices.clear();
}

void DelaunayTriangulation::setInputVertices(std::vector<Vertex>& vertices)
{
    std::cout << std::endl << "Sort lexicographically, Remove duplicates, and Shuffle Vertices..."
              << std::endl;

    //  sort vertices lexicographically in descending order. Cost: O(n log n)
    std::sort(vertices.begin(), vertices.end(), std::greater<>());

    //  remove duplicate vertices. Cost: O(n)
    vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());

    //  compute a random permutation of the vertices
    //  Note: if shuffle is not activated, the complexity of the algorithm becomes: O(n^2).
    auto randomGenerator = std::default_random_engine(std::random_device{}());
    std::shuffle(vertices.begin(), vertices.end(), randomGenerator);

    meshVertices.clear();
    //  extract unique vertices. Cost O(n)
    for (size_t i = 0; i < vertices.size(); ++i) {
        auto vertex = new Vertex(vertices[i]);
        vertex->id = static_cast<int>(i + 1);
        meshVertices.push_back(vertex);
    }
    vertices.clear();
}

void DelaunayTriangulation::createBoundingTriangle()
{
    std::cout << std::endl << "Compute Bounding Triangle..." << std::endl;

    computeBoundaryTriangleTimer.startTimer();

    double minX = (*meshVertices[0])[0];
    double minY = (*meshVertices[0])[1];
    double maxX = minX;
    double maxY = minY;

    for (auto vertex : meshVertices) {
        if ((*vertex)[0] < minX) {
            minX = (*vertex)[0];
        }
        if ((*vertex)[1] < minY) {
            minY = (*vertex)[1];
        }
        if ((*vertex)[0] > maxX) {
            maxX = (*vertex)[0];
        }
        if ((*vertex)[1] > maxY) {
            maxY = (*vertex)[1];
        }
    }

    const double midX = (minX + maxX) / 2;
    const double midY = (minY + maxY) / 2;
    const double maxWidth = std::max(maxX - minX, maxY - minY);
    const double multiplier = 100.0;

    auto Pi = new Vertex({midX - multiplier * maxWidth, midY - maxWidth});
    Pi->id = -3;
    auto Pj = new Vertex({midX, midY + multiplier * maxWidth});
    Pj->id = -2;
    auto Pk = new Vertex({midX + multiplier * maxWidth, midY - maxWidth});
    Pk->id = -1;

    auto PiPj = new Edge();
    auto PjPk = new Edge();
    auto PkPi = new Edge();

    computeBoundaryTriangleTimer.stopTimer();

    auto PiPjPk = new Triangle({Pi, Pj, Pk});
    PiPjPk->setEdges({PiPj, PjPk, PkPi});

    PiPj->addAdjacentTriangle(TrianglePair(PiPjPk, 0));
    PjPk->addAdjacentTriangle(TrianglePair(PiPjPk, 1));
    PkPi->addAdjacentTriangle(TrianglePair(PiPjPk, 2));

    //  initialize root triangle of DAG
    setRootTriangle(PiPjPk);
}

void DelaunayTriangulation::legalizeEdge(EdgeHandle& PiPj, const VertexHandle& Pr)
{
    if (!PiPj->isBoundaryEdge()) {
        /*
         *                                  Pk
         *                                  /\
         *                                 /  \
         *                                /    \
         *                               /      \
         *                              /        \
         *                             /          \
         *                            /            \
         *                           /              \
         *                        Pi ---------------- Pj
         *                            \            /
         *                             \          /
         *                              \        /
         *                               \      /
         *                                \    /
         *                                 \  /
         *                                  \/
         *                                  Pr
         */

        //  find adjacent triangles of edge PiPj
        auto PiPjPr = PiPj->getLeftTriangle();
        auto Pk = PiPj->getDestinationVertexRightTriangle();

        //  Check if PiPj is illegal
        if (GeometricPredicates::inCircle(PiPjPr, Pk)) {
            ////////////////////////////////////////////////////////////////
            //                      Flip Edge Started                     //
            ////////////////////////////////////////////////////////////////

            auto PiPkPj = PiPj->getRightTriangle();

            //  Find vertices and edges of PiPjPr and PiPkPj
            auto Pi = PiPj->getOriginVertexLeftTriangle();
            auto Pj = PiPj->getDestinationVertexLeftTriangle();

            auto PjPr = PiPj->getDestinationEdgeLeftTriangle();
            auto PrPi = PiPj->getApexEdgeLeftTriangle();

            auto PiPk = PiPj->getOriginEdgeRightTriangle();
            auto PkPj = PiPj->getDestinationEdgeRightTriangle();

            //  remove the PiPj edge because we are gonna flip it
            delete PiPj;

            //  create the new triangles
            auto PiPkPr = new Triangle({Pi, Pk, Pr});
            auto PkPjPr = new Triangle({Pk, Pj, Pr});

            //  create the new edge for the new triangles
            auto PkPr = new Edge();

            //  assign adjacent triangles of the PiPkPr edges
            PiPk->replaceAdjacentTriangle(PiPkPj, TrianglePair(PiPkPr, 0));
            PkPr->addAdjacentTriangle(TrianglePair(PiPkPr, 1));
            PrPi->replaceAdjacentTriangle(PiPjPr, TrianglePair(PiPkPr, 2));

            //  assign adjacent triangles of the PkPjPr edges
            PkPj->replaceAdjacentTriangle(PiPkPj, TrianglePair(PkPjPr, 0));
            PjPr->replaceAdjacentTriangle(PiPjPr, TrianglePair(PkPjPr, 1));
            PkPr->addAdjacentTriangle(TrianglePair(PkPjPr, 2));

            //  set edges of PiPkPr and PkPjPr
            PiPkPr->setEdges({PiPk, PkPr, PrPi});
            PkPjPr->setEdges({PkPj, PjPr, PkPr});

            // update the DAG
            PiPkPj->childrenTriangles.push_back(PiPkPr);
            PiPkPj->childrenTriangles.push_back(PkPjPr);

            PiPjPr->childrenTriangles.push_back(PiPkPr);
            PiPjPr->childrenTriangles.push_back(PkPjPr);

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

    //  iterate over the meshVertices and insert them in the current triangulation. Cost: O(n)
    for (auto& Pr : meshVertices) {
        //  locate a triangle that includes Pr. Cost: O(log n)

        //  This complexity is accurate because our vertices are shuffled uniformly,
        //  therefore the depth of the History DAG is almost uniformly distributed.
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

        if (edgeId == -1) { //  if vertex Pr lies in the interior of the triangle
            /*
             *                        Pi ---------------- Pj
             *                            \            /
             *                             \          /
             *                              \   Pr   /
             *                               \      /
             *                                \    /
             *                                 \  /
             *                                  \/
             *                                  Pk
             */

            auto Pi = PiPjPk->vertices[0];
            auto Pj = PiPjPk->vertices[1];
            auto Pk = PiPjPk->vertices[2];

            auto PiPj = PiPjPk->edges[0];
            auto PjPk = PiPjPk->edges[1];
            auto PkPi = PiPjPk->edges[2];

            ////////////////////////////////////////////////////////////////
            //                    Split Triangle Started                  //
            ////////////////////////////////////////////////////////////////

            //  create the new triangles
            auto PiPjPr = new Triangle({Pi, Pj, Pr});
            auto PjPkPr = new Triangle({Pj, Pk, Pr});
            auto PkPiPr = new Triangle({Pk, Pi, Pr});

            //  create the new edges for the new triangles
            auto PiPr = new Edge();
            auto PjPr = new Edge();
            auto PkPr = new Edge();

            //  assign adjacent triangles of the PiPjPr Edges
            PiPj->replaceAdjacentTriangle(PiPjPk, TrianglePair(PiPjPr, 0));
            PjPr->addAdjacentTriangle(TrianglePair(PiPjPr, 1));
            PiPr->addAdjacentTriangle(TrianglePair(PiPjPr, 2));

            //  assign adjacent triangles of the PjPkPr Edges
            PjPk->replaceAdjacentTriangle(PiPjPk, TrianglePair(PjPkPr, 0));
            PkPr->addAdjacentTriangle(TrianglePair(PjPkPr, 1));
            PjPr->addAdjacentTriangle(TrianglePair(PjPkPr, 2));

            //  assign adjacent triangles of the PkPiPr Edges
            PkPi->replaceAdjacentTriangle(PiPjPk, TrianglePair(PkPiPr, 0));
            PiPr->addAdjacentTriangle(TrianglePair(PkPiPr, 1));
            PkPr->addAdjacentTriangle(TrianglePair(PkPiPr, 2));

            //  set edges of PiPjPr, PjPkPr and PkPiPr
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

            //  legalize the edges of PiPjPk
            legalizeEdge(PiPj, Pr);
            legalizeEdge(PjPk, Pr);
            legalizeEdge(PkPi, Pr);
        } else {    //  if vertex lies on an edge
            /*
             *                                  Pm
             *                                  /\
             *                                 /  \
             *                                /    \
             *                               /      \
             *                              /        \
             *                             /          \
             *                            /            \
             *                           /              \
             *                        Pi -------Pr------- Pj
             *                            \            /
             *                             \          /
             *                              \        /
             *                               \      /
             *                                \    /
             *                                 \  /
             *                                  \/
             *                                  Pk
             */

            //  retrieve information from PiPjPk
            VertexHandle Pk;
            EdgeHandle PiPj;

            //  define the above variables to treat each edge the same way
            if (edgeId == 0) {  //  lies on first edge
                Pk = PiPjPk->vertices[2];
                PiPj = PiPjPk->edges[0];
            } else if (edgeId == 1) {   //  lies on second edge
                Pk = PiPjPk->vertices[0];
                PiPj = PiPjPk->edges[1];
            } else {    //  lies on third edge
                Pk = PiPjPk->vertices[1];
                PiPj = PiPjPk->edges[2];
            }

            PiPj->determineAdjacentTriangles(Pk->id);

            auto Pi = PiPj->getOriginVertexLeftTriangle();
            auto Pj = PiPj->getDestinationVertexLeftTriangle();
            auto PjPk = PiPj->getDestinationEdgeLeftTriangle();
            auto PkPi = PiPj->getApexEdgeLeftTriangle();

            //  retrieve information from PiPmPj
            auto PiPmPj = PiPj->getRightTriangle();
            auto Pm = PiPj->getDestinationVertexRightTriangle();
            auto PiPm = PiPj->getOriginEdgeRightTriangle();
            auto PmPj = PiPj->getDestinationEdgeRightTriangle();

            ////////////////////////////////////////////////////////////////
            //                   Split Triangles Started                  //
            ////////////////////////////////////////////////////////////////

            //  remove the bad edge PiPj
            delete PiPj;

            //  create the new triangles
            auto PiPmPr = new Triangle({Pi, Pm, Pr});
            auto PmPjPr = new Triangle({Pm, Pj, Pr});
            auto PjPkPr = new Triangle({Pj, Pk, Pr});
            auto PkPiPr = new Triangle({Pk, Pi, Pr});

            //  create the new edges for the new triangles
            auto PiPr = new Edge();
            auto PmPr = new Edge();
            auto PjPr = new Edge();
            auto PkPr = new Edge();

            //  assign adjacent triangles of the PiPmPr Edges
            PiPm->replaceAdjacentTriangle(PiPmPj, TrianglePair(PiPmPr, 0));
            PmPr->addAdjacentTriangle(TrianglePair(PiPmPr, 1));
            PiPr->addAdjacentTriangle(TrianglePair(PiPmPr, 2));

            //  assign adjacent triangles of the PmPjPr Edges
            PmPj->replaceAdjacentTriangle(PiPmPj, TrianglePair(PmPjPr, 0));
            PjPr->addAdjacentTriangle(TrianglePair(PmPjPr, 1));
            PmPr->addAdjacentTriangle(TrianglePair(PmPjPr, 2));

            //  assign adjacent triangles of the PjPkPr Edges
            PjPk->replaceAdjacentTriangle(PiPjPk, TrianglePair(PjPkPr, 0));
            PkPr->addAdjacentTriangle(TrianglePair(PjPkPr, 1));
            PjPr->addAdjacentTriangle(TrianglePair(PjPkPr, 2));

            //  assign adjacent triangles of the PkPiPr edges
            PkPi->replaceAdjacentTriangle(PiPjPk, TrianglePair(PkPiPr, 0));
            PiPr->addAdjacentTriangle(TrianglePair(PkPiPr, 1));
            PkPr->addAdjacentTriangle(TrianglePair(PkPiPr, 2));

            //  set edges of new triangles
            PiPmPr->setEdges({PiPm, PmPr, PiPr});
            PmPjPr->setEdges({PmPj, PjPr, PmPr});
            PjPkPr->setEdges({PjPk, PkPr, PjPr});
            PkPiPr->setEdges({PkPi, PiPr, PkPr});

            // update the DAG
            PiPmPj->childrenTriangles.push_back(PiPmPr);
            PiPmPj->childrenTriangles.push_back(PmPjPr);

            PiPjPk->childrenTriangles.push_back(PjPkPr);
            PiPjPk->childrenTriangles.push_back(PkPiPr);

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
            if (GeometricPredicates::inCircle(meshTriangle, meshVertex)) {
                std::cout << "Triangle: " << *meshTriangle->vertices[0] << *meshTriangle->vertices[1]
                          << *meshTriangle->vertices[2] << " against Vertex: " << *meshVertex << " is not Delaunay."
                          << std::endl;
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

    std::vector<TriangleHandle> meshTriangles = getTriangulation();

    if (validateDelaunayProperty) {
        if (!this->validateDelaunayTriangulation(meshTriangles)) {
            std::cout << std::endl << "Triangulation is not Delaunay" << std::endl;
        } else {
            std::cout << std::endl << "Triangulation is Delaunay" << std::endl;
        }
    }

    for (auto& meshVertex : meshVertices) {
        mesh.vertices.emplace_back(*meshVertex);
    }

    for (auto triangle : meshTriangles) {
        Mesh::Triangle newTriangle = Mesh::Triangle();
        for (int d = 0; d < 3; ++d) {
            newTriangle.indices[d] = triangle->vertices[d]->id;
        }

        mesh.triangles.push_back(newTriangle);
    }

    std::cout << std::endl << "Mesh Vertices: " << mesh.vertices.size() << std::endl;
    std::cout << "Mesh Triangles: " << mesh.triangles.size() << std::endl;

    computeMeshResultsTimer.stopTimer();

    return mesh;
}
