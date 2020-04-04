/*
 * Filename:    Simplex.cxx
 * 
 * Description: Source file of Simplex class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#include "Triangle.hxx"


Triangle::Triangle() : array()
{
    fill(nullptr);
    id = std::numeric_limits<size_t>::max();
}

Triangle::Triangle(std::array<VertexHandle, 3> points) : array()
{
    for (size_t i = 0; i < points.size(); ++i) {
        this->vertices[i] = points[i];
    }
    id = std::numeric_limits<size_t>::max();
}

Triangle::Triangle(const Triangle& otherTriangle) : array(otherTriangle)
{
    for (size_t i = 0; i < size(); i++) {
        vertices[i] = otherTriangle.vertices[i];
    }
    id = otherTriangle.id;
}

Triangle::~Triangle() = default;

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
    return incircle(vertices[0]->coordinates, vertices[1]->coordinates, vertices[2]->coordinates, vertex->coordinates) < 0;
}

bool Triangle::containsVertex(const VertexHandle& vertex) const
{
    return *vertices[0] == *vertex || *vertices[1] == *vertex || *vertices[2] == *vertex;
}
