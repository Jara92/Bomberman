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
/*====================================================================================================================*/
void CEnemy::CollisionWithPlayer(CPlayer &player)
{
    player.TryKill();
}
/*====================================================================================================================*/
bool CEnemy::LookForward(CBoard &board, unsigned int distance) const
{
    for(unsigned int i = 1; i <= distance; i++)
    {
        CCoord<> loc = this->m_Location + ((this->m_Movement * (distance - 0.5)));
        CCoord<unsigned int> forwardCell = loc.ToUnsignedInt();

        // Check for dangerous object in forwardCell location.
        if (board.GetMapItem(forwardCell) && board.GetMapItem(forwardCell)->IsDangerous())
        { return false; }
    }

    return true;
}

void CEnemy::RunAway(CBoard &board, int deltaTime)
{
    // Move deltaTime times.
    for (int i = 0; i < deltaTime; i++)
    {
        // Save old location and move.
        CCoord<> oldLocation = this->m_Location;
        this->m_Location += (this->m_Movement * this->m_Speed);

        // If enemy stands still or new location is not free or a dangerous object is in sight.
        if (this->m_Movement == CCoord<>(0, 0) || !this->LocationIsFree(board))
        {
            // Recover location and get avaible directions to go.
            this->m_Location = oldLocation;
            auto directions = this->GetPossibleMoveDirections(board);

            // Stand still if there is no direction to go.
            if (directions.empty())
            {
                this->m_Movement = CCoord<>(0, 0);
                this->m_Body.SetActualTextureType(ETextureType::TEXTURE_FRONT);
            }
                // Go to random direction.
            else
            {
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() * rand();
                std::default_random_engine randomEngine(seed);

                // Choose randomIndex direction and set new movement and texture type.
                unsigned int randomIndex = randomEngine() % directions.size();

                CCoord<> randomDirection = directions[randomIndex];

                // Choose other direction if possible.
                if (this->m_Movement == randomDirection && directions.size() > 1)
                {
                    directions.erase(directions.begin() + randomIndex);
                    randomIndex = randomEngine() % directions.size();
                }

                this->m_Movement = directions[randomIndex];
                this->m_Location += (this->m_Movement * this->m_Speed);
            }
        }
    }
}

void CEnemy::GoForward(CBoard &board, int deltaTime)
{

}
