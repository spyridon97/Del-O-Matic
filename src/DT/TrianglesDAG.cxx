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
    predicates = GeometricPredicates();
    rootTriangle = nullptr;
}

TrianglesDAG::~TrianglesDAG() = default;

void TrianglesDAG::setRootTriangle(TriangleHandle rootTriangle)
{
    this->rootTriangle = rootTriangle;
}

TriangleHandle TrianglesDAG::locateTriangle(TriangleHandle triangle, VertexHandle vertex,
                                            std::array<double, 3>& orientationTests)
{
    size_t childrenSize = triangle->childrenTriangles.size();

    if (childrenSize == 0) {  //  base case
        if (triangle != rootTriangle) {
            return triangle;
        } else {
            orientationTests = {-1, 1, 1};
            return rootTriangle;
        }
    } else if (childrenSize == 2) {
        if (predicates.inTriangle(triangle->childrenTriangles[0], vertex, orientationTests)) {
            return locateTriangle(triangle->childrenTriangles[0], vertex, orientationTests);
        } else {
            return locateTriangle(triangle->childrenTriangles[1], vertex, orientationTests);
        }
    } else { // childrenSize == 3
        if (predicates.inTriangle(triangle->childrenTriangles[0], vertex, orientationTests)) {
            return locateTriangle(triangle->childrenTriangles[0], vertex, orientationTests);
        } else if (predicates.inTriangle(triangle->childrenTriangles[1], vertex, orientationTests)) {
            return locateTriangle(triangle->childrenTriangles[1], vertex, orientationTests);
        } else {
            return locateTriangle(triangle->childrenTriangles[2], vertex, orientationTests);
        }
    }
}

bool TrianglesDAG::containsRootTriangleVertices(TriangleHandle triangle) const
{
    // std::cout << "Check root triangles" << std::endl;
    return triangle->containsVertex(rootTriangle->vertices[0]) ||
           triangle->containsVertex(rootTriangle->vertices[1]) ||
           triangle->containsVertex(rootTriangle->vertices[2]);
}

void TrianglesDAG::getTriangulation(std::vector<TriangleHandle>& triangles, TriangleHandle& triangle)
{
    if (!triangle->visitedTriangle) {
    // if (triangle != nullptr) {
        size_t childrenSize = triangle->childrenTriangles.size();
        if (childrenSize == 0) {  //  base case
            triangle->visitedTriangle = true;
            if (!containsRootTriangleVertices(triangle)) {
                triangles.push_back(triangle);
            }
            // auto leafTriangle = new Triangle(triangle);
            // delete triangle;
            // triangle = nullptr;
            //
            // if (!containsRootTriangleVertices(leafTriangle)) {
            //     triangles.push_back(leafTriangle);
            // }
        } else if (childrenSize == 2) {
            triangle->visitedTriangle = true;
            getTriangulation(triangles, triangle->childrenTriangles[0]);
            getTriangulation(triangles, triangle->childrenTriangles[1]);
            // auto childrenTriangles = triangle->childrenTriangles;
            // delete triangle;
            // triangle = nullptr;
            // getTriangulation(triangles, childrenTriangles[0]);
            // getTriangulation(triangles, childrenTriangles[1]);
        } else { //   childrenSize == 3
            triangle->visitedTriangle = true;
            getTriangulation(triangles, triangle->childrenTriangles[0]);
            getTriangulation(triangles, triangle->childrenTriangles[1]);
            getTriangulation(triangles, triangle->childrenTriangles[2]);
            // auto childrenTriangles = triangle->childrenTriangles;
            // delete triangle;
            // triangle = nullptr;
            // getTriangulation(triangles, childrenTriangles[0]);
            // getTriangulation(triangles, childrenTriangles[1]);
            // getTriangulation(triangles, childrenTriangles[2]);
        }
    }
}

TriangleHandle TrianglesDAG::locateTriangle(VertexHandle vertex, std::array<double, 3>& orientationTests)
{
    return locateTriangle(rootTriangle, vertex, orientationTests);
}

std::vector<TriangleHandle> TrianglesDAG::getTriangulation()
{
    std::vector<TriangleHandle> triangles;

    getTriangulation(triangles, rootTriangle);

    return triangles;
}
