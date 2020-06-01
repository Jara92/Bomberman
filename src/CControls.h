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
    /**
     * Settings constructor.
     * @param up Move up button.
     * @param down Move down button.
     * @param left Move left button.
     * @param right Move right button.
     * @param placeBomb Place bomb action button.
     * @param detonation Bomb detonation action button
     */
    CControls(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right, SDL_Keycode placeBomb, SDL_Keycode detonation)
    : m_Up(up), m_Down(down), m_Left(left), m_Right(right), m_PlaceBomb(placeBomb), m_Detonation(detonation)
    {}
    CControls(const CControls & other) = default;
    CControls &operator = (const CControls & other) = default;
    ~CControls() = default;

    SDL_Keycode m_Up;
    SDL_Keycode m_Down;
    SDL_Keycode m_Left;
    SDL_Keycode m_Right;
    SDL_Keycode m_PlaceBomb;
    SDL_Keycode m_Detonation;
};

