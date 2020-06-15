/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <SDL2/SDL.h>
#include "CCoord.h"

/** Represents controls setup for a player */
class CInput
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
    CInput(SDL_Keycode up, SDL_Keycode down, SDL_Keycode left, SDL_Keycode right, SDL_Keycode placeBomb,
           SDL_Keycode detonation)
            : m_Up(up), m_Down(down), m_Left(left), m_Right(right), m_PlaceBomb(placeBomb), m_Detonation(detonation),
              m_PlantingAvaible(false), m_IsPlanting(false), m_DetonatingAvaible(false), m_IsDetonating(false),
              m_Movement()
    {}

    CInput(const CInput &other) = default;

    CInput &operator=(const CInput &other) = default;

    ~CInput() = default;

    /**
     * Update input.
     * @param deltaTime Delta time.
     */
    void Update(int deltaTime);

    /** NextLevel input.     */
    void Reset()
    {
        this->m_IsPlanting = this->m_IsDetonating = false;
        this->m_Movement = CCoord<>(0, 0);
    }

    bool IsPlanting() const
    { return this->m_IsPlanting; }

    bool IsDetonating() const
    { return this->m_IsDetonating; }

    CCoord<> GetMovement() const
    { return this->m_Movement; }
protected:
    SDL_Keycode m_Up, m_Down, m_Left, m_Right, m_PlaceBomb, m_Detonation;
    bool m_PlantingAvaible, m_IsPlanting, m_DetonatingAvaible, m_IsDetonating;
    CCoord<> m_Movement;
};

