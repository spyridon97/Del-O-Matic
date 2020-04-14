/*
 * Filename:    Vertex.cxx
 * 
 * Description: Source file of Vertex class.
 *
 * Author:      Spiros Tsalikis
 * Created on   4/1/20.
 */

#include "Vertex.hxx"


Vertex::Vertex() : array()
{
    this->fill(0);
    id = 0;
}

Vertex::Vertex(const Vertex& vertex) : array(vertex)
{
    for (size_t i = 0; i < 2; i++) {
        this->coordinates[i] = vertex[i];
    }
    id = vertex.id;
}

Vertex::Vertex(std::array<double, 2> coord) : array()
{
    for (size_t i = 0; i < 2; i++) {
        this->coordinates[i] = coord[i];
    }
    id = 0;
}

Vertex::~Vertex() = default;

std::istream& operator>>(std::istream& input, Vertex& vertex)
{
    char c;
    input >> c;

    if (!input.eof()) {
        std::array<double, 2> coordinates{};
        for (size_t i = 0; i < 2; i++) {
            input >> coordinates[i] >> c;
        }
        vertex = Vertex(coordinates);
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const Vertex& vertex)
{
    output << "(";
    for (size_t i = 0; i < 2 - 1; i++) {
        output << vertex[i] << ", ";
    }
    output << vertex[2 - 1] << ")";

    return output;
}