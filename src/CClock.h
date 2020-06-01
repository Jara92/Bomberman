/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <SDL2/SDL.h>
#include <iostream>

/**
 * Clock which controls game refresh rate.
 */
class CGameClock
{
public:
    /**
     * Clock contrucktor.
     * @param requiredFPS How many times will be screen refreshed in 1 second?
     */
    CGameClock(int requiredFPS = 60)
            : m_TicksPerFrame(1000 / requiredFPS)
    {
        this->Reset();
    }

    /**
     * Reset clock status.
     */
    void Reset()
    {
        this->m_DeltaTime = 0;
        this->m_FPS = 0;
    }

    /**
     * Update clock status.
     */
    void Tick()
    {
        // Calculate deltaTime
        Uint32 currentTime = SDL_GetTicks();
        this->m_DeltaTime = static_cast<int>(currentTime - this->m_LastTicks);

        // Calculate FPS
        if(this->m_DeltaTime != 0)
        {
            this->m_FPS = 1000.f / this->m_DeltaTime;
        }

        // Update lastticks value
        this->m_LastTicks = currentTime;
    }

    int DeltaTime() const
    { return this->m_DeltaTime; }

    int GetFPS() const
    { return this->m_FPS; }

    /**
     * Calculates the waiting time before rendering next frame.
     * @return Waiting time in miliseconds
     */
    int GetDelay() const
    {
        if (SDL_GetTicks() - this->m_LastTicks < this->m_TicksPerFrame)
        {
            return static_cast<int>(this->m_TicksPerFrame - (SDL_GetTicks() - this->m_LastTicks));
        }

        return 0;
    }

protected:
    int m_TicksPerFrame;
    Uint32 m_LastTicks;

    int m_DeltaTime;
    double m_FPS;
};


