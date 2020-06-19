/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <functional>
#include "CScene.h"
#include "CGameScene.h"
#include "../CSDLInterface.h"
#include "../CGameClock.h"
#include "../CBoard.h"
#include "../CLevelLoader.h"
#include "../enums/EGameStatus.h"
#include "../CTimer.h"
#include "../CScoreSaver.h"

class CSoloGameScene : public CGameScene
{
public:
    /**
    * Constructor.
    * @param interface Interface to be used.
    */
    explicit CSoloGameScene(CSDLInterface &interface)
    : CGameScene(interface)
    {  }

    virtual ~CSoloGameScene() = default;

    CSoloGameScene(const CSoloGameScene &other) = delete;

    CSoloGameScene &operator=(const CSoloGameScene &other) = delete;

    virtual void Init() override;

protected:
    virtual void Update(int deltaTime) override;

    virtual void GameOver() override ;
};

