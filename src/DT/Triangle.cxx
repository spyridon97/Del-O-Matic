/*
 * Filename:    Simplex.cxx
 * 
 * Description: Source file of Simplex class.
 *
 * Author:      Spiros Tsalikis
 * Created on   4/1/20.
 */

#include "Triangle.hxx"


Triangle::Triangle(std::array<VertexHandle, 3> vertices)
{
    for (size_t i = 0; i < vertices.size(); ++i) {
        this->vertices[i] = vertices[i];
    }
    edges.fill(nullptr);
    childrenTriangles.reserve(3);
    visitedTriangle = false;
}

Triangle::~Triangle() = default;

void Triangle::setEdges(std::array<EdgeHandle, 3> edges)
{
    for (size_t i = 0; i < edges.size(); ++i) {
        this->edges[i] = edges[i];
    }
}

bool Triangle::containsVertex(const VertexHandle& vertex) const
{
    return vertices[0]->id == vertex->id || vertices[1]->id == vertex->id || vertices[2]->id == vertex->id;
}
