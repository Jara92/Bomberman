/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <functional>
#include "CCollectible.h"

class CBoost : public CCollectible
{
public:
    /**
    * Collectible object contructor
    * @param textures Texturepack to be rendered.
    * @param scoreBonus Bonus to be claimed by collector.
    * @param applyFunction Function which will handle boost Apply.
    */
    explicit CBoost(std::shared_ptr<CTexturePack> texturePack, size_t scoreBonus,
                    std::function<void(const CPlayer *)> applyFunction)
            : CCollectible(std::move(texturePack), scoreBonus), m_Apply(std::move(applyFunction))
    {}

    /**
    * Collectible object contructor
    * @param textures Texturepack to be rendered.
    * @param scoreBonus Bonus to be claimed by collector.
    * @param applyFunction Function which will handle boost Apply.
    * @param duration Collectible duration in seconds. Set 0 for unlimited duration (deactivateFunction will never be called)
    * @param deactivateFunction Function which will handle boost Deactivate.
    */
    explicit CBoost(std::shared_ptr<CTexturePack> texturePack, size_t scoreBonus,
                    std::function<void(const CPlayer *)> applyFunction, int duration,
                    std::function<void(const CPlayer *)> deactivateFunction)
            : CCollectible(std::move(texturePack), scoreBonus, duration), m_Apply(std::move(applyFunction)),
              m_Deactivate(std::move(deactivateFunction))
    {}


    CBoost(const CBoost &other) = default;

    CBoost &operator=(const CBoost &other) = delete;

    virtual ~CBoost() = default;

    virtual void Update(CBoard *board, int deltaTime) override;

    virtual void Apply(CPlayer *player);

protected:
    std::function<void(const CPlayer *)> m_Apply;
    std::function<void(const CPlayer *)> m_Deactivate;

    /**
    * Deativate collectible.
    */
    virtual void Deactivate();
};
