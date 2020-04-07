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
REAL orient2dfast(REAL* pa, REAL* pb, REAL* pc);
REAL incircle(REAL* pa, REAL* pb, REAL* pc, REAL* pd);
REAL incirclefast(REAL* pa, REAL* pb, REAL* pc, REAL* pd);
}

double (* orient2dTest)(REAL* pa, REAL* pb, REAL* pc);

double (* inCircleTest)(REAL* pa, REAL* pb, REAL* pc, REAL* pd);

namespace GeometricPredicates
{
    void initialize(bool robustPredicates)
    {
        exactinit();
        if (robustPredicates) {
            orient2dTest = orient2d;
            inCircleTest = incircle;
        } else {
            orient2dTest = orient2dfast;
            inCircleTest = incirclefast;
        }
    }

    bool inCircle(const TriangleHandle& triangle, const VertexHandle& vertex)
    {
        return inCircleTest(triangle->vertices[0]->coordinates,
                            triangle->vertices[1]->coordinates,
                            triangle->vertices[2]->coordinates,
                            vertex->coordinates) < 0;
    }

    bool inTriangle(const TriangleHandle& triangle, const VertexHandle& vertex, std::array<double, 3>& orientationTests)
    {
        orientationTests[0] = orient2dTest(triangle->vertices[0]->coordinates,
                                           triangle->vertices[1]->coordinates,
                                           vertex->coordinates);

        orientationTests[1] = orient2dTest(triangle->vertices[1]->coordinates,
                                           triangle->vertices[2]->coordinates,
                                           vertex->coordinates);

        orientationTests[2] = orient2dTest(triangle->vertices[2]->coordinates,
                                           triangle->vertices[0]->coordinates,
                                           vertex->coordinates);

        return orientationTests[0] <= 0 && orientationTests[1] <= 0 && orientationTests[2] <= 0;
    }
}