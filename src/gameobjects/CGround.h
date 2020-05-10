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
    */
    CGround(std::shared_ptr<CTexturePack> texturePack)
    : CGameObject(texturePack, true) // Every ground is passable...
    {}

    CGround(const CGround &other) = default;

    CGround &operator=(const CGround &other) = delete;

    virtual ~CGround() = default;
};

