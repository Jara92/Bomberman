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
            : CMovable(std::move(texturePack), size, location, speed, wallPass, false, lives), m_Score(score),
              m_Direction({0, 0})
    {}

    CEnemy(const CEnemy &other) = default;

    CEnemy &operator=(const CEnemy &other) = default;

    virtual ~CEnemy() = default;

    /**
     * Update enemy state.
     * @param board Game board.
     * @param deltaTime Delta time.
     */
    virtual void Update(CBoard *board, int deltaTime) override = 0;

    /**
     * Try to kill this enemy.
     * @param distance Distance between the enemy and a killer.
     * @return Score to be achieved.
     */
    virtual int TryKill(unsigned int distance) = 0;

protected:
    int m_Score;
    CCoord<> m_Direction;

    /**
     * Get avaible moving directions.
     * @param board Game board.
     * @return Avaible directions.
     */
    std::vector<std::pair<ETextureType, CCoord<double>>> GetPossibleMoveDirections(CBoard *board) ;

};

