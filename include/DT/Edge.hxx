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
#include "Vertex.hxx"


class Edge;

using EdgeHandle = Edge*;

class Edge
{
public:
    /**
     * @brief Constructor of Edge class.
     *
     * @param points are the vertices that are used to define the ege
     */
    explicit Edge(std::array<VertexHandle, 2> points);

    /**
     * @brief Destructor of Edge class
     */
    ~Edge();

    /**
     * @brief Copy Constructor.
     *
     * @param otherEdge to be copied
     */
    Edge(const Edge& otherEdge);

    /**
     * @brief Gets a vertex of the Edge.
     *
     * @param index is the index of the vertex of the edge that is requested
     * @return a vertex of the Edge
     */
    [[nodiscard]] VertexHandle vertex(unsigned char index) const;

    /**
     * @brief Gets a vertex of the Edge.
     *
     * @param index is the index of the vertex of the edge that is requested
     * @return a vertex of the Edge
     */
    VertexHandle& vertex(unsigned char index);

    /**
     * @brief Compares Edges.
     *
     * @return a boolean value which indicates if edges are the same
     */
    [[nodiscard]] bool isSame(const Edge& edge) const;

    /**
     * @brief Gets squared length of the Edge.
     *
     * @return squared length of the Edge
     */
    [[nodiscard]] double getSquaredLength() const;

private:
    std::array<VertexHandle, 2> vertices{};
public:
    bool isBad;
    size_t id;
};


#endif /* DELAUNAY_TRIANGULATION_EDGE_HXX */
