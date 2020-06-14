/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <stdint.h>
#include "Messages.h"

/** Clock which controls game refresh rate. */
class CGameClock
{
public:
    /**
     * Clock contrucktor.
     * @param requiredFPS How many times will be screen refreshed in 1 second?
     */
    CGameClock(int requiredFPS = 60)
            : m_TicksPerFrame(1000 / requiredFPS)
    { this->Reset(); }

    /**
     * Rerun clock status.
     */
    void Reset()
    {
        this->m_DeltaTime = 0;
        this->m_FPS = 0;
        this->m_LastTicks = SDL_GetTicks();
        this->m_FPSUpdateCounter = 0;
    }

    /**
     * Update clock status.
     * @throws std::runtime_error When program runs for more than ~49 days.
     */
    void Tick()
    {
        // Calculate deltaTime
        Uint32 currentTime = SDL_GetTicks();

        // Check ticks validity because tick value wraps if the program runs for more than ~49 days.
        if (currentTime >= UINT32_MAX - 100)
        { throw std::runtime_error(MESSAGE_CLOCK_OVERFLOW); }

        this->m_DeltaTime = static_cast<int>(currentTime - this->m_LastTicks);

        // Calculate every N milliseconds.
        if (this->m_DeltaTime != 0 && this->m_FPSUpdateCounter >= 250)
        {
            this->m_FPS = 1000.f / this->m_DeltaTime;
            this->m_FPSUpdateCounter = 0;
        }

        // Update lasticks value
        this->m_LastTicks = currentTime;

        // Increment FPS counter.
        this->m_FPSUpdateCounter += this->m_DeltaTime;
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
        Uint32 currentTicks = SDL_GetTicks();

        if (currentTicks - this->m_LastTicks < this->m_TicksPerFrame)
        { return static_cast<int>(this->m_TicksPerFrame - (currentTicks - this->m_LastTicks)); }

        return 0;
    }

protected:
    /** How many ticks sould take one frame to achieve the required FPS.*/
    unsigned int m_TicksPerFrame;
    Uint32 m_LastTicks, m_FPSUpdateCounter;

    int m_DeltaTime;
    double m_FPS;
};


