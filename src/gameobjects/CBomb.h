/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CGameObject.h"
#include "movables/CPlayer.h"

/**
 * Represents object which could explode - Bomb. Bomb can be triggered by remote control or by timer.
 */
class CBomb : public CGameObject
{
public:
    /**
     * Bomb contructor.
     * @param texturePack Texturepack to be rendered.
     * @param explosionDelay Time to explode. Set 0 to activate remote explosion (the bomb will explode only when player trigger explosion)
     */
    CBomb(std::shared_ptr<CTexturePack> texturePack, unsigned int explosionDelay = 2000)
            : CGameObject(std::move(texturePack),
                          false), m_Owner(nullptr), m_IsPassableForOwner(
            true), // Bomb is not passable, but... For owner is passable until the player exits the area of this bomb.
    m_ExplosionDelay(explosionDelay), m_ExplosionCounter(0)
            {}

    CBomb(const CBomb &other) = default;

    CBomb &operator=(const CBomb &other) = default;

    virtual ~CBomb() = default;

    virtual void Update(CBoard *board, int deltaTime) override;

    /**
     * Attach player to this bomb as its owner.
     * @param player
     */
    void SetOwner(CPlayer *player)
    { if (!this->m_Owner) this->m_Owner = player; }

    /**
     * Get bombs owner.
     * @return Bombs owner. Nullptr if the bomb has no owner.
     */
    CPlayer *GetOwner() const
    { return this->m_Owner; }

    /**
     * Is this bomb passable for its owner?
     * @return True - is passable.
     */
    bool IsPassableForOwner() const
    { return this->m_IsPassableForOwner; }

    void MakeUnpassableForOwner()
    { this->m_IsPassableForOwner = false; }

    /**
     * Bomb explosion.
     */
    void Detonate(CBoard * board);

protected:
    CPlayer *m_Owner;
    /** Every bomb is passable for owner until the player left bombs cell. */
    bool m_IsPassableForOwner;
    unsigned int m_ExplosionDelay;
    unsigned int m_ExplosionCounter;
};

