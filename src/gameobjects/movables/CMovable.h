/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once


#include "../CGameObject.h"
#include "../../EDirection.h"

class CMovable : public CGameObject
{
public:
    /**
     * Object which can move in board.
     * @param texturePack Textures to be rendered
     * @param location Starting location
     * @param speed  Starting speed
     * @param wallPass Can this object walk through destructible walls?
     * @param lives Starting lives count
     */
    explicit CMovable(std::shared_ptr<CTexturePack> texturePack, CCoord location, double speed, bool wallPass,
                      int lives)
            : CGameObject(std::move(texturePack), location, true), // every movable object is passable
              m_StartingLocation(location), m_Speed(speed), m_WallPass(wallPass),
              m_VerticalMovingDirection(EDirection::DIRECTION_NONE),
              m_HorizontalMovingDirection(EDirection::DIRECTION_NONE), m_Lives(lives)
    {}

    CMovable(const CMovable &other) = default;

    CMovable &operator=(const CMovable &other) = default;

    virtual ~CMovable() = default;

    /**
     * Draw gameobject
     * @param interface
     * @param cellSize
     * @param offset
     */
    virtual void Draw(CSDLInterface *interface, int cellSize, CCoord offset = CCoord(0, 0)) const;

    virtual void Update(CBoard *board, int deltaTime)
    { CGameObject::Update(board, deltaTime); }


    virtual void Animate(int deltaTime) override;

    /**
     * Get object location cell.
     * @return Coordinates of cell where the left-top corner of this object is located.
     */
    CCoord GetLocationCell() const
    { return CCoord(floor(this->m_Location.m_X + 0.5), floor(this->m_Location.m_Y + 0.5)); }

    void Reset();

    int GetLives() const
    { return this->m_Lives; }


protected:
    CCoord m_StartingLocation;
    double m_Speed;
    bool m_WallPass;
    // EDirection m_MovingDirection;
    EDirection m_VerticalMovingDirection;
    EDirection m_HorizontalMovingDirection;
    int m_Lives;

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

