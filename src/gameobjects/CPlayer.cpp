/**
 * @author Jaroslav Fikar
 * 
*/


#include "CPlayer.h"
#include "../CBoard.h"

CPlayer::~CPlayer()
{
    delete this->m_Controls;
}

void CPlayer::Update(CBoard *board, int deltaTime)
{

    CCoord oldLocation = this->m_Location;
   //  std::cout << "dt: " <<  deltaTime << std::endl;
    // TODO přidat ošetření kolizí se zdí
    switch (this->m_MovingDirection){
        case EDirection::DIRECTION_UP:
            this->m_Location.m_Y -= this->m_Speed * deltaTime;
            break;
        case EDirection::DIRECTION_DOWN:
            this->m_Location.m_Y += this->m_Speed * deltaTime;
            break;
        case EDirection::DIRECTION_LEFT:
            this->m_Location.m_X -= this->m_Speed * deltaTime;
            break;
        case EDirection::DIRECTION_RIGHT:
            this->m_Location.m_X += this->m_Speed * deltaTime;
            break;
    }

    if(!board->IsPassable(this->m_Location, false, false, false)){
        this->m_Location = oldLocation;
    }

    if(this->m_IsPlanting){
        this->TryPlaceBomb(board);
    }

   /* if(this->m_IsDetonating && this->m_RemoteExplosion){
        board.DetonateBombs(this);
    }*/

    this->m_IsDetonating = false;
    this->m_IsPlanting = false;
    this->m_MovingDirection = EDirection::DIRECTION_NONE;
}

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

void CPlayer::TryPlaceBomb(CBoard *board)
{

}




