/**
 * @author Jaroslav Fikar
*/

#include "CBomb.h"
#include "../CBoard.h"

void CBomb::Update(CBoard &board, int deltaTime)
{
    CBlock::Update(board, deltaTime);

    if (this->m_IsAlive)
    {
        this->m_ExplosionTimer.Tick(deltaTime);

        // Trigger when the player is detonating.
        if (this->m_RemoteTrigger && this->m_Owner->IsDetonating())
        {
            // Little delay.
            this->m_ExplosionTimer.Run(this->m_ExplosionDelay, [=](void)
            { this->m_IsTriggered = true; });
        }

        if (this->m_IsTriggered)
        { this->Explode(board); }
    }
}

/*====================================================================================================================*/
void CBomb::Explode(CBoard &board)
{
    if (this->m_IsAlive)
    {
        if (this->m_Owner)
        { this->m_Owner->DecreseActiveBombs(); }

        // Do not explode few times.
        this->m_IsTriggered = false;

        board.CauseExplosion(this);
    }
}

/*====================================================================================================================*/
void CBomb::CollisionWith(CCoord<unsigned int> thisLocation, CPlayer &player)
{
    // Make bomb unpassable for owner once he leaves bomb area.
    if (!this->IsColliding(thisLocation, player) && &player == this->m_Owner)
    { this->m_IsPassableForOwner = false; }
}

/*====================================================================================================================*/
bool CBomb::IsPassable(CCoord<unsigned int> thisLocation, const CMovable &movable) const
{
    if (this->IsColliding(thisLocation, movable))
    {
        // The owner can go through the bomb until it leaves its area.
        if (this->m_Owner == &movable && this->m_IsPassableForOwner)
        { return true; }

            // Bombs are passable for their owners which has "BombPass" bonus activated.
        else if (movable.GetBombPass() && &movable == this->m_Owner)
        { return true; }
        return false;
    }

    return true;
}
