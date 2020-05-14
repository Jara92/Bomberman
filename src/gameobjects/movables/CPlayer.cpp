/**
 * @author Jaroslav Fikar
 * 
*/


#include "CPlayer.h"
#include "../../CBoard.h"

CPlayer::~CPlayer()
{
    delete this->m_Controls;
}


void CPlayer::Update(CBoard *board, int deltaTime)
{
    CCoord oldLocation = this->m_Location;
    double val = (1 - this->m_Speed);
    double fractPart, intpart;
    //  std::cout << "dt: " <<  deltaTime << std::endl;
    // TODO přidat ošetření kolizí se zdí
    switch (this->m_MovingDirection)
    {
        case EDirection::DIRECTION_UP:
            fractPart = modf(this->m_Location.m_X, &intpart);
            std::cout << fractPart << std::endl;
           /* if (fractPart >= 0.75 || fractPart <= 0.25)
            {
                this->m_Location.m_X = round(this->m_Location.m_X);
            }*/
            this->m_Location.m_Y -= this->m_Speed * deltaTime;

            if (!board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y), false, false, false) ||
                !board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y), false, false, false)
                    )
            {
                this->m_Location = oldLocation;
            }

            break;
        case EDirection::DIRECTION_DOWN:
            fractPart = modf(this->m_Location.m_X, &intpart);
            std::cout << fractPart << std::endl;
          /*  if (fractPart >= 0.75 || fractPart <= 0.25)
            {
                this->m_Location.m_X = round(this->m_Location.m_X);
            }*/
            this->m_Location.m_Y += this->m_Speed * deltaTime;

            if (!board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y + val), false, false, false) ||
                !board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y + val), false, false, false)
                    )
            {
                this->m_Location = oldLocation;
            }
            break;
        case EDirection::DIRECTION_LEFT:
            fractPart = modf(this->m_Location.m_Y, &intpart);
            std::cout << fractPart << std::endl;
           /* if ((fractPart >= 0.75 || fractPart <= 0.25))
            {
                this->m_Location.m_Y = round(this->m_Location.m_Y);
            }*/
            this->m_Location.m_Y = round(this->m_Location.m_Y);
            this->m_Location.m_X -= this->m_Speed * deltaTime;

            if (!board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y), false, false, false) ||
                !board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y + val), false, false, false)
                    )
            {
                this->m_Location = oldLocation;
            }
            break;
        case EDirection::DIRECTION_RIGHT:
            fractPart = modf(this->m_Location.m_Y, &intpart);
            std::cout << fractPart << std::endl;
            /*if (fractPart >= 0.75 || fractPart <= 0.25)
            {
                this->m_Location.m_Y = round(this->m_Location.m_Y);
            }*/
            this->m_Location.m_X += this->m_Speed * deltaTime;

            if (!board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y), false, false, false) ||
                !board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y + val), false, false, false)
                    )
            {
                this->m_Location = oldLocation;
            }
            break;
    }

    if (this->m_IsPlanting)
    {
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
    this->m_Input = keyState;
    // moving
    if (keyState[this->m_Controls->m_Up])
    {
        this->m_MovingDirection = EDirection::DIRECTION_UP;
        this->m_ActualTexture = ETextureType::TEXTURE_UP;
    } else if (keyState[this->m_Controls->m_Down])
    {
        this->m_MovingDirection = EDirection::DIRECTION_DOWN;
        this->m_ActualTexture = ETextureType::TEXTURE_DOWN;
    }

    if (keyState[this->m_Controls->m_Left])
    {
        this->m_MovingDirection = EDirection::DIRECTION_LEFT;
        this->m_ActualTexture = ETextureType::TEXTURE_LEFT;
    } else if (keyState[this->m_Controls->m_Right])
    {
        this->m_MovingDirection = EDirection::DIRECTION_RIGHT;
        this->m_ActualTexture = ETextureType::TEXTURE_RIGHT;
    }

    // actions
    if (keyState[this->m_Controls->m_PlaceBomb])
    {
        this->m_IsPlanting = true;
    }

    if (keyState[this->m_Controls->m_TriggerBomb])
    {
        this->m_IsDetonating = true;
    }
}

void CPlayer::TryPlaceBomb(CBoard *board)
{
    // TODO Po odchodu hráče z colliderboxu bomby se zapne detekce kolizí na bombě
}




