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

class Edge : public std::array<VertexHandle, 2>
{
public:
    /**
     * @brief Constructor of Edge class.
     *
     * @param points are the vertices that are used to define the ege
     */
    explicit Edge(std::array<VertexHandle, 2> points);

    /**
     * @brief Copy Constructor.
     *
     * @param otherEdge to be copied
     */
    Edge(const Edge& otherEdge);

    /**
     * @brief Destructor of Edge class
     */
    ~Edge();

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

public:
    #define vertices _M_elems

    bool isBad;
    size_t id;
};


#endif /* DELAUNAY_TRIANGULATION_EDGE_HXX */
