/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CGameObject.h"
#include "collectibles/CCollectible.h"

class CWall : public CGameObject
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
    * @param size Object size.
    * @param location Object location
    * @param isDestructible Is this wall destructible?
    * @param collectible Attached collectible object which will be displayed when the wall is destroyed
    */
    CWall(std::shared_ptr<CTexturePack> texturePack, CCoord size = CCoord(1,1), CCoord location = CCoord(0,0), bool isDestructible = false, CCollectible *collectible = nullptr)
            : CGameObject(std::move(texturePack), size, location, false), // no wall is passable
              m_IsDestructible(isDestructible), m_Collectible(collectible)
    {}

    CWall(const CWall &other) = default;

    CWall &operator=(const CWall &other) = default;

    virtual ~CWall() = default;

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard *board, int deltaTime) override
    {}

    /**
    * Try to destroy the wall.
    * @param distance Distance from the bomb.
    */
    virtual bool TryDestroy(int distance) override;

    bool IsDestructible()
    { return this->m_IsDestructible; }

protected:
    bool m_IsDestructible;
    CCollectible *m_Collectible;
};

