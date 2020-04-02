/*
 * Filename:    Edge.cxx
 * 
 * Description: Source file of Edge class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/2/20.
 */

#include "Edge.hxx"


Edge::Edge(std::array<VertexHandle, 2> points)
{
    for (size_t i = 0; i < points.size(); ++i) {
        this->vertices[i] = points[i];
    }
    isBad = false;
    id = std::numeric_limits<size_t>::max();
}

Edge::~Edge() = default;

Edge::Edge(const Edge& otherEdge)
{
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i] = otherEdge.vertex(i);
    }
    isBad = otherEdge.isBad;
    id = otherEdge.id;
}

VertexHandle Edge::vertex(unsigned char index) const
{
    if (index > 1 || index < 0) {
        throw std::out_of_range(
                "index is bigger compared to what Edge Supports, where max = " +
                std::to_string(1));
    }

    return vertices[index];
}

VertexHandle& Edge::vertex(unsigned char index)
{
    if (index > 1 || index < 0) {
        throw std::out_of_range(
                "index is bigger compared to what Edge Supports, where max = " +
                std::to_string(1));
    }

    return vertices[index];
}

bool Edge::isSame(const Edge& edge) const
{
    return (*vertices[0] == *edge.vertex(0) && *vertices[1] == *edge.vertex(1)) ||
           (*vertices[0] == *edge.vertex(1) && *vertices[1] == *edge.vertex(0));
}

double Edge::getSquaredLength() const
{
    double squaredLength = 0;
    for (size_t i = 0; i < 2; i++) {
        squaredLength += std::pow((*vertices[1])[i] - (*vertices[0])[i], 2);
    }

    return squaredLength;
}
