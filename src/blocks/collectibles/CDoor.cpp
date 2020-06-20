/**
 * @author Jaroslav Fikar
*/

#include "CDoor.h"
#include "../../CBoard.h"

void CDoor::Apply(const CBoard & board, CPlayer &player)
{
    // All enemies must be dead.
    if(board.m_Movables.size() == board.m_Players.size())
    {
        player.IncreseScore(this->m_ScoreBonus);
        player.ActivateLevelUp();

        this->m_ScoreBonus = 0;
    }

    this->m_IsTriggered = false;
}
