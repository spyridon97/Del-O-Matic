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


DelaunayTriangulation::DelaunayTriangulation()
{
    exactinit();
}

DelaunayTriangulation::~DelaunayTriangulation()
{
    for (auto& vertex : meshVertices) {
        delete vertex;
    }
    meshVertices.clear();

    for (auto& triangle : meshTriangles) {
        delete triangle;
    }
    meshTriangles.clear();
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

    //  shuffle points
    // std::random_device rd;
    // auto rng = std::default_random_engine(rd());
    // std::shuffle(points.begin(), points.end(), rng);

    //  convert points to Vertices (a.k.a Point*): Cost O(n)
    for (const auto& point : points) {
        meshVertices.emplace_back(new Vertex(point));
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
        Vertex point = *vertex;
        if (point[0] < minX) {
            minX = point[0];
        }
        if (point[1] < minY) {
            minY = point[1];
        }
        if (point[0] > maxX) {
            maxX = point[0];
        }
        if (point[1] > maxY) {
            maxY = point[1];
        }
    }

    const double dx = maxX - minX;
    const double dy = maxY - minY;
    const double deltaMax = std::max(dx, dy);

    const double multiplier = 100;
    const double midX = (minX + maxX) / 2;
    const double midY = (minY + maxY) / 2;

    const auto p1 = new Vertex({midX - multiplier * deltaMax, midY - deltaMax});
    const auto p2 = new Vertex({midX, midY + multiplier * deltaMax});
    const auto p3 = new Vertex({midX + multiplier * deltaMax, midY - deltaMax});

    boundingTriangle = new Triangle({p1, p2, p3});

    computeBoundaryTriangleTimer.stopTimer();
}

void DelaunayTriangulation::generateMesh()
{
    createBoundingTriangle();

    std::cout << std::endl << "Compute Delaunay Triangulation..." << std::endl;

    meshingTimer.startTimer();

    auto p1 = boundingTriangle->vertices[0];
    auto p2 = boundingTriangle->vertices[1];
    auto p3 = boundingTriangle->vertices[2];

    //  add the bounding triangle in the list of triangles
    meshTriangles.emplace_back(boundingTriangle);

    for (const auto& vertex : meshVertices) {
        std::vector<EdgeHandle> polygon;

        //  TODO use point location to improve complexity
        //  identify and remove bad triangles
        for (size_t i = 0; i < meshTriangles.size(); ++i) {
            if (meshTriangles[i]->inCircleTest(vertex)) {
                polygon.push_back(new Edge({meshTriangles[i]->vertices[0], meshTriangles[i]->vertices[1]}));
                polygon.push_back(new Edge({meshTriangles[i]->vertices[1], meshTriangles[i]->vertices[2]}));
                polygon.push_back(new Edge({meshTriangles[i]->vertices[2], meshTriangles[i]->vertices[0]}));
                delete meshTriangles[i];
                meshTriangles.erase(meshTriangles.begin() + i);
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
            meshTriangles.push_back(new Triangle({edge->vertices[0], edge->vertices[1], vertex}));
            delete edge;
        }
        polygon.clear();
    }

    //  remove triangles that contain vertices of the super triangle
    for (size_t i = 0; i < meshTriangles.size(); ++i) {
        if (meshTriangles[i]->containsVertex(p1) || meshTriangles[i]->containsVertex(p2) ||
            meshTriangles[i]->containsVertex(p3)) {
            delete meshTriangles[i];
            meshTriangles.erase(meshTriangles.begin() + i);
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

    mesh.numberOfPoints = meshVertices.size();

    size_t visitedTrianglesCounter = 1;
    for (auto& triangle : meshTriangles) {
        for (int j = 0; j < 3; ++j) {
            //  if vertex of triangle has not been traversed
            if (triangle->vertices[j]->id == std::numeric_limits<size_t>::max()) {
                triangle->vertices[j]->id = visitedTrianglesCounter++;
                mesh.points.emplace_back(*triangle->vertices[j]);
            }
        }
    }

    for (auto triangle : meshTriangles) {
        Mesh::Triangle newTriangle = Mesh::Triangle();
        for (int d = 0; d < 3; ++d) {
            newTriangle.indices[d] = triangle->vertices[d]->id;
        }

        mesh.triangles.emplace_back(newTriangle);
    }

    std::cout << std::endl << "Mesh Vertices: " << mesh.points.size() << std::endl;
    std::cout << "Mesh Triangles: " << mesh.triangles.size() << std::endl;

    computeMeshResultsTimer.stopTimer();

    return mesh;
}
