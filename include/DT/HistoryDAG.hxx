/*
 * Filename:    HistoryDAG.hxx
 * 
 * Description: Header file of HistoryDAG class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/5/20.
 */

#ifndef DELAUNAY_TRIANGULATION_HISTORY_DAG_HXX
#define DELAUNAY_TRIANGULATION_HISTORY_DAG_HXX


#include "Edge.hxx"
#include "GeometricPredicates.hxx"


class HistoryDAG
{
public:
    /**
     * @brief Constructor of HistoryDAG.
     */
    HistoryDAG();

    /**
     * @brief Destructor of HistoryDAG.
     */
    ~HistoryDAG();

    /**
     * @brief Sets the root triangle of the DAG.
     *
     * @param triangle is the triangle that will be set as the root
     */
    void setRootTriangle(TriangleHandle& triangle);

private:
    /**
     * @brief Locates a triangle that contains the given vertex.
     * @note: this function is a helper of the public locateTriangle function.
     *
     * @param triangle is the triangle whose children are checked in the recursion
     * @param vertex is the given vertex based on which we locate a triangle
     * @param orientationTests are the results of the orientation tests that are use in the inTriangle function
     * @return the triangle that contains the given vertex
     */
    static TriangleHandle& locateTriangle(TriangleHandle& triangle, VertexHandle vertex,
                                          std::array<double, 3>& orientationTests);

    /**
     * @brief Checks if a triangle contains the vertices of the root triangle.
     *
     * @param triangle is the triangle that is checked
     * @return a boolean value which indicates if a triangle contains the vertices of the root triangle
     */
    [[nodiscard]] bool containsBoundingTriangleVertices(TriangleHandle triangle) const;

    /**
     * @brief Extracts the triangles of the Delaunay Triangulation without the bounding triangle.
     * @note: this is a helper function of the public extractTriangulationWithoutBoundingTriangle function.
     *
     * @param triangles is a vector that includes the triangles of the Delaunay Triangulation
     * @param triangle is the triangle whose children are checked in the recursion
     */
    void extractTriangulationWithoutBoundingTriangle(std::vector<TriangleHandle>& triangles, TriangleHandle& triangle);

public:
    /**
     * @brief Locates a triangle that contains the given vertex.
     *
     * @param vertex is the given vertex based on which we locate a triangle
     * @param orientationTests are the results of the orientation tests that are use in the inTriangle function
     * @return the triangle that contains the given vertex
     */
    TriangleHandle& locateTriangle(VertexHandle vertex, std::array<double, 3>& orientationTests);

    /**
     * @brief Extracts the triangles of the Delaunay Triangulation without the bounding triangle.
     *
     * @return the triangles of the Delaunay Triangulation
     */
    std::vector<TriangleHandle> extractTriangulationWithoutBoundingTriangle();

private:
    TriangleHandle rootTriangle;
};


#endif /* DELAUNAY_TRIANGULATION_HISTORY_DAG_HXX */
