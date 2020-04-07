/*
 * Filename:    Edge.hxx
 * 
 * Description: Header file of Edge class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/2/20.
 */

#ifndef DELAUNAY_TRIANGULATION_EDGE_HXX
#define DELAUNAY_TRIANGULATION_EDGE_HXX


#include <cmath>
#include <vector>
#include "Vertex.hxx"


class Triangle;

using TriangleHandle = Triangle*;

using TrianglePair = std::pair<TriangleHandle, size_t>;

class Edge;

using EdgeHandle = Edge*;

class Edge
{
public:
    /**
     * @brief Constructor of Edge class.
     *
     * @param verticesIds are the vertices that are used to define the edge
     */
    explicit Edge(std::array<int, 2> verticesIds);

    /**
     * @brief Destructor of Edge class
     */
    ~Edge();

    /**
     * @brief Adds an adjacent triangle of the edge.
     *
     * @param adjacentTriangleWithEdgeId is the adjacent triangle along with it edgeId
     */
    void addAdjacentTriangle(TrianglePair adjacentTriangleWithEdgeId);

    /**
     * @brief Removes an adjacent triangle of the edge.
     *
     * @param triangle is the adjacent triangle
     */
    void removeAdjacentTriangle(const TriangleHandle& triangle);

    /**
     * @brief Finds the adjacent triangle of a triangle.
     *
     * @param triangle is the triangle that we trying to find its neighbor
     * @return the adjacent triangle along the given edge and its edge id
     */
    TrianglePair getAdjacentTriangle(const TriangleHandle& triangle);

    /**
     * @brief Compares Edges.
     *
     * @return a boolean value which indicates if edges are the same
     */
    [[nodiscard]] bool isSame(const Edge& edge) const;

    /**
     * @brief Gets number of adjacentTriangles.
     * @return number of adjacentTriangles
     */
    [[nodiscard]] size_t getNumberOfAdjacentTriangles() const;

public:
    std::array<int, 2> verticesIds;

    size_t id;
public:
    std::vector<std::pair<TriangleHandle, size_t>> adjacentTrianglesWithEdgeIds;
};


#endif /* DELAUNAY_TRIANGULATION_EDGE_HXX */
