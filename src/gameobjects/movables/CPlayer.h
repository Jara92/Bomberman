/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <cmath>
#include "CMovable.h"
#include "../../CControls.h"

/**
 * Player which can be controlled. Every player has his own controls and can move in game map.
 */
class CPlayer : public CMovable
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
     * @param location Player starting location.
     * @param size Object size.
     * @param controls Controls object to be used.
     * @param speed Object moving speed.
     * @param lives Object starting lives.
    */
    explicit CPlayer(std::shared_ptr<CTexturePack> texturePack, CCoord location, CCoord size = CCoord(1, 1),
                     CControls *controls = nullptr,
                     double speed = 0.0025, int lives = 3)
            : CMovable(std::move(texturePack), size, location, speed, false, lives), m_Score(0), m_ExplosionRadius(1),
              m_MaxBombs(1), m_ActiveBombs(0), m_RemoteExplosion(false), m_BombPass(false), m_FireImmunity(false),
              m_PlantingAvaible(false), m_IsPlanting(false), m_DetanatingAvaible(false), m_IsDetonating(false),
              m_LevelUp(false), m_Controls(controls)
    {/*this->m_Lives = 0;*/}

    CPlayer(const CPlayer &other) = default;
    CPlayer &operator=(const CPlayer &other) = default;

    virtual ~CPlayer();

    /**
     * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard *board, int deltaTime) override;

    /**
     * Handle keyboard input.
     * @param keyState Keyboard layout
     */
    void HandleInput(const Uint8 *keyState);

    /**
    * Place bomb on the ground if it is possible.
    * @param board Game board
    */
    void TryPlaceBomb(CBoard *board);

    /**
     * Kill the player.
     */
    void Kill();

    /**
     * Reset the player and prepare for a next round.
     */
    virtual void Reset();

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

    void DecreseExplosionRadius()
    {
        // Minimum value is 1
        if (this->m_ExplosionRadius > 1)
        { this->m_ExplosionRadius--; }
    }

    void IncreseMaxBombs(unsigned int ammount)
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

    bool GetWallPass() const
    { return this->m_WallPass; }

    bool GetBombPass() const
    { return this->m_BombPass; }

    bool GetFireImmunity() const
    { return this->m_FireImmunity; }

    unsigned int GetExplosionRadius() const
    { return this->m_ExplosionRadius; }

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
    bool m_BombPass;
    bool m_FireImmunity;

    /*====================
     * Player input
     =====================*/
    bool m_PlantingAvaible;
    bool m_IsPlanting;
    bool m_DetanatingAvaible;
    bool m_IsDetonating;
    bool m_LevelUp;

    CControls *m_Controls; // TODO předělat (problém s kopírovacím konstruktorem)

    static constexpr double MIN_TURNING_VALUE = 0.5;
    static constexpr double MAX_TURNING_VALUE = 0.5;
    static constexpr double SPEED_UP = 1.1;

    /**
 * Movement along the axis Y
 * @param board Game board
 * @param deltaTime DeltaTime
 */
    void VerticalMove(CBoard *board, int deltaTime);

    /**
     * Movement along the axis X
     * @param board Game board
     * @param deltaTime DeltaTime
     */
    void HorizontalMove(CBoard *board, int deltaTime);

    /**
     * Center vertical players position.
     * @param board Game board
     * @param deltaTime DeltaTime
     * @param direction Direction
     */
    void VerticalCenter(CBoard *board, int deltaTime, int direction);

    /**
    * Center horiz players position.
    * @param board Game board
    * @param deltaTime DeltaTime
    * @param direction Direction
    */
    void HorizontalCenter(CBoard *board, int deltaTime, int direction);

    /**
     * Is current location free?
     */
    bool LocationIsFree(CBoard *board) const;
};

