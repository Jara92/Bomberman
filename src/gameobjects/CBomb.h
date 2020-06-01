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
     * @param location Object location.
     * @param owner Object owner.
     * @param explosionDelay Time to explode. Set 0 to activate remote explosion (the bomb will explode only when player trigger explosion)
     */
    CBomb(std::shared_ptr<CTexturePack> texturePack, CCoord location, CPlayer * owner, unsigned int explosionDelay = 1000)
            : CGameObject(std::move(texturePack),
                          location, false), m_Owner(owner), m_IsPassableForOwner(
            true), // Bomb is not passable, but... For owner is passable until the player exits the area of this bomb.
    m_ExplosionDelay(explosionDelay), m_ExplosionCounter(0)
            {}

    CBomb(const CBomb &other) = default;

    CBomb &operator=(const CBomb &other) = default;

    virtual ~CBomb() = default;

    virtual void Update(CBoard *board, int deltaTime) override;

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
     * Bomb detonation.
     * Check if the bomb is ready to be detonated.
     */
    void Detonate(CBoard * board);

    /**
     * Bomb explosion.
     * @param board
     */
    void Explode(CBoard * board);

    static constexpr double COLLISION_TOLERANCE = 0.05;
protected:
    CPlayer *m_Owner;
    /** Every bomb is passable for owner until the player left bombs cell. */
    bool m_IsPassableForOwner;
    unsigned int m_ExplosionDelay;
    unsigned int m_ExplosionCounter;
};

