/*
 * Filename:    DelaunayTriangulation.hxx
 *
 * Description: Header file of DelaunayTriangulation class.
 *
 * Author:      Spiros Tsalikis
 * Created on   4/1/20.
 */

#ifndef DELOMATIC_DELAUNAY_TRIANGULATION
#define DELOMATIC_DELAUNAY_TRIANGULATION


#include <vector>
#include "Mesh.hxx"
#include "Timer.hxx"
#include "Edge.hxx"
#include "HistoryDAG.hxx"


class DelaunayTriangulation : public HistoryDAG
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
    static void legalizeEdge(EdgeHandle& PiPj, const VertexHandle& Pr);

public:
    /**
     * @brief Generates the Delaunay Mesh of the input vertices
     */
    void generateMesh();

    /**
     * @brief Validates if the triangulation is Delaunay. Cost: O (n log n)
     */
    void validateDelaunayTriangulation();

    /**
     * @brief Gets outputMesh.
     */
    Mesh getOutputMesh();

private:
    std::vector<VertexHandle> meshVertices;
    std::vector<TriangleHandle> meshTriangles;
public:
    Timer computeBoundaryTriangleTimer{}, meshingTimer{}, validateDelaunayTriangulationTimer{};
};


#endif /* DELOMATIC_DELAUNAY_TRIANGULATION */
