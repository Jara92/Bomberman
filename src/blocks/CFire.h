/**
 * @author Jaroslav Fikar
*/

#pragma once

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
     * @param owner Fire owner.
     * @param size Object size.
     * @param duration Duration of this fire in miliseconds.
     */
    explicit CFire(std::shared_ptr<CTexturePack> texturePack, CPlayer *owner, CCoord<> size = CCoord<>(1, 1),
                   unsigned int duration = 750);

    CFire(const CFire &other) = default;

    CFire &operator=(const CFire &other) = default;

    virtual ~CFire() = default;

    virtual void Update(CBoard &board, int deltaTime) override;

    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override
    { this->m_IsDestroyed = true; }

    virtual void CollisionWith(CCoord<unsigned int> thisLocation, CPlayer &player) override;

    virtual void CollisionWith(CCoord<unsigned int> thisLocation, CEnemy &enemy) override;

    virtual bool IsExplodeable() const override
    { return true; }

    virtual bool TryExplode(unsigned int distance) override
    {
        // The fire was "recovered".
        this->m_ExpirationTimer.Reset();
        return true;
    }

protected:
    CTimer m_ExpirationTimer;
    CPlayer *m_Owner;
};

