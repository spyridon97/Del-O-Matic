/*
 * Filename:    DelaunayTriangulation.hxx
 *
 * Description: Header file of DelaunayTriangulation class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/1/20.
 */

#ifndef DELAUNAY_TRIANGULATION_DELAUNAY_TRIANGULATION
#define DELAUNAY_TRIANGULATION_DELAUNAY_TRIANGULATION


#include <vector>
#include "Edge.hxx"
#include "Mesh.hxx"
#include "Triangle.hxx"
#include "Timer.hxx"


class DelaunayTriangulation
{
public:
    /**
     * @brief Constructor of DelaunayTriangulation.
     */
    DelaunayTriangulation();

    /**
     * @brief Destructor of DelaunayTriangulation.
     */
    ~DelaunayTriangulation();

    /**
     * @brief Sets the input vertices of the triangulation.
     *
     * @param points are the input vertices
     */
    void setInputPoints(std::vector<Point>& points);

private:
    /**
     * @brief Create bounding Triangle
     */
    void createBoundingTriangle();

public:
    /**
     * @brief Generates the Delaunay Mesh of the input vertices
     */
    void generateMesh();

    /**
     * @brief Get outputMesh
     */
    Mesh getCleanMesh();

private:
    TriangleHandle boundingTriangle{};

    std::vector<TriangleHandle> triangles;
    std::vector<VertexHandle> vertices;
public:
    Timer computeBoundaryTriangleTimer{}, meshingTimer{}, computeMeshResultsTimer{};
};


#endif /* DELAUNAY_TRIANGULATION_DELAUNAY_TRIANGULATION */
