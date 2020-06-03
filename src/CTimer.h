/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

/**
 * Counter.
 */
class CTimer
{
public:
    /**
     * Constructor.
     * @param initValue Time in millisecond.
     */
    CTimer(int initValue)
    :m_Time(initValue)
    {}

    /**
     * Coutdown the timer.
     * @param deltaTime Deltatime
     * @return True - timer is done.
     */
    bool Tick(int deltaTime)
    {
        this->m_Time -= deltaTime;
        return this->Done();
    }

    /**
     * Is this timer done?
     * @return True - timer is done
     */
    bool Done() const
    {return (this->m_Time <= 0);}

    /**
     * Reset counter.
     * @param initValue  Time in millisecond.
     */
    void Reset(int initValue = 0)
    {
        if(initValue == 0)
        {
            initValue = this->m_InitTime;
        }
        else
        {
            this->m_InitTime = initValue;
        }

        this->m_Time = initValue;
    }

protected:
    int m_Time;
    int m_InitTime;
};

