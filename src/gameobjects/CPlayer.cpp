/**
 * @author Jaroslav Fikar
 * 
*/


#include "CPlayer.h"

void CPlayer::HandleInput(const Uint8 *keyState)
{
    // moving
    if (keyState[this->m_Controls->m_Up])
    {
        this->m_MovingDirection = EDirection::DIRECTION_UP;
        this->m_ActualTexture = ETextureType ::TEXTURE_UP;
    }
    else if (keyState[this->m_Controls->m_Down])
    {
        this->m_MovingDirection = EDirection::DIRECTION_DOWN;
        this->m_ActualTexture = ETextureType ::TEXTURE_DOWN;
    }
    else if (keyState[this->m_Controls->m_Left])
    {
        this->m_MovingDirection = EDirection::DIRECTION_LEFT;
        this->m_ActualTexture = ETextureType ::TEXTURE_LEFT;
    }
    else if (keyState[this->m_Controls->m_Right])
    {
        this->m_MovingDirection = EDirection::DIRECTION_RIGHT;
        this->m_ActualTexture = ETextureType ::TEXTURE_RIGHT;
    }

    // actions
    if(keyState[this->m_Controls->m_PlaceBomb])
    {
        this->m_IsPlanting = true;
    }

    if(keyState[this->m_Controls->m_TriggerBomb])
    {
        this->m_IsDetonating = true;
    }
}

CPlayer::~CPlayer()
{
    delete this->m_Controls;
}
