/**
 * @author Jaroslav Fikar
 * 
*/


#include "CBoost.h"

void CBoost::Apply(CPlayer *player)
{
    if (this->m_Apply)
    {
        this->m_Apply(player);
    }
    player->IncreseScore(this->m_ScoreBonus);

    this->m_ScoreBonus = 0;

    // save target player
    if (this->m_Duration != 0)
    {
        this->m_TargetPlayer = player;
    }
        // kill object
    else
    {
        this->m_IsAlive = false;
    }
}

void CBoost::Update(CBoard *board, int deltaTime)
{
    (void *) (board);

    if (this->m_TargetPlayer)
    {
        this->m_Duration -= deltaTime;

        if (this->m_Duration <= 0)
        {
            this->Deactivate();
        }
    }
}

void CBoost::Deactivate()
{
    if (this->m_Deactivate)
    {
        this->m_Deactivate(this->m_TargetPlayer);
    }

    this->m_IsAlive = false;
}
