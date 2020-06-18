/**
 * @author Jaroslav Fikar
*/

#include "CBoost.h"
#include "../../CBoard.h"

void CBoost::Apply(const CBoard & board, CPlayer &player)
{
    if (this->m_IsAlive)
    {
        if (this->m_Apply)
        { this->m_Apply(&player); }

        player.IncreseScore(this->m_ScoreBonus);

        this->m_ScoreBonus = 0;

        // save target player
        if (this->m_Duration != 0)
        { this->m_TargetPlayer = &player; }
            // kill object
        else
        { this->m_IsAlive = false; this->m_IsDestroyed = true; }
    }
}

/*====================================================================================================================*/
void CBoost::Update(CBoard &board, int deltaTime)
{
    CCollectible::Update(board, deltaTime);

    if (this->m_TargetPlayer)
    {
        this->m_Duration -= deltaTime;

        if (this->m_Duration <= 0)
        { this->Deactivate(); }
    }
}

/*====================================================================================================================*/
void CBoost::Deactivate()
{
    if (this->m_Deactivate)
    { this->m_Deactivate(this->m_TargetPlayer); }

    this->m_IsAlive = false;
}
