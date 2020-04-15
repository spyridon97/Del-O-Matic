/*
 * Filename:    Edge.hxx
 * 
 * Description: Header file of Edge class.
 *
 * Author:      Spiros Tsalikis
 * Created on   4/2/20.
 */

#ifndef DELOMATIC_EDGE_HXX
#define DELOMATIC_EDGE_HXX


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
     * @note It also determines which triangle is on the left and on the right respectively.
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

    /**
     * @brief Determines which adjacent triangle is on the left and on the right respectively.
     *
     * @param apexVertexLeftTriangleId is the id of the apex Vertex (Pr) of the left triangle
     */
    void determineAdjacentTriangles(int apexVertexLeftTriangleId);

    ////////////////////////////////////////////////////////////////
    //                 Left Triangle Primitives                   //
    ////////////////////////////////////////////////////////////////

    /**
     * @brief Gets left triangle.
     *
     * @return left triangle
     */
    TriangleHandle getLeftTriangle();

    /**
     * @brief Gets origin vertex of left triangle (Pi).
     *
     * @return origin vertex of left triangle
     */
    VertexHandle getOriginVertexLeftTriangle();

    /**
     * @brief Gets destination vertex of left triangle (Pj).
     *
     * @return destination vertex of left triangle
     */
    VertexHandle getDestinationVertexLeftTriangle();

    /**
     * @brief Gets apex vertex of left triangle (Pr).
     *
     * @return apex vertex of left triangle
     */
    VertexHandle getApexVertexLeftTriangle();

    /**
     * @brief Gets origin edge of left triangle (PiPj).
     *
     * @return origin edge of left triangle
     */
    EdgeHandle getOriginEdgeLeftTriangle();

    /**
     * @brief Gets destination edge of left triangle (PjPr).
     *
     * @return destination edge of left triangle
     */
    EdgeHandle getDestinationEdgeLeftTriangle();

    /**
     * @brief Gets apex edge of left triangle (PrPi).
     *
     * @return apex edge of left triangle
     */
    EdgeHandle getApexEdgeLeftTriangle();

    ////////////////////////////////////////////////////////////////
    //                Right Triangle Primitives                   //
    ////////////////////////////////////////////////////////////////

    /**
     * @brief Gets right triangle (PiPkPj).
     *
     * @return right triangle
     */
    TriangleHandle getRightTriangle();

    /**
     * @brief Gets origin vertex of right triangle (Pi).
     *
     * @return origin vertex of right triangle
     */
    VertexHandle getOriginVertexRightTriangle();

    /**
     * @brief Gets destination vertex of right triangle (Pk).
     *
     * @return destination vertex of right triangle
     */
    VertexHandle getDestinationVertexRightTriangle();

    /**
     * @brief Gets apex vertex of right triangle (Pj).
     *
     * @return apex vertex of right triangle
     */
    VertexHandle getApexVertexRightTriangle();

    /**
     * @brief Gets origin edge of right triangle (PiPK).
     *
     * @return origin edge of right triangle
     */
    EdgeHandle getOriginEdgeRightTriangle();

    /**
     * @brief Gets destination edge of right triangle (PkPj).
     *
     * @return destination edge of right triangle
     */
    EdgeHandle getDestinationEdgeRightTriangle();

    /**
     * @brief Gets apex edge of right triangle (PiPj).
     *
     * @return apex edge of right triangle
     */
    EdgeHandle getApexEdgeRightTriangle();

    /**
     * @brief Checks if the edge is a boundary edge.
     *
     * @return a boolean value which indicates if the edge is a boundary edge
     */
    [[nodiscard]] bool isBoundaryEdge() const;

private:
    //  variable that saves the orientation of the edge
    bool correctOrientation;

    //  [Triangle,   id of edge of triangle]
    std::vector<TrianglePair> adjacentTrianglesInfo;
};


#endif /* DELOMATIC_EDGE_HXX */
