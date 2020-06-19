/**
 * @author Jaroslav Fikar
*/

#include "CEnemySmart.h"
#include "../CBoard.h"

CEnemySmart::CEnemySmart(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size, int score,
                         double speed, bool wallPass, int lives)
        : CEnemy(std::move(texturePack), location, size, score, speed, wallPass, lives, 1), m_SpeedUp(false)
{
    this->m_SpeedUpTimer.Run(CRandom::Random(2000, 5000), [=](void)
    {
        if (this->m_SpeedUp)
        {
            this->m_SpeedUp = false;
            this->m_Speed /= CEnemySmart::ENEMY_SPEED_UP;
        }
        else
        {
            this->m_SpeedUp = true;
            this->m_Speed *= CEnemySmart::ENEMY_SPEED_UP;
        }
    });
}
/*====================================================================================================================*/
void CEnemySmart::Update(CBoard &board, int deltaTime)
{
    CEnemy::Update(board, deltaTime);
    this->m_SpeedUpTimer.Tick(deltaTime);

    // Move when the enemy is alive.
    if (this->m_IsAlive)
    {
        // Run speedup timer again with random value.
        if(this->m_SpeedUpTimer.Done())
        {this->m_SpeedUpTimer.Run(CRandom::Random(2000, 5000));}

        CCoord<> oldLocation = this->m_Location;

        this->Move(board, deltaTime);

        this->UpdateTextureType(oldLocation);
    }
}

/*====================================================================================================================*/
void CEnemySmart::UpdateMovementMode()
{
    int actualMovementMode = static_cast<int>(this->m_MovementMode);
    int newMovementMode = 0;

    if (actualMovementMode < static_cast<int>(EEnemyMovementMode::ENEMY_MOVEMENT_MODE_NR_ITEMS) - 1)
    { newMovementMode = actualMovementMode + 1; }

    this->m_MovementMode = static_cast<EEnemyMovementMode >(newMovementMode);

    this->m_MovementModeTimer.Reset();
}

/*====================================================================================================================*/

void CEnemySmart::Move(const CBoard &board, int deltaTime)
{
    for (int i = 0; i < deltaTime; i++)
    {
        if (/*this->m_MovementMode == EEnemyMovementMode::ENEMY_MOVEMENT_MODE_RANDOM && */this->TurnRandom(board))
        { continue; }
        else if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
    }
}



