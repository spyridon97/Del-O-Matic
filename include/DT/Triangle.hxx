/*
 * Filename:    Triangle.hxx
 * 
 * Description: Header file of Triangle class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#ifndef DELAUNAY_TRIANGULATION_TRIANGLE_HXX
#define DELAUNAY_TRIANGULATION_TRIANGLE_HXX


#include "Predicates.hxx"
#include "Vertex.hxx"


class Triangle;

using TriangleHandle = Triangle*;

class Triangle : public std::array<VertexHandle, 3>
{
public:
    /**
     * @brief Constructor of Triangle class.
     */
    Triangle();

    /**
     * @brief Constructor of Triangle class.
     *
     * @param points are the vertices that are used to define the triangle
     */
    explicit Triangle(std::array<VertexHandle, 3> points);

    /**
     * @brief Copy Constructor.
     *
     * @param otherTriangle to be copied
     */
    Triangle(const Triangle& otherTriangle);

    /**
     * @brief Destructor of Triangle class
     */
    ~Triangle();

    /**
     * @brief Checks if a vertex lies in the circumcircle of a triangle.
     *
     * @param vertex is the checked vertex
     * @return a boolean value which indicates if a vertex lies in the circumcircle of a triangle
     */
    [[nodiscard]] bool inCircleTest(const VertexHandle& vertex) const;

    /**
     * @brief Checks if a vertex is part of a triangle.
     *
     * @param vertex is the checked vertex
     * @return a boolean value which indicates if a vertex is part of a triangle.
     */
    [[nodiscard]] bool containsVertex(const VertexHandle& vertex) const;

public:
    #define vertices _M_elems
    size_t id;
};


#endif /* DELAUNAY_TRIANGULATION_TRIANGLE_HXX */
