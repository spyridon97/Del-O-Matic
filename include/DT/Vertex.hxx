/*
 * Filename:    Vertex.hxx
 * 
 * Description: Header file of Vertex class.
 *
 * Author:      Spiros Tsalikis
 * Created on   4/1/20.
 */

#ifndef DELOMATIC_VERTEX_HXX
#define DELOMATIC_VERTEX_HXX


#include <array>
#include <iostream>


class Vertex;

using VertexHandle = Vertex*;

/**
 * @brief Facilitates a 2D cartesian Vertex.
 */
class Vertex : public std::array<double, 2>
{
public:
    /**
     * @brief Constructor of Vertex class which sets all dimensions to 0.
     */
    Vertex();

    /**
     * @brief Copy Constructor of Vertex class.
     *
     * @param vertex is the vertex of which its coordinates will be extracted
     */
    Vertex(const Vertex& vertex);

    /**
     * @brief Constructor of Vertex class which set all dimensions using a specific array.
     *
     * @param coord is the array that includes the coordinates of the vertex
     */
    explicit Vertex(std::array<double, 2> coord);

    /**
     * @brief Destructor of Vertex class.
     */
    ~Vertex();

public:
    #define coordinates _M_elems

    /**
     * @brief This id is used to define vertex for edge and to print fast the triangulation
     * If id =  0, that's the default.
     * If id = -3, it's the first vertex of the boundary triangle
     * If id = -2, it's the second vertex of the boundary triangle
     * If id = -1, it's the third vertex of the boundary triangle
     */
    int id;
};

/**
 * @brief Overloads operator ">>".
 *
 * @param input is the stream which is used to read a vertex
 * @param vertex is a vertex in which the input coordinates will be saved to
 * @return a vertex with the input coordinates
 */
std::istream& operator>>(std::istream& input, Vertex& vertex);

/**
 * @brief Overloads operator "<<".
 *
 * @param output is the stream which is used to output a vertex
 * @param vertex is a vertex whose coordinated will be outputed
 * @return the output coordinates
 */
std::ostream& operator<<(std::ostream& output, const Vertex& vertex);


#endif /* DELOMATIC_VERTEX_HXX */
