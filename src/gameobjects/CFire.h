/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CGameObject.h"
#include "CBlock.h"

/**
 * Represents fire caused by bomb explosion. Collision with fire will kill movable objects and destroy destructible walls.
 */
class CFire : public CBlock
{
public:
    /**
     * Fire contructor.
     * @param texturePack Textures to be rendered.
     * @param location Object location.
     * @param size Object size.
     * @param duration Duration of this fire in miliseconds.
     */
    explicit CFire(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1, 1),
                   unsigned int duration = 750)
            : CBlock(std::move(texturePack), true, size), m_Duration(duration), m_DurationCounter(0)
    {}

    CFire(const CFire &other) = default;

    CFire &operator=(const CFire &other) = default;

    virtual ~CFire() = default;

    virtual void Update(CBoard &board, int deltaTime) override;

    virtual bool IsDestructible() const override
    { return true; }

    virtual bool TryDestroy(unsigned int distance) override
    {
        this->m_DurationCounter = 0;
        return false;
    }

protected:
    unsigned int m_Duration;
    unsigned int m_DurationCounter;
};

