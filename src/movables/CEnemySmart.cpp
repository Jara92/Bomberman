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
        } else
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
        if (this->m_SpeedUpTimer.Done())
        { this->m_SpeedUpTimer.Run(CRandom::Random(2000, 5000)); }

        CCoord<> oldLocation = this->m_Location;

        this->Move(board, deltaTime);

        this->UpdateTextureType(oldLocation);
    }
}

/*====================================================================================================================*/
void CEnemySmart::Move(const CBoard &board, int deltaTime)
{
    for (int i = 0; i < deltaTime; i++)
    {
        if (!this->DirectionIsSafe(board, this->m_Movement, this->m_SurveillanceDistance))
        { this->m_Movement = -1 * this->m_Movement; }

        if (this->TurnRandom(board))
        { continue; }
        else if (this->GoForward(board))
        { continue; }
        else
        { this->GoRandom(board); }
    }
}

/*====================================================================================================================*/
bool CEnemySmart::TurnRandom(const CBoard &board)
{
    auto directions = this->GetPossibleMoveDirections(board);

    if (directions.size() > 2)
    {
        // Choose randomIndex direction and set new movement and texture type.
        unsigned int randomIndex = CRandom::Random(0, directions.size());

        // Remove forward and backward direction.
        while (!directions.empty() && (directions[randomIndex] == -1 * this->m_Movement))
        {
            directions.erase(directions.begin() + randomIndex);
            randomIndex = CRandom::Random(0, directions.size());
        }

        if (!directions.empty())
        {
            this->m_Movement = directions[randomIndex];

            bool move = this->GoForward(board);

            if (move)
            { return move; }
        }
    }
    return false;
}

