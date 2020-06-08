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
     * @param size Object size.
     * @param speed  Starting speed
     * @param wallPass Can this object walk through destructible walls?
     * @param lives Starting lives count
     */
    explicit CMovable(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1,1), CCoord <>location = CCoord<>(0,0), double speed = 0.005, bool wallPass = false,
                      int lives = 1)
            : CGameObject(std::move(texturePack), size, location, true), // every movable object is passable
              m_StartingLocation(location), m_Speed(speed), m_WallPass(wallPass),
              m_VerticalMovingDirection(EDirection::DIRECTION_NONE),
              m_HorizontalMovingDirection(EDirection::DIRECTION_NONE), m_Lives(lives)
    {}

    CMovable(const CMovable &other) = default;

    CMovable &operator=(const CMovable &other) = default;

    virtual ~CMovable() = default;

    virtual void Update(CBoard *board, int deltaTime)
    { CGameObject::Update(board, deltaTime); }


    virtual void Animate(int deltaTime) override;

    /**
     * Get object location cell.
     * @return Coordinates of cell where the left-top corner of this object is located.
     */
    CCoord<unsigned int> GetLocationCell() const
    { return CCoord<unsigned int>(floor(this->m_Location.m_X + 0.5), floor(this->m_Location.m_Y + 0.5)); }

    virtual void Reset();

    int GetLives() const
    { return this->m_Lives; }


protected:
    CCoord <>m_StartingLocation;
    double m_Speed;
    bool m_WallPass;

    EDirection m_VerticalMovingDirection;
    EDirection m_HorizontalMovingDirection;
    int m_Lives;


};

