/**
 * @author Jaroslav Fikar
 * 
*/


#include "CWindowManager.h"

bool CWindowManager::IsClosed() const
{
    // Check events
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        // Close window
        if (e.type == SDL_QUIT)
        {
            return true;
        }
    }

    return false;
}

EApplicationStatus CWindowManager::Run()
{
    // Did user close this window?
    if(this->IsClosed())
    {
        return EApplicationStatus ::APPLICATION_STATUS_EXIT;
    }

    // Tick event to update game clock
    this->m_Clock.Tick();

    // Check keyboard, mouse and program events.
    this->UpdateEvents();

    // Update manager
    this->Update(this->m_Clock.DeltaTime());

    // Draw manager output
    this->Draw();

    // Wait for few miliseconds to draw cca 60 frames per second
    this->m_Interface->Wait(this->m_Clock.GetDelay());

    return EApplicationStatus ::APPLICATON_STATUS_NONE;
}

