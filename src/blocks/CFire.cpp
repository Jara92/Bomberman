/**
 * @author Jaroslav Fikar
 * 
*/


#include "CFire.h"
#include "../CBoard.h"

void CFire::Update(CBoard &board, int deltaTime)
{
    CBlock::Update(board, deltaTime);

    // Update duration counter and destroy fire.
    this->m_DurationCounter += deltaTime;

    // Destroy this fire
    if (this->m_DurationCounter > this->m_Duration)
    { this->m_IsAlive = false; }
}
/*====================================================================================================================*/
void CFire::PlayerCollision(CCoord<unsigned int> thisLocation, CPlayer &player)
{
    if(this->IsColliding(thisLocation, player))
    {
        // Kill the player if he doesnt have fire imunity.
        if(!player.GetFireImunity())
        {player.TryKill();}
    }
}
