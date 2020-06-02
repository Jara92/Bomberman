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
     * @param size Object size.
    * @param location Object location.
    * @param scoreBonus Bonus to be claimed by collector.
    */
    explicit CDoor(std::shared_ptr<CTexturePack> texturePack, CCoord size = CCoord(1, 1),
                   CCoord location = CCoord(0, 0), size_t scoreBonus = 0)
            : CCollectible(std::move(texturePack), size, location, scoreBonus)
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

