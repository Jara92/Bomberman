/**
 * @author Jaroslav Fikar
*/

#include "CEnemy.h"
#include "../CBoard.h"

std::vector<CCoord<double>> CEnemy::GetPossibleMoveDirections(const CBoard &board)
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
    for (unsigned int i = 0; i < directions.size(); i++)
    {
        this->m_Location += (directions[i] * 0.5);

        if (this->LocationIsFree(board))
        { outputDirections.push_back(directions[i]); }

        this->m_Location = oldLocation;
    }

    return outputDirections;
}

/*====================================================================================================================*/
void CEnemy::Update(CBoard &board, int deltaTime)
{
    CMovable::Update(board, deltaTime);

    this->m_DestroyTimer.Tick(deltaTime);
    this->m_MovementModeTimer.Tick(deltaTime);

    if (this->m_Movement == CCoord<>(0, 0))
    { return; }
        // Calibrate not moving dimension.
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
unsigned int CEnemy::TryKill(unsigned int distance)
{
    if (this->m_IsAlive)
    {
        this->m_Lives--;

        // Check lives of the monster
        if (this->m_Lives <= 0)
        {
            this->m_IsAlive = false;
            this->m_Movement = CCoord<>(0, 0);

            int score = this->m_Score;
            // Set score to 0 to make sure player doesn't get it more than once
            this->m_Score = 0;

            // Destroy the object with a delay.
            this->m_DestroyTimer.Run(CEnemy::ENEMY_DESTROY_DELAY, [=](void)
            {
                this->m_IsDestroyed = true;
            });

            return score;
        }
    }

    return 0;
}

/*====================================================================================================================*/
void CEnemy::CollisionWith(CCoord<unsigned int> blockLocation, CBlock &block)
{
    block.CollisionWith(blockLocation, *this);
}

/*====================================================================================================================*/
void CEnemy::CollisionWithMovable(CPlayer &player)
{
    if (this->m_IsAlive)
    { player.TryKill(); }
}

/*====================================================================================================================*/
bool CEnemy::GoForward(const CBoard &board)
{
    CCoord<> oldLocation = this->m_Location;

    this->m_Location += this->m_Movement * this->m_Speed;
    // If enemy stands still or new location is not free or a dangerous object is in sight.
    if (this->m_Movement == CCoord<>(0, 0) || !this->LocationIsFree(board))
    {
        // Recover location.
        this->m_Location = oldLocation;

        return false;
    }

    return true;
}

/*====================================================================================================================*/
bool CEnemy::GoRandom(const CBoard &board)
{
    auto directions = this->GetPossibleMoveDirections(board);

    // Stand still if there is no direction to go.
    if (directions.empty())
    { this->m_Movement = CCoord<>(0, 0); }
        // Go to random direction.
    else
    {
        // Choose randomIndex direction and set new movement and texture type.
        unsigned int randomIndex = CRandom::Random(0, directions.size());

        // Prefer turning before going back.
        CCoord<> randomDirection = directions[randomIndex];
        if (directions.size() > 1 && (this->m_Movement == -1 * randomDirection ||
                                      !this->DirectionIsSafe(board, randomDirection, this->m_SurveillanceDistance)))
        {
            directions.erase(directions.begin() + randomIndex);
            randomIndex = CRandom::Random(0, directions.size());
            randomDirection = directions[randomIndex];
        }

        // Do not move if there is no safe move direction.
        if (this->DirectionIsSafe(board, randomDirection, this->m_SurveillanceDistance))
        { this->m_Movement = randomDirection; }
        else
        { this->m_Movement = CCoord<>(0, 0); }
    }

    // Now enemy can go forward. (Or stay put)
    return this->GoForward(board);
}

/*====================================================================================================================*/
bool CEnemy::DirectionIsSafe(const CBoard &board, CCoord<> direction, unsigned int distance) const
{
    for (unsigned int i = 1; i <= distance; i++)
    {
        CCoord<> loc = this->GetLocation() + CCoord<>(0.5, 0.5) + ((direction * (i)));
        CCoord<unsigned int> forwardCell = loc.ToUnsignedInt();

        // Check for dangerous object in forwardCell location.
        if (board.GetMapItem(forwardCell) && board.GetMapItem(forwardCell)->IsDangerous())
        { return false; }
    }

    return true;
}

