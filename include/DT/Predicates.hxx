/*
 * Filename:    Predicates.hxx
 *
 * Description: Header file of Predicates.
 *
 * Author:      Spyridon Tsalikis
 * Created on   02/04/20.
 */

#ifndef DELAUNAY_TRIANGULATION_PREDICATES_HXX
#define DELAUNAY_TRIANGULATION_PREDICATES_HXX

extern "C" {
#define REAL double
void exactinit();
REAL orient2d(REAL* pa, REAL* pb, REAL* pc);
REAL incircle(REAL* pa, REAL* pb, REAL* pc, REAL* pd);
}

#endif /* DELAUNAY_TRIANGULATION_PREDICATES_HXX */
