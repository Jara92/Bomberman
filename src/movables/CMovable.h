/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <memory>
#include "../CBody.h"
#include "../CTimer.h"

class CBoard;

class CBlock;

class CPlayer;

class CMovable
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
            : m_Body(std::move(texturePack), 100), m_IsAlive(true), m_IsDestroyed(false), m_Size(size),
              m_Location(location), m_StartingLocation(location),
              m_Speed(speed), m_WallPass(wallPass), m_BombPass(bombPass), m_Movement(CCoord<>(0, 0)), m_Lives(lives)
    {}

    CMovable(const CMovable &other) = default;

    CMovable &operator=(const CMovable &other) = default;

    virtual ~CMovable() = default;

    /**
    * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard &board, int deltaTime)
    {
        // Update when moving.
        if (this->m_Movement != CCoord<>(0, 0))
        { this->m_Body.Update(board, deltaTime); }
    }

    /**
     * Draw the gameobject
     * @param interface Interface
     * @param cellSize Cellsize
     * @param location Target cell location
     * @param offset Texture global offset
     */
    virtual void
    Draw(CSDLInterface &interface, int cellSize, CCoord<> offset = CCoord<>(0, 0)) const
    { this->m_Body.Draw(interface, cellSize, this->m_Location, this->m_Size, offset); }

    /**
     * Try to kill this movable.
     * @param distance Distance between the movable and a killer.
     * @return Score to be achieved.
     */
    virtual unsigned int TryKill(unsigned int distance = 0) = 0;

    virtual void CollisionWith(CCoord<unsigned int> blockLocation, CBlock &block) = 0;

    virtual void CollisionWith(CMovable &moavable) = 0;

    virtual void CollisionWithPlayer(CPlayer &player)
    {}

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

    /**
     * Prepare object for next level.
     * @param board Game board.
     * @param clearLevelObjects Objects associated with the level will be deleted.
     */
    virtual void NextLevel(CBoard &board, bool clearLevelObjects);

    /**
    * Are these objects colliding?
    * @param other Other object
    */
    bool IsColliding(const CMovable &other) const
    { return this->m_Body.IsColliding(this->m_Location, this->m_Size, other.m_Location, other.m_Size); }

    void SetLocation(CCoord<> location)
    { this->m_Location = location; }

    CCoord<> GetLocation() const
    { return this->m_Location; }

    /**
    * Get object location cell.
    * @return Coordinates of cell where the center of this object is located.
    */
    CCoord<unsigned int> GetLocationCell() const
    { return CCoord<unsigned int>(floor(this->m_Location.m_X + 0.5), floor(this->m_Location.m_Y + 0.5)); }

    CCoord<> GetSize() const
    { return this->m_Size; }

    /**
     * Is this object alive?
     * @return True is the object is alive.
     */
    bool IsAlive() const
    { return this->m_IsAlive; }

    bool IsDestroyed() const
    { return this->m_IsDestroyed; }

    int GetLives() const
    { return this->m_Lives; }

protected:
    CBody m_Body;
    /** Is this object passable for other objects? */
    bool m_IsAlive, m_IsDestroyed;
    CCoord<> m_Size, m_Location, m_StartingLocation;
    double m_Speed;
    bool m_WallPass, m_BombPass;

    CCoord<> m_Movement;
    int m_Lives;

    /**
    * Update the displayed texture according to the real movement.
    * @param oldLocation Original position before starting the movement.
    */
    virtual void UpdateTextureType(CCoord<> oldLocation)
    { this->UpdateTextureByMovement(oldLocation - this->m_Location); }

    /**
     * Update texture type by difference between the old and the new position.
     * @param diff difference between the old and the new position.
     */
    void UpdateTextureByMovement(CCoord<> diff = {0, 0});

    /** Is current location free? */
    bool LocationIsFree(const CBoard &board) const;
};

