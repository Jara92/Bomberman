/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBomb.h"
#include "../CBoard.h"


void CBomb::Update(CBoard *board, int deltaTime)
{
    CGameObject::Update(board, deltaTime);

    if (this->m_IsAlive)
    {
        // Check for the owner
        if (this->m_IsPassableForOwner && this->m_Owner)
        {
            // If owner left bomb area the bomb will be unpassable for him.
            if (!this->IsColiding(this->m_Owner))
            { this->m_IsPassableForOwner = false; }
        }

        this->m_ExplosionTimer.Tick(deltaTime);

        if(this->m_IsTriggered)
        {this->Explode(board);}
    }
}

/*====================================================================================================================*/
void CBomb::Detonate(CBoard *board)
{
    if (this->m_RemoteTrigger)
    {
        // Set explosion timer.
        this->m_ExplosionTimer.Run(this->m_ExplosionDelay, [=](void)
        { this->m_IsTriggered = true; });
    }
}

/*====================================================================================================================*/
void CBomb::Explode(CBoard *board)
{
    if (this->m_IsAlive)
    {
        if (this->m_Owner)
        {
            this->m_Owner->DecreseActiveBombs();
        }

        // Destroy create explosion and destroy the bomb
        board->CreateExplosion(this);
    }
}
