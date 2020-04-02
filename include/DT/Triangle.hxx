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


class Triangle
{
public:
    /**
     * @brief Constructor of Triangle class.
     */
    Triangle() = default;
    /**
     * @brief Constructor of Triangle class.
     *
     * @param points are the vertices that are used to define the triangle
     */
    explicit Triangle(std::array<VertexHandle, 3> points);

    /**
     * @brief Destructor of Triangle class
     */
    ~Triangle();

    /**
     * @brief Copy Constructor.
     *
     * @param otherTriangle to be copied
     */
    Triangle(const Triangle& otherTriangle);

    /**
     * @brief Gets a vertex of the Triangle.
     *
     * @param index is the index of the vertex of the Triangle that is requested
     * @return a vertex of the Triangle
     */
    [[nodiscard]] VertexHandle vertex(unsigned char index) const;

    /**
     * @brief Gets a vertex of the Triangle.
     *
     * @param index is the index of the vertex of the Triangle that is requested
     * @return a vertex of the Triangle
     */
    VertexHandle& vertex(unsigned char index);

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

private:
    std::array<VertexHandle, 3> vertices{};
public:
    bool isBad;
    size_t id;
};

using TriangleHandle = Triangle*;


#endif /* DELAUNAY_TRIANGULATION_TRIANGLE_HXX */
