/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CMovable.h"
#include "../CControls.h"

class CPlayer : public CMovable
{
public:
    /**
    * Game object contructor
    * @param textures Texturepack to be rendered.
     * @param isPassable Is this object passable for movable objects?
    */
    explicit CPlayer(std::shared_ptr<CTexturePack> texturePack, CCoord location, CControls *controls, double speed = 0.001)
            : CMovable(texturePack, location, speed), m_Controls(controls)
    {}

    CPlayer(const CPlayer &other) = default;

    CPlayer &operator=(const CPlayer &other) = delete;

    virtual ~CPlayer();

    /**
     * Updates object state using deltatime.
    * @param board Game board
    * @param deltaTime DeltaTime
    */
    virtual void Update(CBoard *board, int deltaTime) override{}

    void HandleInput(const Uint8 *keyState);

    /**
    * Place bomb on the ground if it is possible.
    * @param board Game board
    */
    void TryPlaceBomb(CBoard * board);

    /**
 * Boosts interface
 * @param ammount
 */
    void IncreseScore(size_t ammount)
    { this->m_Score += ammount; }

    void IncreseSpeed(double ammount)
    { this->m_Speed += ammount; }

    void IncreseExplosionRadius(size_t ammount)
    { this->m_ExplosionRadius += ammount; }

    void IncreseMaxBombs(size_t ammount)
    { this->m_MaxBombs += ammount; }

    void SwitchRemoveExplosion(bool remoteExplosion)
    { this->m_RemoteExplosion = remoteExplosion; }

    void SwitchBombPass(bool bombPass)
    { this->m_BombPass = bombPass; }

    void SwitchFireImmunity(bool fireImmunity)
    { this->m_FireImmunity = fireImmunity; }


    size_t GetScore() const { return  this->m_Score;}

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
};

