/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once


#include <SDL2/SDL.h>

class CClock
{
public:
    CClock()
    {
        this->Reset();
    }

    void Tick()
    {
        Uint32 currentTime = SDL_GetTicks();
        this->m_DeltaTime = currentTime - this->m_Last;

        this->m_Last = currentTime;
    }

    void Reset()
    {
        this->m_Last = SDL_GetTicks();
        this->m_DeltaTime = SDL_GetTicks();
    }

    int DeltaTime() const
    { return this->m_DeltaTime; }


protected:
    Uint32 m_Last;

    int m_DeltaTime;
};

//The application time based timer
class LTimer
{
public:
    //Initializes variables
    LTimer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    //The clock time when the timer started
    Uint32 mStartTicks;

    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;
};

