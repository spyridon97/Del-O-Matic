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


#include <vector>
#include "Triangle.hxx"

//                                [Triangle, id of edge]
using TrianglePair = std::pair<TriangleHandle, size_t>;

class Edge;

using EdgeHandle = Edge*;

class Edge
{
public:
    /**
     * @brief Constructor of Edge class.
     *
     * @param originVertexId is the id of the origin vertex of the edge
     * @param destinationVertexId is the id of the destination vertex of the edge
     */
    explicit Edge(int originVertexId, int destinationVertexId);

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
     * @brief Replaces an adjacent triangle we a new one.
     *
     * @param oldTriangle is the old adjacent triangle
     * @param newTriangleInfo is the new adjacent triangle along with its edge id
     */
    void replaceAdjacentTriangle(const TriangleHandle& oldTriangle, const TrianglePair& newTriangleInfo);

    /*
     * The following primitives are calculated with the following convention:
     * Given the following Edge PiPj (with this specific order) that will be DELETED, we can extract:
     * 1) the left triangle PiPjPr (with this specific order) and its information
     * 2) the right triangle PiPkPj (with this specific order) and its information
     *
     *
     *                                  Pk
     *                                  /\
     *                                 /  \
     *                                /    \
     *                             Pi--------Pj
     *                                \    /
     *                                 \  /
     *                                  \/
     *                                  Pr
     *
     * Before using the below primitives check Neighbors
     */

    void checkNeighbors(int apexVertexTriangleId);

    ////////////////////////////////////////////////////////////////
    //                 Left Triangle Primitives                   //
    ////////////////////////////////////////////////////////////////

    TriangleHandle getLeftTriangle();

    VertexHandle getOriginVertexLeftTriangle();

    VertexHandle getDestinationVertexLeftTriangle();

    VertexHandle getApexVertexLeftTriangle();

    EdgeHandle getOriginEdgeLeftTriangle();

    EdgeHandle getDestinationEdgeLeftTriangle();

    EdgeHandle getApexEdgeLeftTriangle();

    ////////////////////////////////////////////////////////////////
    //                Right Triangle Primitives                   //
    ////////////////////////////////////////////////////////////////

    TriangleHandle getRightTriangle();

    VertexHandle getOriginVertexRightTriangle();

    VertexHandle getDestinationVertexRightTriangle();

    VertexHandle getApexVertexRightTriangle();

    EdgeHandle getOriginEdgeRightTriangle();

    EdgeHandle getDestinationEdgeRightTriangle();

    EdgeHandle getApexEdgeRightTriangle();

    /**
     * @brief Checks if the edge is a boundary edge.
     *
     * @return a boolean value which indicates if the edge is a boundary edge.
     */
    [[nodiscard]] bool isBoundaryTriangle() const;

public:
    int originVertexId;
    int destinationVertexId;

    //  [Triangle, id of edge]
    std::vector<TrianglePair> adjacentTrianglesInfo;
};


#endif /* DELAUNAY_TRIANGULATION_EDGE_HXX */
