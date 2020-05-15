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
    * @param isDestructible Is this wall destructible?
    * @param collectible Attached collectible object which will be displayed when the wall is destroyed
    */
    CWall(std::shared_ptr<CTexturePack> texturePack, bool isDestructible = false, CCollectible * collectible = nullptr)
            : CGameObject(texturePack, false), // no wall is passable
    m_IsDestructible(isDestructible), m_Collectible(collectible)
    {}

    CWall(const CWall &other) = default;
    CWall &operator=(const CWall &other) = default;
    virtual ~CWall()
    {}

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
    void TryDestroy(int distance);

protected:
    bool m_IsDestructible;
    CCollectible * m_Collectible;
};

