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

