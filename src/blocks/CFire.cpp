/**
 * @author Jaroslav Fikar
*/

#include "CFire.h"
#include "../CBoard.h"

CFire::CFire(std::shared_ptr<CTexturePack> texturePack, CPlayer *owner, CCoord<> size, unsigned int duration)
        : CBlock(std::move(texturePack), size, true, true), m_Owner(owner)
{
    // Run the timer which will destroy this object after the duration expires.
    this->m_ExpirationTimer.Run(duration, [=](void)
    {
        this->m_IsAlive = false;
        this->m_IsDestroyed = true;
    });
}
/*====================================================================================================================*/
void CFire::Update(CBoard &board, int deltaTime)
{
    CBlock::Update(board, deltaTime);

    this->m_ExpirationTimer.Tick(deltaTime);
}

/*====================================================================================================================*/
void CFire::CollisionWith(CCoord<unsigned int> thisLocation, CPlayer &player)
{
    if (this->IsColliding(thisLocation, player))
    {
        // Kill the player if he doesnt have fire imunity.
        unsigned int score = 0;
        if (!player.GetFireImunity())
        { score = player.TryKill(); }

        if(this->m_Owner != &player)
        {this->m_Owner->IncreseScore(score);}
    }
}

/*====================================================================================================================*/
void CFire::CollisionWith(CCoord<unsigned int> thisLocation, CEnemy &enemy)
{
    if (this->IsColliding(thisLocation, enemy))
    {
        unsigned int scoreToBeAchieved = enemy.TryKill(0);

        if (this->m_Owner)
        { this->m_Owner->IncreseScore(scoreToBeAchieved); }
    }
}




