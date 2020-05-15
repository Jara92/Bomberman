/**
 * @author Jaroslav Fikar
 * 
*/


#include "CDoor.h"

void CDoor::Apply(CPlayer *player)
{
    // todo přidat kontrolu, zda hráč může projít do dalšího levelu

    player->IncreseScore(this->m_ScoreBonus);
    player->ActivateLevelUp();

    this->m_ScoreBonus = 0;

    this->m_IsAlive = false;
}
