/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CCollectible.h"

class CDoor : public CCollectible
{
public:
    /**
    * Collectible object contructor
    * @param textures Texturepack to be rendered.
    * @param scoreBonus Bonus to be claimed by collector.
    */
    explicit CDoor(std::shared_ptr<CTexturePack> texturePack, size_t scoreBonus)
            : CCollectible(texturePack, scoreBonus)
    {}

    CDoor(const CDoor &other) = default;

    CDoor &operator=(const CDoor &other) = delete;

    virtual ~CDoor() = default;

    virtual void Update(CBoard *board, int deltaTime) override
    {}

    virtual void Apply(CPlayer *player);

protected:
    virtual void Deactivate()
    {}
};

