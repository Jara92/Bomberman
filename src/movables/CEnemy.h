/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <vector>
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
              m_SurveillanceDistance(surveillanceDistance)
    {}

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

    virtual void CollisionWithPlayer(CPlayer &player) override;

    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override;

    virtual unsigned int TryKill(unsigned int distance) = 0;

protected:
    int m_Score;
    CTimer m_DeadTimer;
    unsigned int m_SurveillanceDistance;

    static constexpr unsigned int ENEMY_DESTROY_DELAY = 1000;

    /**
     * Get avaible moving directions.
     * @param board Game board.
     * @return Avaible directions.
     */
    std::vector<CCoord<double>> GetPossibleMoveDirections(CBoard &board);

    bool LookForward(CBoard &board, unsigned int distance) const;

    /**
    * Enemy will run away from given location.
    * @param board Game board.
     * @param deltaTime Delta time.
    */
    void RunAway(CBoard &board, int deltaTime);

    void GoForward(CBoard & board, int deltaTime);

    CCoord<> FindWayOut(CBoard *board);
};

