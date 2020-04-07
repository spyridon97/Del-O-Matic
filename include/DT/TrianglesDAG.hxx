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
    TrianglesDAG();

    ~TrianglesDAG();

    void setRootTriangle(TriangleHandle triangle);

private:
    TriangleHandle locateTriangle(TriangleHandle triangle, VertexHandle vertex,
                                  std::array<double, 3>& orientationTests);

    void getTriangulation(std::vector<TriangleHandle>& triangles, TriangleHandle& triangle);

    [[nodiscard]] bool containsRootTriangleVertices(TriangleHandle triangle) const;

public:
    TriangleHandle locateTriangle(VertexHandle vertex, std::array<double, 3>& orientationTests);

    std::vector<TriangleHandle> getTriangulation();

private:
    TriangleHandle rootTriangle;
protected:
    GeometricPredicates predicates;
};


#endif /* DELAUNAY_TRIANGULATION_TRIANGLE_LOCATOR_DAG_HXX */
