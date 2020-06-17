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

    this->m_RandomMovementTimer.Tick(deltaTime);

  //  std::cout << "Remaining " << m_RandomMovementTimer.GetRemainingTime() << std::endl;

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
bool CEnemy::DirectionIsSafe(const CBoard &board, CCoord<> direction, unsigned int distance) const
{
    for (unsigned int i = 1; i <= distance; i++)
    {
        CCoord<> loc = this->GetLocationCell().ToDouble() + ((direction * (i)));
        CCoord<unsigned int> forwardCell = loc.ToUnsignedInt();

        // Check for dangerous object in forwardCell location.
        if (board.GetMapItem(forwardCell) && board.GetMapItem(forwardCell)->IsDangerous())
        { return false; }
    }

    return true;
}

/*====================================================================================================================*/
void CEnemy::RunAway(const CBoard &board)
{
    auto directions = this->GetPossibleMoveDirections(board);

    // Do nothing when there is no option.
    if (directions.empty())
    { this->m_Movement = CCoord<>(0, 0); }
    else
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() * rand();
        std::default_random_engine randomEngine(seed);

        // Choose randomIndex direction and set new movement and texture type.
        unsigned int randomIndex = randomEngine() % directions.size();

        // Do not move if the enemy is surrounded.
        if (this->m_Movement == directions[randomIndex] && directions.size() == 1)
        {
            this->m_Movement = CCoord<>(0, 0);
            return;
        }
            // Choose other direction if possible.
        else if (this->m_Movement == directions[randomIndex] && directions.size() > 1)
        {
            directions.erase(directions.begin() + randomIndex);
            randomIndex = randomEngine() % directions.size();
        }

        this->m_Movement = directions[randomIndex];
    }
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
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() * rand();
        std::default_random_engine randomEngine(seed);

        // Choose randomIndex direction and set new movement and texture type.
        unsigned int randomIndex = randomEngine() % directions.size();

        // Prefer turning before going back.
        CCoord<> randomDirection = directions[randomIndex];
        if (directions.size() > 1 && (this->m_Movement == -1 * randomDirection ||
                                      !this->DirectionIsSafe(board, randomDirection, this->m_SurveillanceDistance)))
        {
            directions.erase(directions.begin() + randomIndex);
            randomIndex = randomEngine() % directions.size();
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

bool CEnemy::TurnRandom(const CBoard &board)
{
    auto directions = this->GetPossibleMoveDirections(board);

    if (directions.size() <= 2)
    { return this->GoForward(board); }
    else
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() * rand();
        std::default_random_engine randomEngine(seed);

        // Choose randomIndex direction and set new movement and texture type.
        unsigned int randomIndex = randomEngine() % directions.size();

        // Remove forward and backward direction.
        while (!directions.empty() && (directions[randomIndex] == this->m_Movement ||
                                       directions[randomIndex] == -1 * this->m_Movement))
        {
            directions.erase(directions.begin() + randomIndex);
            randomIndex = randomEngine() % directions.size();
        }

        // Go forward if there is no turn.
        if (!directions.empty())
        {
            this->m_Movement = directions[randomIndex];

            bool move = this->GoForward(board);

            if (move)
            {
                this->m_MoveRandom = false;
                this->m_RandomMovementTimer.Reset();
            }
        } else
        { return this->GoForward(board); }
    }
}

