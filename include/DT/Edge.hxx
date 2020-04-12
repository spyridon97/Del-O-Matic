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


//                            [Triangle,   id of edge of triangle]
using TrianglePair = std::pair<TriangleHandle, unsigned char>;

/**
 * @brief This class is a place holder for adjacent Triangles.
 */
class Edge
{
public:
    /**
     * @brief Constructor of Edge class.
     */
    Edge();

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
     * @brief Replaces an adjacent triangle with a new one.
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
     *                               /      \
     *                              /        \
     *                             /          \
     *                            /            \
     *                           /              \
     *                        Pi ---------------- Pj
     *                            \            /
     *                             \          /
     *                              \        /
     *                               \      /
     *                                \    /
     *                                 \  /
     *                                  \/
     *                                  Pr
     *
     * Before using the below primitives, either determine adjacent Triangles of PiPj edge against Pr vertex
     * or use replaceAdjacentTriangle if needed.
     */

    void determineAdjacentTriangles(int apexVertexLeftTriangleId);

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
     * @return a boolean value which indicates if the edge is a boundary edge
     */
    [[nodiscard]] bool isBoundaryEdge() const;

private:
    unsigned char leftTriangleId;
    unsigned char rightTriangleId;

    //  [Triangle,   id of edge of triangle]
    std::vector<TrianglePair> adjacentTrianglesInfo;
};


#endif /* DELAUNAY_TRIANGULATION_EDGE_HXX */
