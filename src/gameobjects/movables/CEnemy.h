/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <set>
#include "CMovable.h"

class CEnemy : public CMovable
{
public:
    /**
    * CEnemy contructor
    * @param textures Texturepack to be rendered.
    * @param location Starting location. (Must be passable)
    * @param speed Enemy speed
    * @param wallPass Can this Enemy walk through destructible walls?
    * @param lives How many lives doest this monster have?
    */
    explicit CEnemy(std::shared_ptr<CTexturePack> texturePack, CCoord location, int score = 100, double speed = 0.005, bool wallPass = false, int lives = 1)
    : CMovable(std::move(texturePack), location, speed, wallPass, lives), m_Score(score)
    {}

    CEnemy(const CEnemy &other) = default;
    CEnemy &operator=(const CEnemy &other) = default;
    virtual ~CEnemy() = default;

    virtual void Update(CBoard * board, int deltaTime) override = 0;

    virtual int TryKill(unsigned int distance) = 0;

protected:
    int m_Score;

    std::set<EDirection> GetPossibleMoveLocations(CBoard * board) const;
};

