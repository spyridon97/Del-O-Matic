/*
 * Filename:    TrianglesDAG.cxx
 * 
 * Description: Source file of TrianglesDAG class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/5/20.
 */

#include "TrianglesDAG.hxx"


TrianglesDAG::TrianglesDAG()
{
    rootTriangle = nullptr;
}

TrianglesDAG::~TrianglesDAG() = default;

void TrianglesDAG::setRootTriangle(TriangleHandle& rootTriangle)
{
    this->rootTriangle = rootTriangle;
}

TriangleHandle& TrianglesDAG::locateTriangle(TriangleHandle& triangle, VertexHandle vertex,
                                             std::array<double, 3>& orientationTests)
{
    size_t childrenSize = triangle->childrenTriangles.size();

    if (childrenSize == 0) {  //  base case
        //  This is mandatory to be executed because orientationTests array has to be updated
        //  for the case where a point falls on an edge of a triangle.
        GeometricPredicates::inTriangle(triangle, vertex, orientationTests);
        return triangle;
    } else if (childrenSize == 2) {
        if (GeometricPredicates::inTriangle(triangle->childrenTriangles[0], vertex, orientationTests)) {
            return locateTriangle(triangle->childrenTriangles[0], vertex, orientationTests);
        } else {
            return locateTriangle(triangle->childrenTriangles[1], vertex, orientationTests);
        }
    } else { // childrenSize == 3
        if (GeometricPredicates::inTriangle(triangle->childrenTriangles[0], vertex, orientationTests)) {
            return locateTriangle(triangle->childrenTriangles[0], vertex, orientationTests);
        } else if (GeometricPredicates::inTriangle(triangle->childrenTriangles[1], vertex, orientationTests)) {
            return locateTriangle(triangle->childrenTriangles[1], vertex, orientationTests);
        } else {
            return locateTriangle(triangle->childrenTriangles[2], vertex, orientationTests);
        }
    }
}

bool TrianglesDAG::containsRootTriangleVertices(TriangleHandle triangle) const
{
    return triangle->containsVertex(rootTriangle->vertices[0]) ||
           triangle->containsVertex(rootTriangle->vertices[1]) ||
           triangle->containsVertex(rootTriangle->vertices[2]);
}

void TrianglesDAG::getTriangulation(std::vector<TriangleHandle>& triangles, TriangleHandle& triangle)
{
    if (!triangle->visitedTriangle) {
        size_t childrenSize = triangle->childrenTriangles.size();
        if (childrenSize == 0) {  //  base case
            triangle->visitedTriangle = true;
            if (!containsRootTriangleVertices(triangle)) {
                triangles.push_back(triangle);
            }
        } else if (childrenSize == 2) {
            triangle->visitedTriangle = true;
            getTriangulation(triangles, triangle->childrenTriangles[0]);
            getTriangulation(triangles, triangle->childrenTriangles[1]);
        } else { //   childrenSize == 3
            triangle->visitedTriangle = true;
            getTriangulation(triangles, triangle->childrenTriangles[0]);
            getTriangulation(triangles, triangle->childrenTriangles[1]);
            getTriangulation(triangles, triangle->childrenTriangles[2]);
        }
    }
}

TriangleHandle& TrianglesDAG::locateTriangle(VertexHandle vertex, std::array<double, 3>& orientationTests)
{
    return locateTriangle(rootTriangle, vertex, orientationTests);
}

std::vector<TriangleHandle> TrianglesDAG::getTriangulation()
{
    std::vector<TriangleHandle> triangles;

    getTriangulation(triangles, rootTriangle);

    return triangles;
}
