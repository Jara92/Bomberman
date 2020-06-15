/**
 * @author Jaroslav Fikar
*/

#include "CInput.h"

void CInput::Update(int deltaTime)
{
    // NextLevel old input.
    this->m_IsDetonating = this->m_IsPlanting = false;
    this->m_Movement = CCoord<>(0, 0);

    // Read keyboard state
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    // movement
    if (keyState[this->m_Up])
    { this->m_Movement.m_Y = -1; }
    else if (keyState[this->m_Down])
    { this->m_Movement.m_Y = 1; }

    if (keyState[this->m_Left])
    { this->m_Movement.m_X = -1; }
    else if (keyState[this->m_Right])
    { this->m_Movement.m_X = 1; }

    // Planting action
    if (keyState[this->m_PlaceBomb] && this->m_PlantingAvaible)
    {
        this->m_IsPlanting = true;
        this->m_PlantingAvaible = false;
    }
        // Planting is not avaible until the button is released
    else if (!keyState[this->m_PlaceBomb])
    { this->m_PlantingAvaible = true; }

    // Detonating action
    if (keyState[this->m_Detonation] && this->m_DetonatingAvaible)
    {
        this->m_DetonatingAvaible = false;
        this->m_IsDetonating = true;
    } else if (keyState[this->m_Detonation] && this->m_IsDetonating && !this->m_DetonatingAvaible)
    { this->m_IsDetonating = false; }

        // Detonating is not avaible until the button is released
    else if (!keyState[this->m_Detonation])
    { this->m_DetonatingAvaible = true; }
}
