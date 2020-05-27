/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CGameObject.h"

/**
 * Represents fire caused by bomb explosion. Collision with fire will kill movable objects and destroy destructible walls.
 */
class CFire : public CGameObject
{
public:
    /**
     * Fire contructor.
     * @param texturePack Textures.
     * @param duration Duration of this fire.
     */
    CFire(std::shared_ptr<CTexturePack> texturePack, unsigned int duration)
    : CGameObject(std::move(texturePack), false) // Fire is not passable, but... For owner is passable until the player exits the area of this bomb.
    , m_Duration(duration)
    {}

    CFire(const CFire &other) = default;

    CFire &operator=(const CFire &other) = default;

    virtual ~CFire() = default;

    virtual void Update(CBoard * board, int deltaTime) override
    {}

protected:
    unsigned int m_Duration;
};

