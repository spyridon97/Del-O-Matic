/*
 * Filename:    Timer.cxx
 *
 * Description: Source file of Timer class.
 *
 * Author:      Spyridon Tsalikis
 * Created on   02/04/20.
 */

#include "Timer.hxx"


Timer::Timer() = default;

void Timer::startTimer()
{
    start = std::chrono::steady_clock::now();
}

void Timer::stopTimer()
{
    end = std::chrono::steady_clock::now();
}

double Timer::getSeconds()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
}
