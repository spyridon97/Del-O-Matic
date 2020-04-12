/*
 * Filename:    TrianglesDAG.hxx
 * 
 * Description: Header file of TrianglesDAG class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/5/20.
 */

#ifndef DELAUNAY_TRIANGULATION_TRIANGLE_LOCATOR_DAG_HXX
#define DELAUNAY_TRIANGULATION_TRIANGLE_LOCATOR_DAG_HXX


#include "GeometricPredicates.hxx"
#include "Triangle.hxx"


class TrianglesDAG
{
public:
    /**
     * @brief Constructor of TrianglesDAG.
     */
    TrianglesDAG();

    /**
     * @brief Destructor of TrianglesDAG.
     */
    ~TrianglesDAG();

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
    [[nodiscard]] bool containsRootTriangleVertices(TriangleHandle triangle) const;

    /**
     * @brief Gets the triangles of the Delaunay Triangulation.
     * @note: this is a helper function of the public getTriangulation function.
     *
     * @param triangles is a vector that includes the triangles of the Delaunay Triangulation
     * @param triangle is the triangle whose children are checked in the recursion
     */
    void getTriangulation(std::vector<TriangleHandle>& triangles, TriangleHandle& triangle);

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
     * @brief Gets the triangles of the Delaunay Triangulation.
     *
     * @return the triangles of the Delaunay Triangulation
     */
    std::vector<TriangleHandle> getTriangulation();

private:
    TriangleHandle rootTriangle;
};


#endif /* DELAUNAY_TRIANGULATION_TRIANGLE_LOCATOR_DAG_HXX */
