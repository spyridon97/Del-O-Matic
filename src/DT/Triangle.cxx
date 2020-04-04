/*
 * Filename:    Simplex.cxx
 * 
 * Description: Source file of Simplex class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include "Triangle.hxx"


Triangle::Triangle(std::array<VertexHandle, 3> points)
{
    for (size_t i = 0; i < points.size(); ++i) {
        this->vertices[i] = points[i];
    }
    id = std::numeric_limits<size_t>::max();
}

Triangle::~Triangle() = default;

Triangle::Triangle(const Triangle& otherTriangle)
{
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i] = otherTriangle.vertex(i);
    }
    id = otherTriangle.id;
}

VertexHandle Triangle::vertex(unsigned char index) const
{
    if (index > 2 || index < 0) {
        throw std::out_of_range(
                "index is bigger compared to what Triangle Supports, where max = " +
                std::to_string(2));
    }

    return vertices[index];
}

VertexHandle& Triangle::vertex(unsigned char index)
{
    if (index > 2 || index < 0) {
        throw std::out_of_range(
                "index is bigger compared to what Triangle Supports, where max = " +
                std::to_string(2));
    }

    return vertices[index];
}

bool Triangle::inCircleTest(const VertexHandle& vertex) const
{
    // double orientResult = orient2d(vertices[0]->toArray(), vertices[1]->toArray(),
    //                                vertices[2]->toArray());
    // if (orientResult > 0) {
    //     std::cout << orientResult << *vertices[0] << *vertices[1] << *vertices[2] << std::endl;
    // }
    //
    // if (orientResult > 0) { //  ClockWise order
    //     double inCircleResult = incircle(vertices[0]->toArray(), vertices[1]->toArray(),
    //                                      vertices[2]->toArray(),
    //                                      vertex->toArray());
    //     return inCircleResult > 0;
    // } else if (orientResult < 0) { //  Counter-ClockWise order
    //     double inCircleResult = incircle(vertices[0]->toArray(), vertices[1]->toArray(),
    //                                      vertices[2]->toArray(),
    //                                      vertex->toArray());
    //     return inCircleResult < 0;
    // } else {
    //     return false;
    // }

    //  triangle vertices are oriented in counter-clockwise order
    return incircle(vertices[0]->toArray(), vertices[1]->toArray(), vertices[2]->toArray(), vertex->toArray()) < 0;
}

bool Triangle::containsVertex(const VertexHandle& vertex) const
{
    return *vertices[0] == *vertex || *vertices[1] == *vertex || *vertices[2] == *vertex;
}
