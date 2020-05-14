/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <cmath>
#include "CMovable.h"
#include "../../CControls.h"

class CPlayer : public CMovable
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
     * @param isPassable Is this object passable for movable objects?
    */
    explicit CPlayer(std::shared_ptr<CTexturePack> texturePack, CCoord location, CControls *controls,
                     double speed = 0.0025)
            : CMovable(std::move(texturePack), location, speed, false), m_Controls(controls)
    {}

    // I do not want to allow copying players. Every player object has his own controls and copying may cause troubles.
    CPlayer(const CPlayer &other) = delete;
    CPlayer &operator=(const CPlayer &other) = delete;

    virtual ~CPlayer();

    /**
     * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard *board, int deltaTime) override;

    void VerticalMove(CBoard * board, int deltaTime);
    void HorizontalMove(CBoard * board, int deltaTime);

    /**
     * Center vertical players position.
     * @param board Game board
     * @param deltaTime DeltaTime
     * @param direction
     */
    void VerticalCenter(CBoard * board, int deltaTime, int direction);
    void HorizontalCenter(CBoard * board, int deltaTime, int direction);

    /**
     * Is the square determined by two points free?
     * @param board Game board
     * @param p1 First point
     * @param p2 Second point
     * @return True - Location is free; False - Location is not free
     */
    bool LocationIsFree(CBoard *board, CCoord p1, CCoord p2) const;

    bool LocationIsFree(CBoard *board, CCoord p1, CCoord p2, CCoord p3, CCoord p4) const;

    void HandleInput(const Uint8 *keyState);

    /**
    * Place bomb on the ground if it is possible.
    * @param board Game board
    */
    void TryPlaceBomb(CBoard *board);

    /**
 * Boosts interface
 * @param ammount
 */
    void IncreseScore(size_t ammount)
    { this->m_Score += ammount; }

    void SpeedUp()
    { this->m_Speed *= 1.1; /* TODO setup contants */}

    void SpeedDown()
    { this->m_Speed /= 1.1; /* TODO setup contants */    }

    void IncreseExplosionRadius()
    { this->m_ExplosionRadius++; }

    void DecreseExplosionRadius()
    {
        // Minimum value is 1
        if (this->m_ExplosionRadius > 1)
        { this->m_ExplosionRadius--; }
    }

    void IncreseMaxBombs(size_t ammount)
    { this->m_MaxBombs++; }

    void DecreseMaxBombs()
    {
        // Minimum value is 1
        if (this->m_MaxBombs > 1)
        { this->m_MaxBombs--; }
    }

    void ActivateRemoteExplosion()
    { this->m_RemoteExplosion = true; }

    void DeactivateRemoteExplosion()
    { this->m_RemoteExplosion = false; }

    void ActivateBombPass()
    { this->m_BombPass = true; }

    void DeactivateBombPass()
    { this->m_BombPass = false; }

    void ActivateWallPass()
    { this->m_WallPass = true; }

    void DeactivateWallPass()
    { this->m_BombPass = false; }

    void ActivateFireImmunity()
    { this->m_FireImmunity = true; }

    void DeactivateFireImmunity()
    { this->m_FireImmunity = false; }

    void ActivateLevelUp()
    { this->m_LevelUp = true; }

    void DeactivateLevelUp()
    { this->m_LevelUp = false; }

    void DecreseActivateBombs()
    {
        // Minimum value is 0
        if (this->m_ActiveBombs > 0)
        { this->m_ActiveBombs--; }
    }

    size_t GetScore() const
    { return this->m_Score; }

    bool GetLevelUp() const
    {
        return this->m_LevelUp;
    }

protected:
    size_t m_Score;
    size_t m_ExplosionRadius;
    size_t m_MaxBombs;
    size_t m_ActiveBombs;
    bool m_RemoteExplosion;
    bool m_BombPass;
    bool m_FireImmunity;

    bool m_IsPlanting;
    bool m_IsDetonating;
    bool m_LevelUp;

    CControls *m_Controls;

    /*EDirection m_HorizontalMoveDirection;
    EDirection m_VerticalMoveDirection;*/
    const Uint8 * m_Input;

};

