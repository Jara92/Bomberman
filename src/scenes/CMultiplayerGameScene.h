/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include "CGameScene.h"

class CMultiplayerGameScene : public CGameScene
{
public:
    /**
     * Constructor.
     * @param interface Interface to be used.
     */
    explicit CMultiplayerGameScene(CSDLInterface &interface)
    : CGameScene(interface)
    { }

    virtual ~CMultiplayerGameScene() = default;

    CMultiplayerGameScene (const CMultiplayerGameScene &other) = delete;

    CGameScene &operator=(const CMultiplayerGameScene &other) = delete;

    virtual void Init() override;

protected:
    std::unique_ptr<CText> m_WinnerText;

    virtual void Update(int deltaTime) override;

    virtual void GameOver() override ;

    virtual void DrawGameOver() const override ;
};

