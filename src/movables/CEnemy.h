/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <vector>
#include "CMovable.h"
#include "../enums/EEnemyMovementMode.h"

class CEnemy : public CMovable
{
public:
    /**
    * CEnemy contructor
    * @param texturePack Texturepack to be rendered.
    * @param location Starting location. (Must be passable)
    * @param size Object size.
    * @param score Score to be claimed.
    * @param speed Enemy speed
    * @param wallPass Can this Enemy walk through destructible walls?
    * @param lives How many lives doest this monster have?
    * @param surveillanceDistance How far this enemy can look forward?
    */
    explicit CEnemy(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size = CCoord<>(1, 1),
                    int score = 100, double speed = 0.005, bool wallPass = false, int lives = 1,
                    unsigned int surveillanceDistance = 1)
            : CMovable(std::move(texturePack), size, location, speed, wallPass, false, lives), m_Score(score),
              m_MovementMode(EEnemyMovementMode::ENEMY_MOVEMENT_MODE_WALK_FORWARD),
              m_SurveillanceDistance(surveillanceDistance)
    {
        // Generate random delay to choose random direction.
        unsigned  int randomDelay = CRandom::Random(4500, 8000);
        this->m_MovementModeTimer.Run(randomDelay, [=](void)
        {
            this->UpdateMovementMode();
        });
    }

    CEnemy(const CEnemy &other) = default;

    CEnemy &operator=(const CEnemy &other) = default;

    virtual ~CEnemy() = default;

    /**
     * Update enemy state.
     * @param board Game board.
     * @param deltaTime Delta time.
     */
    virtual void Update(CBoard &board, int deltaTime) override;

    /**
     * Handle collision with CBlock object.
     * @param blockLocation Block location.
     * @param block Block.
     */
    virtual void CollisionWith(CCoord<unsigned int> blockLocation, CBlock &block) override;

    /**
     * Handle collision with other CMovable object.
     * @param movable Movable object.
     */
    virtual void CollisionWith(CMovable &movable) override
    {}

    /**
     * Handle colision with player.
     * @param player Player.
     */
    virtual void CollisionWithMovable(CPlayer &player) override;

    /**
     * Prepare the enemy for next level.
     * @param board Game board.
     * @param clearLevelObjects Kill and destroy enemies?
     */
    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override;

    /**
     * Try to kill the enemy.
     * @param distance Distance from the enemy
     * @return Score to be achieved.
     */
    virtual unsigned int TryKill(unsigned int distance);

protected:
    int m_Score;
    CTimer m_DestroyTimer;
    CTimer m_MovementModeTimer;
    EEnemyMovementMode m_MovementMode;
    unsigned int m_SurveillanceDistance;

    static constexpr unsigned int ENEMY_DESTROY_DELAY = 1000;

    virtual void UpdateMovementMode() = 0;

    /** Enemy movement. */
    virtual void Move(const CBoard &board, int deltaTime) = 0;

    /**
     * Get avaible moving directions.
     * @param board Game board.
     * @return Avaible directions.
     */
    std::vector<CCoord<double>> GetPossibleMoveDirections(const CBoard &board);

    /**
    * Is given direction safe?
    * @param board Game board.
    * @param direction Moving direction.
    * @param distance How far can the enemy see?
    * @return True - Direction is safe.
    */
    bool DirectionIsSafe(const CBoard &board, CCoord<> direction, unsigned int distance) const;

    /** Enemy goes forward by m_Movement */
    bool GoForward(const CBoard &board);

    /** The enemy chooses random direction. The enemy turns in a random direction.
     * If he has no other choice, he turns around and goes back.*/
    bool GoRandom(const CBoard &board);

    /** The enemy turns in random direction in next crossroad. */
    bool TurnRandom(const CBoard &board);
};
