/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CBlock.h"
#include "../gameobjects/CGameObject.h"
#include "../gameobjects/movables/CPlayer.h"
#include "../CTimer.h"

/**
 * Represents object which could explode - Bomb. Bomb can be triggered by remote control or by timer.
 */
class CBomb : public CBlock
{
public:
    /**
     * Bomb contructor.
     * @param texturePack Texturepack to be rendered.
     * @param size Object size.
     * @param location Object location.
     * @param owner Object owner.
     * @param explosionDelay Time to explode.
     * @param remoteTrigger Must this bomb be triggered to explode by the player?
     */

    CBomb(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1, 1),
          CPlayer *owner = nullptr, int explosionDelay = 2000, bool remoteTrigger = false)
            : CBlock(std::move(texturePack), false, size), m_Owner(owner), m_IsPassableForOwner(true),
              m_RemoteTrigger(remoteTrigger), m_IsTriggered(false), m_ExplosionDelay(explosionDelay)
    {
        // Set auto explosion timer.
        if (!this->m_RemoteTrigger)
        {
            this->m_ExplosionTimer.Run(explosionDelay, [=](void)
            { this->m_IsTriggered = true; });
        }
    }

    CBomb(const CBomb &other) = default;

    CBomb &operator=(const CBomb &other) = default;

    virtual ~CBomb() = default;

    virtual void Update(CBoard &board, int deltaTime) override;

    virtual void PlayerCollision(CCoord<unsigned int> thisLocation, CPlayer &player) override;

    /**
     * Get bombs owner.
     * @return Bombs owner. Nullptr if the bomb has no owner.
     */
    CPlayer *GetOwner() const
    { return this->m_Owner; }

    virtual bool IsPassable(CCoord<unsigned int> thisLocation, const CMovable &movable) const override;

    /**
     * Bomb explosion.
     * @param board
     */
    void Explode(CBoard &board);

protected:
    CPlayer *m_Owner;
    /** Every bomb is passable for owner until the player left bombs cell. */
    bool m_IsPassableForOwner, m_RemoteTrigger, m_IsTriggered;
    int m_ExplosionDelay;
    CTimer m_ExplosionTimer;
};

