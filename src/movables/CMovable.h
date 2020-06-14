/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <memory>
#include "../CTexturePack.h"

class CBoard;

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
            : m_TexturePack(std::move(texturePack)), m_ActualTexture(ETextureType::TEXTURE_FRONT), m_Size(size),
              m_Location(location), m_StartingLocation(location), m_Speed(speed), m_WallPass(wallPass),
              m_BombPass(bombPass), m_Movement(CCoord<>(0, 0)), m_Lives(lives), m_AnimationIndex(0),
              m_AnimationUpdateInterval(100), m_AnimationTimer(0)
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
    { this->Animate(deltaTime); }

    /**
     * Draw the gameobject
     * @param interface Interface
     * @param cellSize Cellsize
     * @param location Target cell location
     * @param offset Texture global offset
     */
    virtual void
    Draw(CSDLInterface &interface, int cellSize, CCoord<> location, CCoord<> offset = CCoord<>(0, 0)) const;

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

    /** Reset the object and prepare for a next round. */
    virtual void Reset(CBoard &board);

    /**
    * Are these objects colliding?
    * @param other Other object
    */
    bool IsColliding(const CMovable *other) const;

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

    int GetLives() const
    { return this->m_Lives; }

protected:
    /** Texturepack which is used for rendering. */
    std::shared_ptr<CTexturePack> m_TexturePack;
    /** Actual texture type to be rendered. */
    ETextureType m_ActualTexture;
    /** Is this object passable for other objects? */
    bool m_IsAlive;
    CCoord<> m_Size, m_Location, m_StartingLocation;
    double m_Speed;
    bool m_WallPass, m_BombPass;

    CCoord<> m_Movement;
    int m_Lives;

    /* Mutable keyword is very useful here. Animation index is not important for CGameObject, because it
    * does not disrupt the internal structure of the object. It is just auxiliary variable.*/
    mutable unsigned int m_AnimationIndex;
    unsigned int m_AnimationUpdateInterval;
    unsigned int m_AnimationTimer;

    /**
    * Update animation state
    * @param deltaTime DeltaTime
    */
    virtual void Animate(int deltaTime);

    /** Is current location free? */
    virtual bool CellIsFree(CBoard &board, int deltaTime, CCoord<> location) const;

    /**
    * Returns the texture to be rendered.
    * @return SDL_Texture * to be rendered. Nullptr if there is no texture (this should never happen).
    */
    SDL_Texture *GetTexture() const
    {
        SDL_Texture *texture = this->m_TexturePack.get()->GetTexture(this->m_ActualTexture, &(this->m_AnimationIndex));
        return texture;
    }
};
