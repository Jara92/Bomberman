/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <SDL2/SDL.h>

/**
 * Represents controls setup for a player
 */
class CControls
{
public:
    CControls(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right, SDL_Keycode placeBomb, SDL_Keycode triggerBomb)
    : m_Up(up), m_Down(down), m_Left(left), m_Right(right), m_PlaceBomb(placeBomb), m_TriggerBomb(triggerBomb)
    {}
    // I dont want to allow copying this objekt because it should be unique (2 players should not have the same controls)
    CControls(const CControls & other) = delete;
    CControls &operator = (const CControls & other) = delete;
    ~CControls() = default;

    SDL_Keycode m_Up;
    SDL_Keycode m_Down;
    SDL_Keycode m_Left;
    SDL_Keycode m_Right;
    SDL_Keycode m_PlaceBomb;
    SDL_Keycode m_TriggerBomb;
};

