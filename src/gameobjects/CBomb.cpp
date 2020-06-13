/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBomb.h"
#include "../CBoard.h"


void CBomb::Update(CBoard &board, int deltaTime)
{
    CBlock::Update(board, deltaTime);

    if (this->m_IsAlive)
    {
        this->m_ExplosionTimer.Tick(deltaTime);

        // Check for the owner
        if (this->m_IsPassableForOwner && this->m_Owner)
        {
            // If owner left bomb area the bomb will be unpassable for him.
            // TODO owner lolision
            /*  if (!this->IsColliding(this->m_Owner))
              { this->m_IsPassableForOwner = false; }*/
        }

        // Trigger when the player is detonating.
        if(this->m_RemoteTrigger && this->m_Owner->IsDetonating())
        {this->m_IsTriggered = true;}


        if (this->m_IsTriggered)
        { this->Explode(board); }
    }
}

/*====================================================================================================================*/
void CBomb::Detonate(CBoard &board)
{
    if (this->m_RemoteTrigger)
    {
        // Set explosion timer.
        this->m_ExplosionTimer.Run(this->m_ExplosionDelay, [=](void)
        { this->m_IsTriggered = true; });
    }
}

/*====================================================================================================================*/
void CBomb::Explode(CBoard &board)
{
    if (this->m_IsAlive)
    {
        if (this->m_Owner)
        { this->m_Owner->DecreseActiveBombs(); }

        // Destroy create explosion and destroy the bomb
        board.CauseExplosion(this);
    }
}
