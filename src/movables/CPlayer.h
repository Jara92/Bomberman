/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <cmath>
#include <set>
#include "CMovable.h"
#include "../CInput.h"

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
    explicit CPlayer(std::shared_ptr<CTexturePack> texturePack, CCoord<> location, CCoord<> size, CInput controls,
                     double speed = 0.0025, int lives = 3)
            : CMovable(std::move(texturePack), size, location, speed, false, false, lives), m_Score(0),
              m_ExplosionRadius(1), m_MaxBombs(1), m_ActiveBombs(0), m_RemoteExplosion(false), m_FireImmunity(false),
              m_LevelUp(false), m_Input(controls)
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

    virtual void CollisionWith(CCoord<unsigned int > blockLocation, CBlock & block) override ;

    virtual void CollisionWith(CMovable & movable) override ;

    /** Kill to kill the player. */
    virtual unsigned int TryKill(unsigned int distance = 0) override;

    virtual void NextLevel(CBoard &board, bool clearLevelObjects) override;

    /* Boost interface. */
    void IncreseScore(std::size_t amount)
    { this->m_Score += amount; }

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
    { return (this->m_Input.IsDetonating() && this->m_RemoteExplosion); }

    /** Player save zones when generation new map / loading level. */
    static constexpr double ENEMY_SAVE_ZONE = 4, OBSTACLES_SAVE_ZONE = 2;
protected:
    std::size_t m_Score;
    /* Player abilities. */
    unsigned int m_ExplosionRadius, m_MaxBombs, m_ActiveBombs;
    bool m_RemoteExplosion, m_FireImmunity, m_LevelUp;
    CInput m_Input;

    static constexpr double MIN_TURNING_VALUE = 0.5, MAX_TURNING_VALUE = 0.5;
    static constexpr double SPEED_UP = 1.1;

    virtual void UpdateTextureType(CCoord<> oldLocation ) override ;

    /**
     * Handle keyboard input.
     * @param deltaTime Delta time.
     */
    void HandleInput(int deltaTime);

    /**
    * Place bomb on the ground if it is possible.
    * @param board Game board
    */
    void TryPlaceBomb(CBoard &board);

    /**
    * Movement along the axis Y
    * @param board Game board
    */
    void VerticalMove(CBoard &board);

    /**
     * Movement along the axis X
     * @param board Game board
     */
    void HorizontalMove(CBoard &board);

    /**
     * Center vertical players position.
     * @param board Game board
     * @param direction Direction
     */
    void VerticalCenter(CBoard &board, int direction);

    /**
    * Center horiz players position.
    * @param board Game board
    * @param direction Direction
    */
    void HorizontalCenter(CBoard &board, int direction);
};

