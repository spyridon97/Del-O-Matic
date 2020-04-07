/*
 * Filename:    GeometricPredicates.hxx
 * 
 * Description: Header file of GeometricPredicates class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/5/20.
 */

#ifndef DELAUNAY_TRIANGULATION_GEOMETRIC_PREDICATES_HXX
#define DELAUNAY_TRIANGULATION_GEOMETRIC_PREDICATES_HXX


#include "Triangle.hxx"


class GeometricPredicates
{
public:
    GeometricPredicates();

    /**
     * @brief Checks if a vertex lies inside the circumcircle of a triangle
     *
     * @param triangle is the triangle
     * @param vertex is the vertex
     * @return a boolean value which indicates if vertex d lies inside the circumcircle
     */
    bool inCircle(const TriangleHandle& triangle, const VertexHandle& vertex);

    /**
     * @brief Checks if vertex lies inside or on one of the edges of a triangle.
     *
     * @param triangle is the tested triangle
     * @param vertex is the tested vertex
     * @param orientationTests are the results of the orientation test of the triangle
     * @return if vertex lies inside or on one of the edges of a triangle
     */
    bool
    inTriangle(const TriangleHandle& triangle, const VertexHandle& vertex, std::array<double, 3>& orientationTests);
};


#endif /* DELAUNAY_TRIANGULATION_GEOMETRIC_PREDICATES_HXX */
