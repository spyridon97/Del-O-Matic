/*
 * Filename:    DelaunayTriangulation.cxx
 *
 * Description: Source file of DelaunayTriangulation class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include "DelaunayTriangulation.hxx"


DelaunayTriangulation::DelaunayTriangulation()
{
    exactinit();
}

DelaunayTriangulation::~DelaunayTriangulation()
{
    for (auto& vertex : vertices) {
        delete vertex;
    }
    vertices.clear();
    triangles.clear();
}

void DelaunayTriangulation::setInputPoints(std::vector<Point>& points)
{
    //  sort vertices lexicographically in decreasing order. Cost: O(n log n )
    std::sort(points.rbegin(), points.rend());

    //  remove duplicate points. Cost: O(n)
    for (size_t i = 1; i < points.size(); ++i) {
        if (points[i] == points[i - 1]) {
            points.erase(points.begin() + i - 1);
            --i;
        }
    }

    //  convert points to Vertices (a.k.a Point*): Cost O(n)
    for (const auto& point : points) {
        vertices.emplace_back(new Point(point));
    }
}

Triangle DelaunayTriangulation::createBoundingTriangle()
{
    std::cout << std::endl << "Compute Bounding Triangle..." << std::endl;

    computeBoundaryTriangleTimer.start_seconds_timer();

    double minX = (*vertices[0])[0];
    double minY = (*vertices[0])[1];
    double maxX = minX;
    double maxY = minY;

    for (auto& vertex : vertices) {
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

    const double dx = maxX - minX;
    const double dy = maxY - minY;
    const double deltaMax = std::max(dx, dy);

    const double multiplier = 100;
    const double midX = (minX + maxX) / 2;
    const double midY = (minY + maxY) / 2;

    const auto p1 = new Point({midX - multiplier * deltaMax, midY - deltaMax});
    const auto p2 = new Point({midX, midY + multiplier * deltaMax});
    const auto p3 = new Point({midX + multiplier * deltaMax, midY - deltaMax});

    computeBoundaryTriangleTimer.stop_seconds_timer();

    return Triangle({p1, p2, p3});
}

void DelaunayTriangulation::generateMesh()
{
    Triangle boundingTriangle = createBoundingTriangle();

    std::cout << std::endl << "Compute Delaunay Triangulation..." << std::endl;

    meshingTimer.start_seconds_timer();

    auto p1 = boundingTriangle.vertex(0);
    auto p2 = boundingTriangle.vertex(1);
    auto p3 = boundingTriangle.vertex(2);

    //  create a list of triangles, and add the super-triangle in it
    triangles.emplace_back(boundingTriangle);

    for (const auto& vertex : vertices) {

        std::vector<Edge> polygon;

        //  TODO use point location to improve complexity
        for (auto& triangle : triangles) {
            if (triangle.inCircleTest(vertex)) {
                triangle.isBad = true;
                polygon.push_back(Edge({triangle.vertex(0), triangle.vertex(1)}));
                polygon.push_back(Edge({triangle.vertex(1), triangle.vertex(2)}));
                polygon.push_back(Edge({triangle.vertex(2), triangle.vertex(0)}));
            }
        }

        triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
                                       [](Triangle& t) {
                                           return t.isBad;
                                       }), triangles.end());

        for (auto e1 = polygon.begin(); e1 != polygon.end(); ++e1) {
            for (auto e2 = e1 + 1; e2 != polygon.end(); ++e2) {
                if (e1->compareEdges(*e2)) {
                    e1->isBad = true;
                    e2->isBad = true;
                }
            }
        }

        polygon.erase(std::remove_if(polygon.begin(), polygon.end(),
                                     [](Edge& edge) {
                                         return edge.isBad;
                                     }), end(polygon));

        for (const auto& edge : polygon) {
            //edge.point(0), edge.vertex(1), vertex;
            triangles.push_back(Triangle({edge.vertex(0), edge.vertex(1), vertex}));
        }

    }

    //  remove triangles that contain vertices of the super triangle
    triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
                                   [p1, p2, p3](Triangle& triangle) {
                                       return triangle.containsVertex(p1) || triangle.containsVertex(p2) ||
                                              triangle.containsVertex(p3);
                                   }), triangles.end());

    delete boundingTriangle.vertex(0);
    delete boundingTriangle.vertex(1);
    delete boundingTriangle.vertex(2);

    meshingTimer.stop_seconds_timer();
}

Mesh DelaunayTriangulation::getCleanMesh()
{
    std::cout << std::endl << "Compute Mesh Results..." << std::endl;

    computeMeshResultsTimer.start_seconds_timer();

    Mesh mesh = Mesh();

    mesh.numberOfPoints = vertices.size();

    size_t visitedTrianglesCounter = 1;
    for (auto& triangle : triangles) {
        for (int j = 0; j < 3; ++j) {
            //  if vertex of triangle has not been traversed
            if (triangle.vertex(j)->id == std::numeric_limits<size_t>::max()) {
                triangle.vertex(j)->id = visitedTrianglesCounter;
                mesh.points.emplace_back(*triangle.vertex(j));
                visitedTrianglesCounter++;
            }
        }
    }

    for (auto triangle : triangles) {
        Mesh::Triangle newTriangle = Mesh::Triangle();
        for (int d = 0; d < 3; ++d) {
            newTriangle.indices[d] = triangle.vertex(d)->id;
        }

        mesh.triangles.emplace_back(newTriangle);
    }

    computeMeshResultsTimer.stop_seconds_timer();

    return mesh;
}
