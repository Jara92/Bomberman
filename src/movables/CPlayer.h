/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <cmath>
#include <set>
#include "CMovable.h"
#include "../CControls.h"

/** Player which can be controlled. Every player has his own controls and can move in game map. */
class CPlayer : public CMovable
{
public:
    /**
    * Game object contructor
    * @param texturePack Texturepack to be rendered.
     * @param location Player starting location.
     * @param size Object size.
     * @param controls Controls object to be used.
     * @param speed Object moving speed.
     * @param lives Object starting lives.
    */
    explicit CPlayer(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size, CControls controls,
                     double speed = 0.0025, int lives = 2)
            : CMovable(std::move(texturePack), size, location, speed, false, true, lives), m_Score(0),
              m_ExplosionRadius(3), m_MaxBombs(15), m_ActiveBombs(0), m_RemoteExplosion(true), m_FireImmunity(false),
              m_PlantingAvaible(false), m_IsPlanting(false), m_DetonatingAvaible(false), m_IsDetonating(false),
              m_LevelUp(false), m_Controls(controls)
    {}

    CPlayer(const CPlayer &other) = default;

    CPlayer &operator=(const CPlayer &other) = default;

    virtual ~CPlayer() = default;

    /**
     * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard &board, int deltaTime) override;

//    virtual void CollisionWith(CGameObject &other) override ;

    /**
     * Handle keyboard input.
     * @param keyState Keyboard layout
     */
    void HandleInput(const Uint8 *keyState);

    /** Kill the player. */
    void Kill();

    virtual void Reset(CBoard &board) override;

    /**======================
    * Boost interface.
    =========================*/
    void IncreseScore(std::size_t ammount)
    { this->m_Score += ammount; }

    void SpeedUp()
    { this->m_Speed *= CPlayer::SPEED_UP; }

    void SpeedDown()
    { this->m_Speed /= CPlayer::SPEED_UP; }

    void IncreseExplosionRadius()
    { this->m_ExplosionRadius++; }

    void IncreseLiveCount()
    { this->m_Lives++; }

    void DecreseExplosionRadius()
    {
        // Minimum value is 1
        if (this->m_ExplosionRadius > 1)
        { this->m_ExplosionRadius--; }
    }

    void IncreseMaxBombs()
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

    void ActivateFireImmunity()
    { this->m_FireImmunity = true; }

    void DeactivateFireImmunity()
    { this->m_FireImmunity = false; }

    void ActivateLevelUp()
    { this->m_LevelUp = true; }

    void DeactivateLevelUp()
    { this->m_LevelUp = false; }

    void DecreseActiveBombs()
    {
        // Minimum value is 0
        if (this->m_ActiveBombs > 0)
        { this->m_ActiveBombs--; }
    }

    std::size_t GetScore() const
    { return this->m_Score; }

    bool GetLevelUp() const
    { return this->m_LevelUp; }

    bool GetFireImunity() const
    { return this->m_FireImmunity; }

    bool GetRemoteExplosion() const
    { return this->m_RemoteExplosion; }

    unsigned int GetExplosionRadius() const
    { return this->m_ExplosionRadius; }

    bool IsDetonating() const
    { return (this->m_IsDetonating && this->m_RemoteExplosion); }

    static constexpr double ENEMY_SAVE_ZONE = 3;
    static constexpr double OBSTACLES_SAVE_ZONE = 1;
protected:
    /** Achieved score. */
    std::size_t m_Score;

    /*====================
     * Player abilities.
     =====================*/
    unsigned int m_ExplosionRadius;
    unsigned int m_MaxBombs;
    unsigned int m_ActiveBombs;
    bool m_RemoteExplosion;
    bool m_FireImmunity;

    /*====================
     * Player input
     =====================*/
    bool m_PlantingAvaible;
    bool m_IsPlanting;
    bool m_DetonatingAvaible;
    bool m_IsDetonating;
    bool m_LevelUp;
    CControls m_Controls;

    static constexpr double MIN_TURNING_VALUE = 0.5, MAX_TURNING_VALUE = 0.5;
    static constexpr double SPEED_UP = 1.1;

    /**
    * Place bomb on the ground if it is possible.
    * @param board Game board
    */
    void TryPlaceBomb(CBoard &board);

    /**
    * Movement along the axis Y
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    void VerticalMove(CBoard &board, int deltaTime);

    /**
     * Movement along the axis X
     * @param board Game board
     * @param deltaTime DeltaTime
     */
    void HorizontalMove(CBoard &board, int deltaTime);

    /**
     * Center vertical players position.
     * @param board Game board
     * @param deltaTime DeltaTime
     * @param direction Direction
     */
    void VerticalCenter(CBoard &board, int deltaTime, int direction);

    /**
    * Center horiz players position.
    * @param board Game board
    * @param deltaTime DeltaTime
    * @param direction Direction
    */
    void HorizontalCenter(CBoard &board, int deltaTime, int direction);

    /**
     * Update the displayed texture according to the real movement of the player.
     * @param oldLocation Original position before starting the movement.
     */
    void UpdateTextureType(CCoord<> oldLocation);

};

