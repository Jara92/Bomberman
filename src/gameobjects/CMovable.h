/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once


#include "CGameObject.h"
#include "../EDirection.h"

class CMovable : public CGameObject
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
     * @param isPassable Is this object passable for movable objects?
    */
    explicit CMovable(std::shared_ptr<CTexturePack> texturePack, CCoord location, double speed = 0.001)
            : CGameObject(texturePack, true), // every movable object is passable
              m_Location(location), m_Speed(speed), m_MovingDirection(EDirection::DIRECTION_NONE)
    {}

    CMovable(const CMovable &other) = default;

    CMovable &operator=(const CMovable &other) = delete;

    virtual ~CMovable() = default;

protected:
    CCoord m_Location;
    double m_Speed;
    EDirection m_MovingDirection;
};

