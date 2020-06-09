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
    CMovable::Update(board, deltaTime);
    //this->Animate(deltaTime);

    // Movement in vertical and horizontal axis
    this->HorizontalMove(board, deltaTime);
    this->VerticalMove(board, deltaTime);

    // Plating action
    if (this->m_IsPlanting)
    { this->TryPlaceBomb(board); }

    // Detonation action
    if (this->m_IsDetonating && this->m_DetanatingAvaible && this->m_RemoteExplosion)
    {
        this->m_DetanatingAvaible = false;
        board->DetonateBombs(this);
    }

    // Clean input
    this->m_IsDetonating = false;
    this->m_IsPlanting = false;
    this->m_VerticalMovingDirection = EDirection::DIRECTION_NONE;
    this->m_HorizontalMovingDirection = EDirection::DIRECTION_NONE;
}

/*====================================================================================================================*/
void CPlayer::VerticalMove(CBoard *board, int deltaTime)
{
    // Save old location
    CCoord<> oldLocation = this->m_Location;

    // Move
    this->m_Location.m_Y += (this->m_Speed * static_cast<int>(this->m_VerticalMovingDirection)) * deltaTime;
    //std::cout << "Step size " << (this->m_Speed * static_cast<int>(this->m_VerticalMovingDirection)) * deltaTime << std::endl;

    // Check collisions
    if (!this->LocationIsFree(board))
    {
        // Set old location
        this->m_Location = oldLocation;

        // Try center horizontal position if horizontal direction is none
        // This handles problems with turning. When the player is close to turn I will try to center his position to allow him turn this direction.
        if (m_HorizontalMovingDirection == EDirection::DIRECTION_NONE)
        { this->HorizontalCenter(board, deltaTime, static_cast<int>(this->m_VerticalMovingDirection)); }
    }
}

/*====================================================================================================================*/
void CPlayer::HorizontalMove(CBoard *board, int deltaTime)
{
    // Save old location
    CCoord<> oldLocation = this->m_Location;

    // Move
    this->m_Location.m_X += (this->m_Speed * static_cast<int>(this->m_HorizontalMovingDirection)) * deltaTime;

    // Check collisions
    if (!this->LocationIsFree(board))
    {
        // Set old location
        this->m_Location = oldLocation;

        // Try center horizontal position if horizontal direction is none
        // This handles problems with turning. When the player is close to turn I will try to center his position to allow him turn this direction.
        if (m_VerticalMovingDirection == EDirection::DIRECTION_NONE)
        { this->VerticalCenter(board, deltaTime, static_cast<int>(this->m_HorizontalMovingDirection)); }
    }
}

/*====================================================================================================================*/
void CPlayer::VerticalCenter(CBoard *board, int deltaTime, int direction)
{
    // Get decimal part of m_Location.m_Y
    double decPart, intpart;
    decPart = modf(this->m_Location.m_Y, &intpart);

    if ((decPart >= CPlayer::MIN_TURNING_VALUE) &&
        board->IsPassable(CCoord<unsigned int>(this->m_Location.m_X + direction, std::ceil(this->m_Location.m_Y)),
                          this))
    {
        this->m_Location.m_Y = std::min(this->m_Location.m_Y + this->m_Speed * deltaTime,
                                        std::ceil(this->m_Location.m_Y));

    }
        // TODO comment this
    else if ((decPart <= CPlayer::MAX_TURNING_VALUE) &&
             board->IsPassable(CCoord<unsigned int>(this->m_Location.m_X + direction, std::floor(this->m_Location.m_Y)),
                               this))
    {
        this->m_Location.m_Y = std::max(this->m_Location.m_Y - this->m_Speed * deltaTime,
                                        std::floor(this->m_Location.m_Y));
    }
}

/*====================================================================================================================*/
void CPlayer::HorizontalCenter(CBoard *board, int deltaTime, int direction)
{
    // Get decimal part of m_Location.m_X
    double decPart, intpart;
    decPart = modf(this->m_Location.m_X, &intpart);

    if ((decPart >= CPlayer::MAX_TURNING_VALUE) &&
        board->IsPassable(CCoord<unsigned int>(std::ceil(this->m_Location.m_X), this->m_Location.m_Y + direction),
                          this))
    {
        this->m_Location.m_X = std::min(this->m_Location.m_X + this->m_Speed * deltaTime,
                                        std::ceil(this->m_Location.m_X));

    }
        // TODO comment this
    else if ((decPart <= CPlayer::MIN_TURNING_VALUE) &&
             board->IsPassable(CCoord<unsigned int>(std::floor(this->m_Location.m_X), this->m_Location.m_Y + direction),
                               this))
    {
        this->m_Location.m_X = std::max(this->m_Location.m_X - this->m_Speed * deltaTime,
                                        std::floor(this->m_Location.m_X));
    }
}

/*====================================================================================================================*/
bool CPlayer::LocationIsFree(CBoard *board) const
{
    double val = (1 - this->m_Speed);

    if (!board->IsPassable(CCoord<unsigned int>(this->m_Location.m_X, this->m_Location.m_Y), this) ||
        !board->IsPassable(CCoord<unsigned int>(this->m_Location.m_X + val, this->m_Location.m_Y), this) ||
        !board->IsPassable(CCoord<unsigned int>(this->m_Location.m_X, this->m_Location.m_Y + val), this) ||
        !board->IsPassable(CCoord<unsigned int>(this->m_Location.m_X + val, this->m_Location.m_Y + val), this))
    { return false; }

    return true;
}

/*====================================================================================================================*/
void CPlayer::HandleInput(const Uint8 *keyState)
{
    // Handle input when the player is alive
    if (this->m_IsAlive && !this->m_LevelUp)
    {
        // TODO change animation system. Animation setup should not be in Input method.
        // movement
        if (keyState[this->m_Controls->m_Up])
        {
            this->m_VerticalMovingDirection = EDirection::DIRECTION_UP;
            this->m_ActualTexture = ETextureType::TEXTURE_BACK;
        } else if (keyState[this->m_Controls->m_Down])
        {
            this->m_VerticalMovingDirection = EDirection::DIRECTION_DOWN;
            this->m_ActualTexture = ETextureType::TEXTURE_FRONT;
        }

        if (keyState[this->m_Controls->m_Left])
        {
            this->m_HorizontalMovingDirection = EDirection::DIRECTION_LEFT;
            this->m_ActualTexture = ETextureType::TEXTURE_LEFT;
        } else if (keyState[this->m_Controls->m_Right])
        {
            this->m_HorizontalMovingDirection = EDirection::DIRECTION_RIGHT;
            this->m_ActualTexture = ETextureType::TEXTURE_RIGHT;
        }

        // Planting action
        if (keyState[this->m_Controls->m_PlaceBomb] && this->m_PlantingAvaible)
        {
            this->m_IsPlanting = true;
            this->m_PlantingAvaible = false;
        }
            // Planting is not avaible until the button is released
        else if (!keyState[this->m_Controls->m_PlaceBomb])
        { this->m_PlantingAvaible = true; }

        // Detonating action
        if (keyState[this->m_Controls->m_Detonation] && this->m_DetanatingAvaible)
        {
            this->m_DetanatingAvaible = false;
            this->m_IsDetonating = true;
        }
            // Detonating is not avaible until the button is released
        else if (!keyState[this->m_Controls->m_Detonation])
        { this->m_DetanatingAvaible = true; }
    }
}

/*====================================================================================================================*/
void CPlayer::TryPlaceBomb(CBoard *board)
{
    if (this->m_ActiveBombs < this->m_MaxBombs)
    {
        board->PlaceBomb(this);
        //this->m_ActiveBombs++; // TODO uncomment this
    }
}

/*====================================================================================================================*/
void CPlayer::Kill()
{
    if (this->m_IsAlive)
    {
        this->m_Lives--;

        this->m_IsAlive = false;
    }
}

/*====================================================================================================================*/
void CPlayer::Reset()
{
    CMovable::Reset();
    this->m_ActiveBombs = 0;
    this->m_IsAlive = true;
    this->m_LevelUp = false;
}













