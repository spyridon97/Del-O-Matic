/*
 * Filename:    Timer.hxx
 *
 * Description: Header file of Timer class.
 *
 * Author:      Spiros Tsalikis
 * Created on   02/04/20.
 */

#ifndef DELOMATIC_TIMER_HXX
#define DELOMATIC_TIMER_HXX


#include <chrono>


class Timer
{
public:
    /**
     * @brief Constructor of Timer.
     */
    Timer();

    /**
     * @brief Starts timer.
     */
    void startTimer();

    /**
     * @brief Stops timer.
     */
    void stopTimer();

    /**
     * @brief Gets total time in seconds.
     *
     * @return total time in seconds
     */
    double getSeconds();

private:
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
};


#endif /* DELOMATIC_TIMER_HXX */
