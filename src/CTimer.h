/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <iostream>
#include <functional>

class CTimer
{
public:
    /**
     * Timer constructor. Timer is not running until Run() method is called.
     * @param value Value to be counted.
     * @param callBack Callback function which will be called when the timer is done.
     */
    CTimer(unsigned int value = 0, std::function<void(void)> callBack = {})
            : m_ActualTime(0), m_TargetTime(value), m_IsOn(false), m_CallBackCalled(std::move(callBack))
    {}

    /**
     * Coutdown the timer.
     * @param deltaTime Deltatime
     * @return True - timer is done.
     */
    bool Tick(int deltaTime)
    {
        if (this->m_IsOn)
        { this->m_ActualTime += deltaTime; }

        bool done = this->Done();

        // We want to call callback just once.
        if (done && !m_CallBackCalled)
        {
            this->m_CallBackCalled = true;
            if (this->m_Callback)
            { this->m_Callback(); }
        }
        return done;
    }

    /**
     * Is this timer done?
     * @return True - timer is done
     */
    bool Done() const
    { return (this->m_ActualTime >= this->m_TargetTime); }

    /** Run counter again with same parameters. */
    void Reset()
    {
        this->m_IsOn = true;
        this->m_CallBackCalled = false;

        this->m_ActualTime = 0;
    }

    /** Start the timer using the existing parameters. */
    void Run()
    { this->Run(this->m_TargetTime, this->m_Callback); }

    void Run(unsigned int value)
    { this->Run(value, this->m_Callback); }

    /**
     * Turn on timer countdown.
     * @param value Value to be counted.
     * @param callBack Callback function which will be called when the timer is done.
     */
    void Run(unsigned int value, std::function<void(void)> callBack)
    {
        this->m_IsOn = true;
        this->m_ActualTime = 0;
        this->m_TargetTime = value;
        this->m_Callback = std::move(callBack);
        this->m_CallBackCalled = false;
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
     * @return Remaining time in milliseconds.
     */
    int GetRemainingTime() const
    { return ((this->m_TargetTime > this->m_ActualTime) ? (this->m_TargetTime - this->m_ActualTime) : 0); }

protected:
    unsigned int m_ActualTime, m_TargetTime;
    bool m_IsOn;
    bool m_CallBackCalled;

    std::function<void(void)> m_Callback;
};

