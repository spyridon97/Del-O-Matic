/*
 * Filename:    Timer.cxx
 *
 * Description: Source file of Timer class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   02/04/20.
 */

#include "Timer.hxx"


void Timer::start_seconds_timer()
{
    clock_gettime(CLOCK_MONOTONIC, &(this->first_seconds));
}

void Timer::stop_seconds_timer()
{
    clock_gettime(CLOCK_MONOTONIC, &(this->second_seconds));
}

double Timer::get_seconds()
{
    double nsecs_start = this->first_seconds.tv_sec * 1000000000 + this->first_seconds.tv_nsec;
    double nsecs_end = this->second_seconds.tv_sec * 1000000000 + this->second_seconds.tv_nsec;

    return (nsecs_end - nsecs_start) / 1000000000.0;
}

double Timer::get_nanoseconds()
{
    double nsecs_start = this->first_seconds.tv_sec * 1000000000 + this->first_seconds.tv_nsec;
    double nsecs_end = this->second_seconds.tv_sec * 1000000000 + this->second_seconds.tv_nsec;

    return nsecs_end - nsecs_start;
}
