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
     * @brief Default Destructor.
     */
    ~Vertex();

public:
    size_t id;
};

using VertexHandle = Vertex*;


#endif /* DELAUNAY_TRIANGULATION_VERTEX_HXX */
