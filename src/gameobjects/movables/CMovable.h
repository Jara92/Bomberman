/**
 * @author Jaroslav Fikar
*/

#pragma once

#include "../CGameObject.h"

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
    explicit CMovable(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1, 1),
                      CCoord<> location = CCoord<>(0, 0), double speed = 0.005, bool wallPass = false,
                      bool bombPass = false, int lives = 1)
            : CGameObject(std::move(texturePack), size, location), // every movable object is passable
              m_StartingLocation(location), m_Speed(speed), m_WallPass(wallPass), m_BombPass(bombPass),
              m_Movement(CCoord<>(0, 0)), m_Lives(lives)
    {}

    CMovable(const CMovable &other) = default;

    CMovable &operator=(const CMovable &other) = default;

    virtual ~CMovable() = default;

    virtual void Update(CBoard &board, int deltaTime)
    { CGameObject::Update(board, deltaTime); }

    bool GetWallPass() const
    { return this->m_WallPass; }

    bool GetBombPass() const
    { return this->m_BombPass; }

    void ActivateBombPass()
    { this->m_BombPass = true; }

    void DeactivateBombPass()
    { this->m_BombPass = false; }

    void ActivateWallPass()
    { this->m_WallPass = true; }

    void DeactivateWallPass()
    { this->m_BombPass = false; }

    virtual void Reset(CBoard & board) override;

    int GetLives() const
    { return this->m_Lives; }

protected:
    CCoord<> m_StartingLocation;
    double m_Speed;
    bool m_WallPass, m_BombPass;

    CCoord<> m_Movement;
    int m_Lives;

    virtual void Animate(int deltaTime) override;

    /** Is current location free? */
    virtual bool CellIsFree(CBoard &board, int deltaTime, CCoord<> location) const;
};

