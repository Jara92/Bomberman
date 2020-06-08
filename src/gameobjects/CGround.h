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
    * @param texturePack Texturepack to be rendered.
    * @param size Object size.
    * @param location Object location.
    */
    CGround(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1,1), CCoord<> location = CCoord<>(0,0))
    : CGameObject(std::move(texturePack), size, location, true) // Every ground is passable...
    {}

    CGround(const CGround &other) = default;

    CGround &operator=(const CGround &other) = default;

    virtual ~CGround() = default;

    virtual void Update(CBoard * board, int deltaTime) override
    {}
};

