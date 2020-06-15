/**
 * @author Jaroslav Fikar
 * 
*/


#include "CPlayer.h"
#include "../CBoard.h"
#include "../blocks/CBlock.h"

/*====================================================================================================================*/
void CPlayer::Update(CBoard &board, int deltaTime)
{
    CMovable::Update(board, deltaTime);

    this->HandleInput(deltaTime);

    // Save old location to calculate actual movement vector.
    CCoord<> oldLocation = this->m_Location;

    // Move in horizontal and vertical axis deltaTime times.
    for (int i = 0; i < deltaTime; i++)
    {
        this->HorizontalMove(board);
        this->VerticalMove(board);
    }
    this->UpdateTextureType(oldLocation);

    // Plating action.
    if (this->m_Input.IsPlanting())
    { this->TryPlaceBomb(board); }
}

/*====================================================================================================================*/
void CPlayer::VerticalMove(CBoard &board)
{
    CCoord<> oldLocation = this->m_Location;
    this->m_Location.m_Y += (this->m_Speed * this->m_Input.GetMovement().m_Y);

    // Check collisions
    if (!this->CellIsFree(board, this->m_Location))
    {
        this->m_Location = oldLocation;
        // Try center horizontal position if horizontal direction is none
        // This handles problems with turning. When the player is close to turn I will try to center his position to allow him turn this direction.
        if (m_Movement.m_X == 0)
        { this->HorizontalCenter(board, static_cast<int>(this->m_Input.GetMovement().m_Y)); }
    }
}

/*====================================================================================================================*/
void CPlayer::HorizontalMove(CBoard &board)
{
    CCoord<> oldLocation = this->m_Location;
    this->m_Location.m_X += (this->m_Speed * this->m_Input.GetMovement().m_X);

    // Check collisions
    if (!this->CellIsFree(board, this->m_Location))
    {
        this->m_Location = oldLocation;
        // Try center horizontal position if horizontal direction is 0.
        // This handles problems with turning. When the player is close to turn I will try to center his position to allow him turn this direction.
        if (m_Movement.m_Y == 0)
        { this->VerticalCenter(board, static_cast<int>(this->m_Input.GetMovement().m_X)); }
    }
}

/*====================================================================================================================*/
void CPlayer::VerticalCenter(CBoard &board, int direction)
{
    // Get decimal part of m_Location.m_Y
    double decPart, intpart;
    decPart = modf(this->m_Location.m_Y, &intpart);

    // Turn smoothly down when player is very close to empty cell
    if ((decPart >= CPlayer::MIN_TURNING_VALUE) &&
        board.IsPassable(CCoord<unsigned int>(this->m_Location.m_X + direction, std::ceil(this->m_Location.m_Y)),
                         *this))
    {
        this->m_Location.m_Y = std::min(this->m_Location.m_Y + this->m_Speed, std::ceil(this->m_Location.m_Y));
    }
        // Turn smoothly up
    else if ((decPart <= CPlayer::MAX_TURNING_VALUE) && board.IsPassable(
            CCoord<unsigned int>(this->m_Location.m_X + direction, std::floor(this->m_Location.m_Y)), *this))
    { this->m_Location.m_Y = std::max(this->m_Location.m_Y - this->m_Speed, std::floor(this->m_Location.m_Y)); }

}

/*====================================================================================================================*/
void CPlayer::HorizontalCenter(CBoard &board, int direction)
{
    // Get decimal part of m_Location.m_X
    double decPart, intpart;
    decPart = modf(this->m_Location.m_X, &intpart);

    // Turn smoothly right when player is very close to empty cell
    if ((decPart >= CPlayer::MAX_TURNING_VALUE) &&
        board.IsPassable(CCoord<unsigned int>(std::ceil(this->m_Location.m_X), this->m_Location.m_Y + direction),
                         *this))
    {
        this->m_Location.m_X = std::min(this->m_Location.m_X + this->m_Speed, std::ceil(this->m_Location.m_X));
    }
        // Turn smoothly left
    else if ((decPart <= CPlayer::MIN_TURNING_VALUE) && board.IsPassable(
            CCoord<unsigned int>(std::floor(this->m_Location.m_X), this->m_Location.m_Y + direction), *this))
    { this->m_Location.m_X = std::max(this->m_Location.m_X - this->m_Speed, std::floor(this->m_Location.m_X)); }

}

/*====================================================================================================================*/
void CPlayer::HandleInput(int deltaTime)
{
    // Handle input when the player is alive
    if (this->m_IsAlive && !this->m_LevelUp)
    { this->m_Input.Update(deltaTime); }
    else
    { this->m_Input.Reset(); }

    this->m_Movement = this->m_Input.GetMovement();
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
unsigned int CPlayer::TryKill(unsigned int distance)
{
    if (this->m_IsAlive)
    {
        this->m_Lives--;
        this->m_IsAlive = false;

        return 1;
    }

    return 0;
}

/*====================================================================================================================*/
void CPlayer::NextLevel(CBoard &board, bool clearLevelObjects)
{
    CMovable::NextLevel(board, clearLevelObjects);
    this->m_ActiveBombs = 0;
    this->m_LevelUp = false;
}

/*====================================================================================================================*/
void CPlayer::UpdateTextureType(CCoord<> oldLocation)
{
    // Calculate movement vector.
    CCoord<> diff = oldLocation - this->m_Location;
    // Move in both dimensions.
    if (diff != CCoord<>(0, 0))
    {
        // Set smaller move step to zero.
        if (std::abs(diff.m_X) > std::abs(diff.m_Y))
        { diff.m_Y = 0; }
        else
        { diff.m_X = 0; }
    }
        // Player is not moving. Use input movement direction to setup animation.
    else
    { diff = -1 * this->m_Input.GetMovement(); }

    CMovable::UpdateTextureByMovement(diff);
}
/*====================================================================================================================*/
void CPlayer::CollisionWith(CCoord<unsigned int> blockLocation, CBlock &block)
{
    block.CollisionWith(blockLocation, *this);
}
/*====================================================================================================================*/
void CPlayer::CollisionWith(CMovable &movable)
{
    if (this->IsColliding(movable))
    {
        std::cout << "collision player" << std::endl;
    }
}
