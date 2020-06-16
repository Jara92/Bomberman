/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CEnemy.h"

class CEnemyDumb : public CEnemy
{
public:
    /**
    * CEnemyDumb contructor
    * @param texturePack Texturepack to be rendered.
    * @param location Starting location. (Must be passable)
    * @param score Score to be claimed.
    * @param size Object size.
    * @param speed Enemy speed
    * @param wallPass Can this Enemy walk through destructible walls?
    * @param lives How many lives doest this monster have?
    */
    explicit CEnemyDumb(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size = CCoord<>(1, 1), int score = 0, double speed = 0.005, bool wallPass = false, int lives = 1)
    : CEnemy(std::move(texturePack), location, size,score,speed, wallPass, lives)
    {}

    CEnemyDumb(const CEnemyDumb &other) = default;
    CEnemyDumb &operator=(const CEnemyDumb &other) = default;
    virtual ~CEnemyDumb() = default;

    virtual void Update(CBoard & board, int deltaTime) override;

    unsigned int TryKill(unsigned int distance) override;

protected:
    virtual void Move(const CBoard & board, int deltaTime ) override ;
};

