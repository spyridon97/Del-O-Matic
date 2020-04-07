/*
 * Filename:    GeometricPredicates.cxx
 * 
 * Description: Source file of GeometricPredicates class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   4/5/20.
 */

#include "GeometricPredicates.hxx"


extern "C" {
#define REAL double
void exactinit();
REAL orient2d(REAL* pa, REAL* pb, REAL* pc);
REAL incircle(REAL* pa, REAL* pb, REAL* pc, REAL* pd);
}

GeometricPredicates::GeometricPredicates()
{
    exactinit();
}

bool GeometricPredicates::inCircle(const TriangleHandle& triangle, const VertexHandle& vertex)
{
    return incircle(triangle->vertices[0]->coordinates,
                    triangle->vertices[1]->coordinates,
                    triangle->vertices[2]->coordinates,
                    vertex->coordinates) < 0;
}

bool GeometricPredicates::inTriangle(const TriangleHandle& triangle, const VertexHandle& vertex,
                                     std::array<double, 3>& orientationTests)
{
    orientationTests[0] = orient2d(triangle->vertices[0]->coordinates,
                                   triangle->vertices[1]->coordinates,
                                   vertex->coordinates);

    orientationTests[1] = orient2d(triangle->vertices[1]->coordinates,
                                   triangle->vertices[2]->coordinates,
                                   vertex->coordinates);

    orientationTests[2] = orient2d(triangle->vertices[2]->coordinates,
                                   triangle->vertices[0]->coordinates,
                                   vertex->coordinates);

    return orientationTests[0] <= 0 && orientationTests[1] <= 0 && orientationTests[2] <= 0;
}
