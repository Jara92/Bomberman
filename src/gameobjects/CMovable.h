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
    explicit CMovable(std::shared_ptr<CTexturePack> texturePack, CCoord location, double speed, bool wallPass)
            : CGameObject(texturePack, true), // every movable object is passable
              m_Location(location), m_Speed(speed), m_WallPass(wallPass), m_MovingDirection(EDirection::DIRECTION_NONE)
    {}

    CMovable(const CMovable &other) = default;

    CMovable &operator=(const CMovable &other) = delete;

    virtual ~CMovable() = default;

    /**
     * Draw gameobject
     * @param interface
     * @param cellSize
     * @param offset
     */
    virtual void Draw(CSDLInterface *interface, int cellSize, CCoord offset = CCoord(0, 0)) const;

protected:
    CCoord m_Location;
    double m_Speed;
    bool m_WallPass;
    EDirection m_MovingDirection;

    /**
     * Draw gameobject at location.
     * @param interface SDL Interface
     * @param cellSize Cellsize
     * @param location Location
     * @param offset Offset
     */
    virtual void
    Draw(CSDLInterface *interface, int cellSize, CCoord location, CCoord offset = CCoord(0, 0)) const override
    {
        CGameObject::Draw(interface, cellSize, location, offset);
    }
};

