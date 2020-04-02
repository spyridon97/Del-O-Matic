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

    void startTimer();

    void stopTimer();

    double getSeconds();

public:
    struct timespec firstSeconds, secondSeconds;
};


#endif /* DELAUNAY_TRIANGULATION_TIMER_HXX */
