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

/*====================================================================================================================*/
void CPlayer::Update(CBoard *board, int deltaTime)
{
    //  std::cout << "dt: " <<  deltaTime << std::endl;

    this->HorizontalMove(board, deltaTime);
    this->VerticalMove(board, deltaTime);

    if (this->m_IsPlanting)
    {
        this->TryPlaceBomb(board);
    }

    /*  if(this->m_IsDetonating && this->m_RemoteExplosion){
          board.DetonateBombs(this);
      }*/

    this->m_IsDetonating = false;
    this->m_IsPlanting = false;
    this->m_MovingDirection = EDirection::DIRECTION_NONE;
    this->m_VerticalMovingDirection = EDirection::DIRECTION_NONE;
    this->m_HorizontalMovingDirection = EDirection::DIRECTION_NONE;
}

/*====================================================================================================================*/
void CPlayer::VerticalMove(CBoard *board, int deltaTime)
{
    CCoord oldLocation = this->m_Location;

    double fractPart, intpart;
    fractPart = modf(this->m_Location.m_X, &intpart);
    //std::cout << fractPart << std::endl;

    double val = (1 - this->m_Speed);

    switch (this->m_VerticalMovingDirection)
    {
        case EDirection::DIRECTION_UP:
            this->m_Location.m_Y -= this->m_Speed * deltaTime;
          /*  if(!this->LocationIsFree(board, CCoord(this->m_Location.m_X, this->m_Location.m_Y), CCoord(this->m_Location.m_X + val, this->m_Location.m_Y)))*/
                  if (!board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y), this->m_WallPass,
                              this->m_BombPass, this->m_FireImmunity) ||
           !board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y), this->m_WallPass,
                              this->m_BombPass, this->m_FireImmunity)
               )
            {
                this->m_Location = oldLocation;
            }
            break;
        case EDirection::DIRECTION_DOWN:
            this->m_Location.m_Y += this->m_Speed * deltaTime;

            if(!this->LocationIsFree(board, CCoord(this->m_Location.m_X, this->m_Location.m_Y + val), CCoord(this->m_Location.m_X + val, this->m_Location.m_Y + val)))
           /* if (!board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y + val), this->m_WallPass,
                                   this->m_BombPass, this->m_FireImmunity) ||
                !board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y + val), this->m_WallPass,
                                   this->m_BombPass, this->m_FireImmunity)
                    )*/
            {
                this->m_Location = oldLocation;
            }
            break;
    }
}

/*====================================================================================================================*/
void CPlayer::HorizontalMove(CBoard *board, int deltaTime)
{
    CCoord oldLocation = this->m_Location;
    double fractPart, intpart;
    fractPart = modf(this->m_Location.m_Y, &intpart);
    std::cout << fractPart << std::endl;

    double val = (1 - this->m_Speed);

    switch (this->m_HorizontalMovingDirection)
    {
        case EDirection::DIRECTION_LEFT:
            this->m_Location.m_X -= this->m_Speed * deltaTime;

            if(!this->LocationIsFree(board, CCoord(this->m_Location.m_X, this->m_Location.m_Y), CCoord(this->m_Location.m_X, this->m_Location.m_Y + val)))
            // Check collisions
           /* if (!board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y), this->m_WallPass,
                                   this->m_BombPass, this->m_FireImmunity) ||
                !board->IsPassable(CCoord(this->m_Location.m_X, this->m_Location.m_Y + val), this->m_WallPass,
                                   this->m_BombPass, this->m_FireImmunity)
                    )*/
            {
                this->m_Location = oldLocation;


                if ((fractPart >= 0.6) &&
                    board->IsPassable(CCoord(this->m_Location.m_X - 1, std::ceil(this->m_Location.m_Y)),
                                      this->m_WallPass, this->m_BombPass, this->m_FireImmunity))
                {
                    this->m_Location.m_Y = std::min(this->m_Location.m_Y + this->m_Speed * deltaTime,
                                                    std::ceil(this->m_Location.m_Y));

                } else if ((fractPart <= 0.4) &&
                           board->IsPassable(CCoord(this->m_Location.m_X - 1, std::floor(this->m_Location.m_Y)),
                                             this->m_WallPass, this->m_BombPass, this->m_FireImmunity))
                {
                    this->m_Location.m_Y = std::max(this->m_Location.m_Y - this->m_Speed * deltaTime,
                                                    std::floor(this->m_Location.m_Y));
                }
            }
            break;
        case EDirection::DIRECTION_RIGHT:
            this->m_Location.m_X += this->m_Speed * deltaTime;
            if(!this->LocationIsFree(board, CCoord(this->m_Location.m_X + val, this->m_Location.m_Y), CCoord(this->m_Location.m_X + val, this->m_Location.m_Y + val)))
            /*if (!board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y), this->m_WallPass,
                                   this->m_BombPass, this->m_FireImmunity) ||
                !board->IsPassable(CCoord(this->m_Location.m_X + val, this->m_Location.m_Y + val), this->m_WallPass,
                                   this->m_BombPass, this->m_FireImmunity)
                    )*/
            {
                this->m_Location = oldLocation;

                if ((fractPart >= 0.6) &&
                    board->IsPassable(CCoord(this->m_Location.m_X + 1, std::ceil(this->m_Location.m_Y)),
                                      this->m_WallPass, this->m_BombPass, this->m_FireImmunity))
                {
                    this->m_Location.m_Y = std::min(this->m_Location.m_Y + this->m_Speed * deltaTime,
                                                    std::ceil(this->m_Location.m_Y));

                } else if ((fractPart <= 0.4) &&
                           board->IsPassable(CCoord(this->m_Location.m_X + 1, std::floor(this->m_Location.m_Y)),
                                             this->m_WallPass, this->m_BombPass, this->m_FireImmunity))
                {
                    this->m_Location.m_Y = std::max(this->m_Location.m_Y - this->m_Speed * deltaTime,
                                                    std::floor(this->m_Location.m_Y));
                }
            }
            break;
    }
}

/*====================================================================================================================*/
void CPlayer::MoveLeft(CBoard *board, int deltaTime)
{

}

/*====================================================================================================================*/
void CPlayer::MoveRight(CBoard *board, int deltaTime)
{

}

/*====================================================================================================================*/
void CPlayer::MoveUp(CBoard *board, int deltaTime)
{

}

/*====================================================================================================================*/
void CPlayer::MoveDown(CBoard *board, int deltaTime)
{

}

/*====================================================================================================================*/
bool CPlayer::LocationIsFree(CBoard *board, CCoord p1, CCoord p2) const
{
    if (!board->IsPassable(p1, this->m_WallPass, this->m_BombPass, this->m_FireImmunity) ||
        !board->IsPassable(p2, this->m_WallPass, this->m_BombPass, this->m_FireImmunity))
    {
        return false;
    }

    return true;
}

/*====================================================================================================================*/
void CPlayer::HandleInput(const Uint8 *keyState)
{
    this->m_Input = keyState;
    // moving
    if (keyState[this->m_Controls->m_Up])
    {
        this->m_MovingDirection = EDirection::DIRECTION_UP;
        this->m_VerticalMovingDirection = EDirection::DIRECTION_UP;
        this->m_ActualTexture = ETextureType::TEXTURE_UP;
    } else if (keyState[this->m_Controls->m_Down])
    {
        this->m_MovingDirection = EDirection::DIRECTION_DOWN;
        this->m_VerticalMovingDirection = EDirection::DIRECTION_DOWN;
        this->m_ActualTexture = ETextureType::TEXTURE_DOWN;
    }

    if (keyState[this->m_Controls->m_Left])
    {
        this->m_MovingDirection = EDirection::DIRECTION_LEFT;
        this->m_HorizontalMovingDirection = EDirection::DIRECTION_LEFT;
        this->m_VerticalMovingDirection = EDirection::DIRECTION_NONE; // todo remove
        this->m_ActualTexture = ETextureType::TEXTURE_LEFT;
    } else if (keyState[this->m_Controls->m_Right])
    {
        this->m_MovingDirection = EDirection::DIRECTION_RIGHT;
        this->m_HorizontalMovingDirection = EDirection::DIRECTION_RIGHT;
        this->m_VerticalMovingDirection = EDirection::DIRECTION_NONE; // todo remove
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

/*====================================================================================================================*/
void CPlayer::TryPlaceBomb(CBoard *board)
{
    // TODO Po odchodu hráče z colliderboxu bomby se zapne detekce kolizí na bombě
    // TODO udělat kolize před trigger box
}











