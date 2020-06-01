/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBomb.h"
#include "../CBoard.h"


void CBomb::Update(CBoard *board, int deltaTime)
{
    CGameObject::Update(board, deltaTime);

    if(this->m_IsAlive)
    {
        // Check for the owner
        if (this->m_IsPassableForOwner && this->m_Owner)
        {
            // If owner left bomb area the bomb will be unpassable for him.
            if (!this->IsColiding(this->m_Owner, CBomb::COLLISION_TOLERANCE))
            {
                this->m_IsPassableForOwner = false;
            }
        }

        // Explosion
        this->m_ExplosionCounter += deltaTime;
        if (this->m_ExplosionCounter > this->m_ExplosionDelay && this->m_IsAlive)
        {
            this->m_ExplosionCounter = 0;
            this->m_ExplosionDelay = 0;

            this->Detonate(board);
        }
    }
}

/*====================================================================================================================*/
void CBomb::Detonate(CBoard *board)
{
    if (this->m_ExplosionDelay == 0)
    {
        Explode(board);
    }
}
/*====================================================================================================================*/
void CBomb::Explode(CBoard *board)
{
    if(this->m_IsAlive)
    {
        this->m_IsAlive = false;
        board->CreateExplosion(this);

        this->m_Owner->DecreseActiveBombs();
        this->m_Owner = nullptr;
    }

}
