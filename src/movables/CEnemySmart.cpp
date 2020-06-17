/**
 * @author Jaroslav Fikar
 * 
*/


#include "CEnemySmart.h"
#include "../CBoard.h"

void CEnemySmart::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);
}
/*====================================================================================================================*/

void CEnemySmart::Move(const CBoard &board, int deltaTime)
{
    for(int i = 0; i < deltaTime; i++)
    {

    }
}
/*====================================================================================================================*/
void CEnemySmart::FollowThePlayer(const CBoard & board)
{
    // TODO test random generator staff
    if(!this->m_PersecutedPlayer)
    {
        unsigned int randomPlayer = CRandom::Random(0, board.m_Players.size());
        this->m_PersecutedPlayer = board.m_Players[randomPlayer];
    }

    CCoord<unsigned int> targetLocation = this->m_PersecutedPlayer->GetLocationCell();

}
/*====================================================================================================================*/
void CEnemySmart::ProtectCollectible(const CBoard & board)
{

}
