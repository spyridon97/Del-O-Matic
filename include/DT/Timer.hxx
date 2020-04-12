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


#include <chrono>


class Timer
{
public:
    Timer();

    void startTimer();

    void stopTimer();

    double getSeconds();

public:
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
};


#endif /* DELAUNAY_TRIANGULATION_TIMER_HXX */
