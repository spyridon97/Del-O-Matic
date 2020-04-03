/*
 * Filename:    DelaunayTriangulation.cxx
 *
 * Description: Source file of DelaunayTriangulation class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include <algorithm>
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

    for (auto& triangle : triangles) {
        delete triangle;
    }
    triangles.clear();
}

void DelaunayTriangulation::setInputPoints(std::vector<Point>& points)
{
    std::cout << std::endl << "Sort points and remove duplicates" << std::endl;

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
        vertices.emplace_back(new Vertex(point));
    }
}

void DelaunayTriangulation::createBoundingTriangle()
{
    std::cout << std::endl << "Compute Bounding Triangle..." << std::endl;

    computeBoundaryTriangleTimer.startTimer();

    double minX = (*vertices[0])[0];
    double minY = (*vertices[0])[1];
    double maxX = minX;
    double maxY = minY;

    for (auto& vertex : vertices) {
        VertexHandle point = vertex;
        if ((*point)[0] < minX) {
            minX = (*point)[0];
        }
        if ((*point)[1] < minY) {
            minY = (*point)[1];
        }
        if ((*point)[0] > maxX) {
            maxX = (*point)[0];
        }
        if ((*point)[1] > maxY) {
            maxY = (*point)[1];
        }
    }

    const double dx = maxX - minX;
    const double dy = maxY - minY;
    const double deltaMax = std::max(dx, dy);

    const double multiplier = 100;
    const double midX = (minX + maxX) / 2;
    const double midY = (minY + maxY) / 2;

    const auto p1 = new Vertex(Point({midX - multiplier * deltaMax, midY - deltaMax}));
    const auto p2 = new Vertex(Point({midX, midY + multiplier * deltaMax}));
    const auto p3 = new Vertex(Point({midX + multiplier * deltaMax, midY - deltaMax}));

    boundingTriangle = new Triangle({p1, p2, p3});

    computeBoundaryTriangleTimer.stopTimer();
}

void DelaunayTriangulation::generateMesh()
{
    createBoundingTriangle();

    std::cout << std::endl << "Compute Delaunay Triangulation..." << std::endl;

    meshingTimer.startTimer();

    auto p1 = boundingTriangle->vertex(0);
    auto p2 = boundingTriangle->vertex(1);
    auto p3 = boundingTriangle->vertex(2);

    //  add the bounding triangle in the list of triangles
    triangles.emplace_back(boundingTriangle);

    for (const auto& vertex : vertices) {
        std::vector<EdgeHandle> polygon;

        //  TODO use point location to improve complexity
        //  identify bad triangles
        for (auto& triangle : triangles) {
            if (triangle->inCircleTest(vertex)) {
                triangle->isBad = true;
                polygon.push_back(new Edge({triangle->vertex(0), triangle->vertex(1)}));
                polygon.push_back(new Edge({triangle->vertex(1), triangle->vertex(2)}));
                polygon.push_back(new Edge({triangle->vertex(2), triangle->vertex(0)}));
            }
        }

        //  remove bad triangles
        for (size_t i = 0; i < triangles.size(); ++i) {
            if (triangles[i]->isBad) {
                delete triangles[i];
                triangles.erase(triangles.begin() + i);
                i--;
            }
        }

        //  identify bad edges
        for (size_t i = 0; i < polygon.size(); ++i) {
            for (size_t j = i + 1; j < polygon.size(); ++j) {
                if (polygon[i]->isSame(*polygon[j])) {
                    polygon[i]->isBad = true;
                    polygon[j]->isBad = true;
                }
            }
        }

        //  remove bad edges
        for (size_t i = 0; i < polygon.size(); ++i) {
            if (polygon[i]->isBad) {
                delete polygon[i];
                polygon.erase(polygon.begin() + i);
                i--;
            }
        }

        //  add new triangles
        for (const auto& edge : polygon) {
            //  triangle's vertices are oriented in counter-clockwise order
            triangles.push_back(new Triangle({edge->vertex(0), edge->vertex(1), vertex}));
            delete edge;
        }
        polygon.clear();
    }

    //  remove triangles that contain vertices of the super triangle
    for (size_t i = 0; i < triangles.size(); ++i) {
        if (triangles[i]->containsVertex(p1) || triangles[i]->containsVertex(p2) || triangles[i]->containsVertex(p3)) {
            delete triangles[i];
            triangles.erase(triangles.begin() + i);
            i--;
        }
    }

    //  delete bounding triangle vertices
    delete p1;
    delete p2;
    delete p3;

    meshingTimer.stopTimer();
}

Mesh DelaunayTriangulation::getCleanMesh()
{
    std::cout << std::endl << "Compute Mesh Results..." << std::endl;

    computeMeshResultsTimer.startTimer();

    Mesh mesh = Mesh();

    mesh.numberOfPoints = vertices.size();

    size_t visitedTrianglesCounter = 1;
    for (auto& triangle : triangles) {
        for (int j = 0; j < 3; ++j) {
            //  if vertex of triangle has not been traversed
            if (triangle->vertex(j)->id == std::numeric_limits<size_t>::max()) {
                triangle->vertex(j)->id = visitedTrianglesCounter++;
                mesh.points.emplace_back(*triangle->vertex(j));
            }
        }
    }

    for (auto triangle : triangles) {
        Mesh::Triangle newTriangle = Mesh::Triangle();
        for (int d = 0; d < 3; ++d) {
            newTriangle.indices[d] = triangle->vertex(d)->id;
        }

        mesh.triangles.emplace_back(newTriangle);
    }

    std::cout << std::endl << "Mesh Vertices: " << mesh.points.size() << std::endl;
    std::cout << "Mesh Triangles: " << mesh.triangles.size() << std::endl;

    computeMeshResultsTimer.stopTimer();

    return mesh;
}
