/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <vector>
#include <chrono>
#include "CMovable.h"

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
              m_MoveRandom(false), m_SurveillanceDistance(surveillanceDistance)
    {
        this->m_RandomMovementTimer.Run(5000, [=](void)
        {
            this->m_MoveRandom = true;
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

    virtual void CollisionWith(CCoord<unsigned int> blockLocation, CBlock &block) override;

    virtual void CollisionWith(CMovable &movable) override
    {}

    virtual void CollisionWithMovable(CPlayer &player) override;

    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override;

    virtual unsigned int TryKill(unsigned int distance) = 0;

protected:
    int m_Score;
    CTimer m_DestroyTimer;
    CTimer m_RandomMovementTimer;
    bool m_MoveRandom;
    unsigned int m_SurveillanceDistance;

    static constexpr unsigned int ENEMY_DESTROY_DELAY = 1000;

    /** Enemy movement. */
    virtual void Move(const CBoard &board, int deltaTime) = 0;

    /**
     * Get avaible moving directions.
     * @param board Game board.
     * @return Avaible directions.
     */
    std::vector<CCoord<double>> GetPossibleMoveDirections(const CBoard &board);

    /**
     * Is current m_Movement direction safe?
     * @param board Game board.
     * @param direction Moving direction.
     * @param distance How far can the enemy see?
     * @return True - Direction is safe.
     */
    bool DirectionIsSafe(const CBoard &board, CCoord<> direction, unsigned int distance) const;

    /** Enemy tries to find save direction to go. */
    void RunAway(const CBoard &board);

    /** Enemy goes forward by m_Movement */
    bool GoForward(const CBoard &board);

    /** The enemy chooses random direction. The enemy turns in a random direction.
     * If he has no other choice, he turns around and goes back.*/
    bool GoRandom(const CBoard &board);

    bool TurnRandom(const CBoard &board);
};
