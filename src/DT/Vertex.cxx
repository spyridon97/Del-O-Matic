/*
 * Filename:    Vertex.cxx
 * 
 * Description: Source file of Vertex class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/2/20.
 */

#include "Vertex.hxx"


Vertex::Vertex() : Point()
{
    id = std::numeric_limits<size_t>::max();
}

Vertex::Vertex(const Point& point) : Vertex()
{
    for (size_t i = 0; i < 2; i++) {
        coord[i] = point[i];
    }
}

Vertex::~Vertex() = default;
