/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CCollectible.h"

/** Portal to next level */
class CDoor : public CCollectible
{
public:
    /**
    * Collectible object contructor
    * @param texturePack Texture pack to be rendered.
    * @param size Object size.
    * @param scoreBonus Bonus to be claimed by collector.
    */
    explicit CDoor(std::shared_ptr<CTexturePack> texturePack, CCoord<> size = CCoord<>(1, 1), size_t scoreBonus = 0)
            : CCollectible(std::move(texturePack), size, scoreBonus)
    {}

    CDoor(const CDoor &other) = default;

    CDoor &operator=(const CDoor &other) = default;

    virtual ~CDoor() = default;

    virtual void Update(CBoard &board, int deltaTime) override
    {}

    virtual void Apply(CPlayer &player) override ;

protected:
    virtual void Deactivate()
    {}
};

