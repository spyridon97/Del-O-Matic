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
#include "GeometricPredicates.hxx"
#include "Mesh.hxx"
#include "Timer.hxx"
#include "Edge.hxx"
#include "TrianglesDAG.hxx"


class DelaunayTriangulation : public TrianglesDAG
{
public:
    /**
     * @brief Constructor of DelaunayTriangulation.
     *
     * @param robustPredicates is a boolean value that indicates if robust predicates will be used
     */
    explicit DelaunayTriangulation(bool robustPredicates);

    /**
     * @brief Destructor of DelaunayTriangulation.
     */
    ~DelaunayTriangulation();

    /**
     * @brief Sets the input vertices of the triangulation.
     *
     * @param vertices are the input vertices
     */
    void setInputVertices(std::vector<Vertex>& vertices);

private:
    /**
     * @brief Creates bounding Triangle
     */
    void createBoundingTriangle();

    /**
     * @brief Legalizes an edge.
     *
     * @param PiPj is the edge that will be legalized
     * @param Pr is the vertex that will be checked if it is inside PiPjPk triangle
     */
    void legalizeEdge(EdgeHandle& PiPj, const VertexHandle& Pr);

public:
    /**
     * @brief Generates the Delaunay Mesh of the input vertices
     */
    void generateMesh();

    /**
     * @brief Validates if the triangulation is Delaunay. Cost: O (n log n)
     *
     * @param meshTriangles are the triangles that will be checked if they are Delaunay
     * @return a boolean value which indicates if the triangulation is Delaunay.
     */
    bool validateDelaunayTriangulation(const std::vector<TriangleHandle>& meshTriangles);

    /**
     * @brief Gets outputMesh.
     *
     * @param validateDelaunayProperty is a flag which checks if the triangulation is Delaunay
     */
    Mesh getCleanMesh(bool validateDelaunayProperty);

private:
    std::vector<VertexHandle> meshVertices;
public:
    Timer computeBoundaryTriangleTimer{}, meshingTimer{}, computeMeshResultsTimer{};
};


#endif /* DELAUNAY_TRIANGULATION_DELAUNAY_TRIANGULATION */
