/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <functional>
#include "CCollectible.h"
#include "../../CTimer.h"

class CBoost : public CCollectible
{
public:
    /**
    * Collectible object contructor
    * @param texturePack Texturepack to be rendered.
    * @param size Object size.
    * @param scoreBonus Bonus to be claimed by collector.
    * @param applyFunction Function which will handle boost Apply.
    */
    explicit CBoost(std::shared_ptr<CTexturePack> texturePack, std::function<void(CPlayer *)> applyFunction,
                    CCoord<> size = CCoord<>(1, 1), size_t scoreBonus = 0)
            : CCollectible(std::move(texturePack), size, scoreBonus, 0),
              m_Apply(std::move(applyFunction))
    {}

    /**
    * Collectible object contructor
    * @param texturePack Texturepack to be rendered.
    * @param size Object size.
    * @param scoreBonus Bonus to be claimed by collector.
    * @param applyFunction Function which will handle boost Apply.
    * @param duration Collectible duration in seconds. Set 0 for unlimited duration (deactivateFunction will never be called)
    * @param deactivateFunction Function which will handle boost Deactivate.
    */
    explicit CBoost(std::shared_ptr<CTexturePack> texturePack, std::function<void(CPlayer *)> applyFunction,
                    int duration, std::function<void(const CPlayer *)> deactivateFunction,
                    CCoord<> size = CCoord<>(1, 1), std::size_t scoreBonus = 0)
            : CCollectible(std::move(texturePack), size, scoreBonus, duration),
              m_Apply(std::move(applyFunction)), m_Deactivate(std::move(deactivateFunction))
    {}

    CBoost(const CBoost &other) = default;

    CBoost &operator=(const CBoost &other) = default;

    virtual ~CBoost() = default;

    virtual void Update(CBoard &board, int deltaTime) override;

protected:
    std::function<void(CPlayer *)> m_Apply;
    std::function<void(CPlayer *)> m_Deactivate;

    virtual void Apply(const CBoard & board, CPlayer &player) override ;

    virtual void Deactivate();
};
