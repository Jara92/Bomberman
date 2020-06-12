/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CEnemy.h"

class CEnemyDump : public CEnemy
{
public:
    /**
    * CEnemyDump contructor
    * @param texturePack Texturepack to be rendered.
    * @param location Starting location. (Must be passable)
    * @param score Score to be claimed.
    * @param size Object size.
    * @param speed Enemy speed
    * @param wallPass Can this Enemy walk through destructible walls?
    * @param lives How many lives doest this monster have?
    */
    explicit CEnemyDump(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size = CCoord<>(1,1), int score = 0,double speed = 0.005, bool wallPass = false, int lives = 1)
    : CEnemy(std::move(texturePack), location, size,score,speed, wallPass, lives)
    {}

    CEnemyDump(const CEnemyDump &other) = default;
    CEnemyDump &operator=(const CEnemyDump &other) = default;
    virtual ~CEnemyDump() = default;

    virtual void Update(CBoard * board, int deltaTime) override;

    int TryKill(unsigned int distance) override;

protected:
    void WalkAround(CBoard & board, int deltaTime);
};

