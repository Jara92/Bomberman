/**
 * @author Jaroslav Fikar
 * 
*/


#include "CPlayer.h"
#include "../../CBoard.h"

/*====================================================================================================================*/
void CPlayer::Update(CBoard &board, int deltaTime)
{
    CMovable::Update(board, deltaTime);

    // Save old location to calculate actual movement vector.
    CCoord<> oldLocation = this->m_Location;

    // Movement in vertical and horizontal axis and update texture by movement.
    this->HorizontalMove(board, deltaTime);
    this->VerticalMove(board, deltaTime);
    this->UpdateTextureType(oldLocation);

    // Plating action.
    if (this->m_IsPlanting)
    { this->TryPlaceBomb(board); }

    // Detonation action.
    if (this->m_IsDetonating)
    { board.DetonateBombs(this); }

    // Clean input.
    this->m_IsDetonating = this->m_IsPlanting = false;
    this->m_Movement = CCoord<>(0, 0);
}

/*====================================================================================================================*/
void CPlayer::VerticalMove(CBoard &board, int deltaTime)
{
    CCoord<> oldLocation = this->m_Location;
    this->m_Location.m_Y += (this->m_Speed * this->m_Movement.m_Y) * deltaTime;

    // Check collisions
    if (!this->CellIsFree(board, deltaTime, this->m_Location))
    {
        this->m_Location = oldLocation;
        // Try center horizontal position if horizontal direction is none
        // This handles problems with turning. When the player is close to turn I will try to center his position to allow him turn this direction.
        if (m_Movement.m_X == 0)
        { this->HorizontalCenter(board, deltaTime, static_cast<int>(this->m_Movement.m_Y)); }
    }
}

/*====================================================================================================================*/
void CPlayer::HorizontalMove(CBoard &board, int deltaTime)
{
    CCoord<> oldLocation = this->m_Location;
    this->m_Location.m_X += (this->m_Speed * this->m_Movement.m_X) * deltaTime;

    // Check collisions
    if (!this->CellIsFree(board, deltaTime, this->m_Location))
    {
        this->m_Location = oldLocation;
        // Try center horizontal position if horizontal direction is none
        // This handles problems with turning. When the player is close to turn I will try to center his position to allow him turn this direction.
        if (m_Movement.m_Y == 0)
        { this->VerticalCenter(board, deltaTime, static_cast<int>(this->m_Movement.m_X)); }
    }
}

/*====================================================================================================================*/
void CPlayer::VerticalCenter(CBoard &board, int deltaTime, int direction)
{
    // Get decimal part of m_Location.m_Y
    double decPart, intpart;
    decPart = modf(this->m_Location.m_Y, &intpart);

    // Turn smoothly when player is very close to empty cell
    if ((decPart >= CPlayer::MIN_TURNING_VALUE) &&
        board.IsPassable(CCoord<unsigned int>(this->m_Location.m_X + direction, std::ceil(this->m_Location.m_Y)),
                          this))
    {
        this->m_Location.m_Y = std::min(this->m_Location.m_Y + this->m_Speed * deltaTime,
                                        std::ceil(this->m_Location.m_Y));

    } else if ((decPart <= CPlayer::MAX_TURNING_VALUE) &&
               board.IsPassable(
                       CCoord<unsigned int>(this->m_Location.m_X + direction, std::floor(this->m_Location.m_Y)),
                       this))
    {
        this->m_Location.m_Y = std::max(this->m_Location.m_Y - this->m_Speed * deltaTime,
                                        std::floor(this->m_Location.m_Y));
    }

}

/*====================================================================================================================*/
void CPlayer::HorizontalCenter(CBoard &board, int deltaTime, int direction)
{
    // Get decimal part of m_Location.m_X
    double decPart, intpart;
    decPart = modf(this->m_Location.m_X, &intpart);

    // Turn smoothly when player is very close to empty cell
    if ((decPart >= CPlayer::MAX_TURNING_VALUE) &&
        board.IsPassable(CCoord<unsigned int>(std::ceil(this->m_Location.m_X), this->m_Location.m_Y + direction),
                          this))
    {
        this->m_Location.m_X = std::min(this->m_Location.m_X + this->m_Speed * deltaTime,
                                        std::ceil(this->m_Location.m_X));

    } else if ((decPart <= CPlayer::MIN_TURNING_VALUE) &&
               board.IsPassable(
                       CCoord<unsigned int>(std::floor(this->m_Location.m_X), this->m_Location.m_Y + direction),
                       this))
    {
        this->m_Location.m_X = std::max(this->m_Location.m_X - this->m_Speed * deltaTime,
                                        std::floor(this->m_Location.m_X));
    }

}

/*====================================================================================================================*/
void CPlayer::HandleInput(const Uint8 *keyState)
{
    // Handle input when the player is alive
    if (this->m_IsAlive && !this->m_LevelUp)
    {
        // movement
        if (keyState[this->m_Controls.m_Up])
        { this->m_Movement.m_Y = -1; }
        else if (keyState[this->m_Controls.m_Down])
        { this->m_Movement.m_Y = 1; }

        if (keyState[this->m_Controls.m_Left])
        { this->m_Movement.m_X = -1; }
        else if (keyState[this->m_Controls.m_Right])
        { this->m_Movement.m_X = 1; }

        // Planting action
        if (keyState[this->m_Controls.m_PlaceBomb] && this->m_PlantingAvaible)
        {
            this->m_IsPlanting = true;
            this->m_PlantingAvaible = false;
        }
            // Planting is not avaible until the button is released
        else if (!keyState[this->m_Controls.m_PlaceBomb])
        { this->m_PlantingAvaible = true; }

        // Detonating action
        if (keyState[this->m_Controls.m_Detonation] && this->m_DetonatingAvaible)
        {
            this->m_DetonatingAvaible = false;
            this->m_IsDetonating = true;
        }

            // Detonating is not avaible until the button is released
        else if (!keyState[this->m_Controls.m_Detonation])
        { this->m_DetonatingAvaible = true; }
    }
}

/*====================================================================================================================*/
void CPlayer::TryPlaceBomb(CBoard &board)
{
    if (this->m_ActiveBombs < this->m_MaxBombs)
    {
        if (board.PlaceBomb(this))
        { this->m_ActiveBombs++; } // TODO uncomment this
    }
}

/*====================================================================================================================*/
void CPlayer::Kill()
{
    if (this->m_IsAlive)
    {
        //this->m_Lives--;
        // this->m_IsAlive = false;
    }
}

/*====================================================================================================================*/
void CPlayer::Reset()
{
    CMovable::Reset();
    this->m_ActiveBombs = 0;
    this->m_LevelUp = false;
}

/*====================================================================================================================*/
void CPlayer::UpdateTextureType(CCoord<> oldLocation)
{
    // Calculate movement vector.
    CCoord<> diff = oldLocation - this->m_Location;
    // Move in both dimensions.
    if (diff != CCoord<>(0,0))
    {
        // Set smaller move step to zero.
        if (std::abs(diff.m_X) > std::abs(diff.m_Y))
        { diff.m_Y = 0; }
        else
        { diff.m_X = 0; }
    }
    // Player is not moving. Use input movement direction to setup animation.
    else
    { diff = -1 * this->m_Movement; }

    // Set right texture by movement vector.
    if (diff.m_X < 0)
    { this->m_ActualTexture = ETextureType::TEXTURE_RIGHT; }
    else if (diff.m_X > 0)
    { this->m_ActualTexture = ETextureType::TEXTURE_LEFT; }
    else if (diff.m_Y < 0)
    { this->m_ActualTexture = ETextureType::TEXTURE_FRONT; }
    else if (diff.m_Y > 0)
    { this->m_ActualTexture = ETextureType::TEXTURE_BACK; }
}

