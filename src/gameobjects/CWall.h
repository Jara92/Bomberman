/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CGameObject.h"

class CWall : public CGameObject
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
    */
    CWall(std::shared_ptr<CTexturePack> texturePack)
            : CGameObject(texturePack, false) // no wall is passable
    {}

    CWall(const CWall &other) = default;

    CWall &operator=(const CWall &other) = delete;

    virtual ~CWall() = default;

    CWall *Clone()
    {
        std::cerr << this->m_TexturePack.use_count() << std::endl;
        return new CWall(this->m_TexturePack);
    }

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard *board, int deltaTime) override
    {}
};

