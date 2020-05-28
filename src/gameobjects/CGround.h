/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CGameObject.h"

class CGround : public CGameObject
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
    * @param location Object location.
    */
    CGround(std::shared_ptr<CTexturePack> texturePack, CCoord location = CCoord(0,0))
    : CGameObject(std::move(texturePack), location, true) // Every ground is passable...
    {}

    CGround(const CGround &other) = default;

    CGround &operator=(const CGround &other) = default;

    virtual ~CGround() = default;

    virtual void Update(CBoard * board, int deltaTime) override
    {}
};

