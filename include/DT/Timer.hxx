/*
 * Filename:    Timer.hxx
 *
 * Description: Header file of Timer class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   02/04/20.
 */

#ifndef DELAUNAY_TRIANGULATION_TIMER_HXX
#define DELAUNAY_TRIANGULATION_TIMER_HXX


#include <ctime>


class Timer
{
public:
    Timer() = default;;

    void start_seconds_timer();

    void stop_seconds_timer();

    double get_seconds();

    double get_nanoseconds();

public:
    struct timespec first_seconds, second_seconds;
};


#endif /* DELAUNAY_TRIANGULATION_TIMER_HXX */
