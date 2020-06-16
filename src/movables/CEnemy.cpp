/**
 * @author Jaroslav Fikar
*/

#include "CEnemy.h"
#include "../CBoard.h"

std::vector<CCoord<double>> CEnemy::GetPossibleMoveDirections(CBoard &board)
{
    CCoord<> oldLocation = this->m_Location;

    std::vector<CCoord<double>> outputDirections;
    // Create directional vectors and texture types.
    double move = (1);
    std::vector<CCoord<>> directions = {{CCoord<double>(0, move)},
                                        {CCoord<double>(0, -move)},
                                        {CCoord<double>(move, 0)},
                                        {CCoord<double>(-move, 0)}};
    // Test every directional vector.
    //  std::cout << "Avaibles:=================" << std::endl;
    for (unsigned int i = 0; i < directions.size(); i++)
    {
        this->m_Location += (directions[i] * 0.5);

        if (this->LocationIsFree(board))
        {
            outputDirections.push_back(directions[i]);
            //  std::cout << "avaible: " << i << " - " << directions[i].second << std::endl;
        }

        this->m_Location = oldLocation;
    }


    return outputDirections;
}

/*====================================================================================================================*/
CCoord<> CEnemy::FindWayOut(CBoard *board)
{
    return CCoord<>(0, -1);
}

/*====================================================================================================================*/
void CEnemy::Update(CBoard &board, int deltaTime)
{
    CMovable::Update(board, deltaTime);

    // Calibrate not moving dimension to integer.
    if (this->m_Movement == CCoord<>(0, 0))
    { return; }
    else if (this->m_Movement.m_X == 0)
    { this->m_Location.m_X = std::max(std::floor(this->m_Location.m_X), this->m_Location.m_X - this->m_Speed); }
    else if (this->m_Movement.m_Y == 0)
    { this->m_Location.m_Y = std::max(std::floor(this->m_Location.m_Y), this->m_Location.m_Y - this->m_Speed); }
}

/*====================================================================================================================*/
void CEnemy::NextLevel(CBoard &board, bool clearLevelObjects)
{
    CMovable::NextLevel(board, clearLevelObjects);

    // Destroy object if required.
    if (clearLevelObjects)
    { this->m_IsDestroyed = true; }
        // Move ene
    else
    {
        // Set random location for this enemy.
        CCoord<unsigned int> random;
        do
        { random = board.GetRandomBoardLocation(); }
        while (!board.PositionFree(random) || !board.PlayersAreaFree(random, CPlayer::ENEMY_SAVE_ZONE));

        this->SetLocation(random.ToDouble());
    }
}

/*====================================================================================================================*/
void CEnemy::CollisionWith(CCoord<unsigned int> blockLocation, CBlock &block)
{
    block.CollisionWith(blockLocation, *this);
}

void CEnemy::CollisionWithPlayer(CPlayer &player)
{
    player.TryKill();
}
