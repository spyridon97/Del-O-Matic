/*
 * Filename:    Edge.cxx
 * 
 * Description: Source file of Edge class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/2/20.
 */

#include "Edge.hxx"


Edge::Edge(std::array<int, 2> verticesIds)
{
    adjacentTrianglesWithEdgeIds.reserve(2);
    for (size_t i = 0; i < verticesIds.size(); ++i) {
        this->verticesIds[i] = verticesIds[i];
    }
    id = std::numeric_limits<size_t>::max();
}

Edge::~Edge() = default;

void Edge::addAdjacentTriangle(TrianglePair adjacentTriangleWithEdgeId)
{
    adjacentTrianglesWithEdgeIds.push_back(adjacentTriangleWithEdgeId);
}

void Edge::removeAdjacentTriangle(const TriangleHandle& triangle)
{
    if (adjacentTrianglesWithEdgeIds[0].first == triangle) {
        adjacentTrianglesWithEdgeIds.erase(adjacentTrianglesWithEdgeIds.begin() + 0);
    } else {
        adjacentTrianglesWithEdgeIds.erase(adjacentTrianglesWithEdgeIds.begin() + 1);
    }
}

TrianglePair Edge::getAdjacentTriangle(const TriangleHandle& triangle)
{
    if (triangle == adjacentTrianglesWithEdgeIds[0].first) {
        return adjacentTrianglesWithEdgeIds[1];
    } else {
        return adjacentTrianglesWithEdgeIds[0];
    }
}

bool Edge::isSame(const Edge& edge) const
{
    return (verticesIds[0] == edge.verticesIds[0] && verticesIds[1] == edge.verticesIds[1]) ||
           (verticesIds[0] == edge.verticesIds[1] && verticesIds[1] == edge.verticesIds[0]);
}

size_t Edge::getNumberOfAdjacentTriangles() const
{
    return adjacentTrianglesWithEdgeIds.size();
}
