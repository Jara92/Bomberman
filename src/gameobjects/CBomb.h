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
     * @param texturePack
     * @param explosionDelay
     */
    CBomb(std::shared_ptr<CTexturePack> texturePack, unsigned int explosionDelay = 2000)
            : CGameObject(std::move(texturePack),
                          false) // Bomb is not passable, but... For owner is passable until the player exits the area of this bomb.
    {}

    CBomb(const CBomb &other) = default;

    CBomb &operator=(const CBomb &other) = default;

    virtual ~CBomb() = default;

    virtual void Update(CBoard *board, int deltaTime) override
    {}

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
    CPlayer * GetOwner() const
    {return this->m_Owner;}

protected:
    CPlayer *m_Owner;
};

