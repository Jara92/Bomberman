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
    */
    explicit CEnemy(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size = CCoord<>(1, 1),
                    int score = 100, double speed = 0.005, bool wallPass = false, int lives = 1)
            : CMovable(std::move(texturePack), size, location, speed, wallPass, false, lives), m_Score(score)
    {    }

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

    virtual void CollisionWith(CMovable &movable) override;

    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override;

    virtual unsigned int TryKill(unsigned int distance) = 0;

protected:
    int m_Score;
    CTimer m_DeadTimer;

    static constexpr unsigned int ENEMY_DESTROY_DELAY = 1000;

    /**
     * Get avaible moving directions.
     * @param board Game board.
     * @return Avaible directions.
     */
    std::vector<CCoord<double>> GetPossibleMoveDirections(CBoard &board);

    CCoord<> FindWayOut(CBoard *board);
};

