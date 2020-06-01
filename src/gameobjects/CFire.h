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
     * @param texturePack Textures to be rendered.
     * @param location Object location.
     * @param duration Duration of this fire in miliseconds.
     */
    explicit CFire(std::shared_ptr<CTexturePack> texturePack, CCoord location = CCoord(0,0), unsigned int duration = 1000)
    : CGameObject(std::move(texturePack), location, false) // Fire is not passable
    , m_Duration(duration), m_DurationCounter(0)
    {}

    CFire(const CFire &other) = default;

    CFire &operator=(const CFire &other) = default;

    virtual ~CFire() = default;

    virtual void Update(CBoard * board, int deltaTime) override;

protected:
    unsigned int m_Duration;
    unsigned int m_DurationCounter;
};

