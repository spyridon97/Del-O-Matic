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


#include <vector>
#include "Edge.hxx"
#include "Vertex.hxx"


class Triangle;

using TriangleHandle = Triangle*;

class Triangle
{
public:
    /**
     * @brief Constructor of Triangle class.
     *
     * @param vertices are the vertices that are used to define the triangle
     */
    explicit Triangle(std::array<VertexHandle, 3> vertices);

    /**
     * @brief Copy Constructor of Triangle class.
     *
     * @param triangle is the triangle that will be copied
     */
    explicit Triangle(TriangleHandle& triangle);

    /**
     * @brief Destructor of Triangle class
     */
    ~Triangle();

    /**
     * @brief Sets the edges of the triangle.
     *
     * @param edges are the edge of the triangle
     */
    void setEdges(std::array<EdgeHandle, 3> edges);

    /**
     * @brief Checks if a vertex is part of a triangle.
     *
     * @param vertex is the checked vertex
     * @return a boolean value which indicates if a vertex is part of a triangle.
     */
    [[nodiscard]] bool containsVertex(const VertexHandle& vertex) const;

public:
    std::array<VertexHandle, 3> vertices;

    std::array<EdgeHandle, 3> edges;

    //  used by DAG
    std::vector<TriangleHandle> childrenTriangles;

    //  used by DAG to extract triangulation
    bool visitedTriangle;
};


#endif /* DELAUNAY_TRIANGULATION_TRIANGLE_HXX */
