/*
 * Filename:    Edge.cxx
 * 
 * Description: Source file of Edge class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/2/20.
 */

#include "Edge.hxx"


Edge::Edge(std::array<VertexHandle, 2> points) : array()
{
    for (size_t i = 0; i < points.size(); ++i) {
        this->vertices[i] = points[i];
    }
    isBad = false;
    id = std::numeric_limits<size_t>::max();
}

Edge::~Edge() = default;

Edge::Edge(const Edge& otherEdge) : array(otherEdge)
{
    for (size_t i = 0; i < size(); i++) {
        vertices[i] = otherEdge.vertices[i];
    }
    isBad = otherEdge.isBad;
    id = otherEdge.id;
}

bool Edge::isSame(const Edge& edge) const
{
    return (*vertices[0] == *edge.vertices[0] && *vertices[1] == *edge.vertices[1]) ||
           (*vertices[0] == *edge.vertices[1] && *vertices[1] == *edge.vertices[0]);
}

double Edge::getSquaredLength() const
{
    double squaredLength = 0;
    for (size_t i = 0; i < 2; i++) {
        squaredLength += std::pow((*vertices[1])[i] - (*vertices[0])[i], 2);
    }

    return squaredLength;
}
