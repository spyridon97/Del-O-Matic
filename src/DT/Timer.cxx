/*
 * Filename:    Timer.cxx
 *
 * Description: Source file of Timer class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   02/04/20.
 */

#include "Timer.hxx"


void Timer::startTimer()
{
    clock_gettime(CLOCK_MONOTONIC, &(this->firstSeconds));
}

void Timer::stopTimer()
{
    clock_gettime(CLOCK_MONOTONIC, &(this->secondSeconds));
}

double Timer::getSeconds()
{
    double nsecs_start = this->firstSeconds.tv_sec * 1000000000 + this->firstSeconds.tv_nsec;
    double nsecs_end = this->secondSeconds.tv_sec * 1000000000 + this->secondSeconds.tv_nsec;

    return (nsecs_end - nsecs_start) / 1000000000.0;
}
