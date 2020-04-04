/*
 * Filename:    Vertex.hxx
 * 
 * Description: Header file of Vertex class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/2/20.
 */

#ifndef DELAUNAY_TRIANGULATION_VERTEX_HXX
#define DELAUNAY_TRIANGULATION_VERTEX_HXX


#include "Point.hxx"


class Vertex;

using VertexHandle = Vertex*;

class Vertex : public Point
{
public:
    /**
     * @brief Default constructor
     */
    Vertex();

    /**
     * @brief Copy Constructor.
     *
     * @param point the copied point
     */
    explicit Vertex(const Point& point);

    /**
     * @brief Constructor of Vertex class which set all dimensions using a specific array.
     *
     * @param coord is the array that includes the coordinates of the vertex
     */
    explicit Vertex(std::array<double, 2> coord);

    /**
     * @brief Default Destructor.
     */
    ~Vertex();

public:
    size_t id;
};


#endif /* DELAUNAY_TRIANGULATION_VERTEX_HXX */
