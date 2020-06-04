/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>

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
            : m_Time(0), m_InitTime(0), m_IsRunning(false)
    {}

    /**
     * Coutdown the timer.
     * @param deltaTime Deltatime
     * @return True - timer is done.
     */
    bool Tick(int deltaTime)
    {
        if (this->m_IsRunning)
        { this->m_Time -= deltaTime; }
        return this->Done();
    }

    /**
     * Is this timer done?
     * @return True - timer is done
     */
    bool Done() const
    { return (this->m_IsRunning && this->m_Time <= 0); }

    /**
     * Rerun counter.
     * @param initValue  Time in millisecond.
     */
    void Rerun(int initValue = 0)
    {
        this->m_IsRunning = true;

        if (initValue == 0)
        {
            initValue = this->m_InitTime;
        } else
        {
            this->m_InitTime = initValue;
        }

        this->m_Time = initValue;
    }

    void Run(int value)
    {this->m_IsRunning = true;
    this->m_Time = this->m_InitTime = value;}

    void Stop()
    {this->m_IsRunning = false;}

    bool IsRunning() const
    {return this->m_IsRunning;}

    int GetRemainingTime() const
    {return std::max(0,this->m_Time);}


protected:
    int m_Time;
    int m_InitTime;
    bool m_IsRunning;
};

