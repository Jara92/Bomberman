/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <functional>

/**
 * Counter.
 */
class CTimer
{
public:
    /**
     * Constructor.
     */
    CTimer()
            : m_Time(0), m_InitTime(0), m_IsOn(false)
    {}

    /**
     * Coutdown the timer.
     * @param deltaTime Deltatime
     * @return True - timer is done.
     */
    bool Tick(int deltaTime)
    {
        if (this->m_IsOn)
        { this->m_Time -= deltaTime; }

        bool done = this->Done();

        if (done && this->m_Callback)
        { this->m_Callback(); }

        return done;
    }

    /**
     * Is this timer done?
     * @return True - timer is done
     */
    bool Done() const
    { return (this->m_Time <= 0); }

    /**
     * Run counter again with same parameters.
     * @param initValue  Time in millisecond.
     */
    void Rerun(int initValue = 0)
    {
        this->m_IsOn = true;

        if (initValue == 0)
        { initValue = this->m_InitTime; }
        else
        { this->m_InitTime = initValue; }

        this->m_Time = initValue;
    }

    /**
     * Turn on timer countdown.
     * @param value Value to be counted.
     * @param callBack Callback function which will be called when the timer is done.
     */
    void Run(int value, std::function<void(void)> callBack = {})
    {
        this->m_IsOn = true;
        this->m_Time = this->m_InitTime = value;
        this->m_Callback = std::move(callBack);
    }

    /**
     * Turn off timer.
     */
    void Stop()
    { this->m_IsOn = false; }

    /**
     * Turn on timer.
     */
    void Continue()
    { this->m_IsOn = true; }

    /**
     * Is this timer running?
     * @return True - running
     */
    bool IsOn() const
    { return this->m_IsOn; }

    /**
     * Get remaining time to be counted.
     * @return Time in milliseconds.
     */
    int GetRemainingTime() const
    { return std::max(0, this->m_Time); }

    std::function<void(void)> GetCallback() const
    { return this->m_Callback; }

protected:
    int m_Time, m_InitTime;
    bool m_IsOn;

    std::function<void(void)> m_Callback;
};

