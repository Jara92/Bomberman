/**
 * @author Jaroslav Fikar
*/

#pragma once
#include "CSDLInterface.h"
#include "scenes/CGameScene.h"
#include "scenes/CMultiplayerGameScene.h"
#include "scenes/CSoloGameScene.h"
#include "scenes/CMenuScene.h"
#include "scenes/CSettingsScene.h"
#include "Messages.h"

class CApplication
{
public:
    int Run(int argc, char * argv[]);

protected:
    CSettings Init(int argc, char * argv[]);

    /**
     * Get scene by application state.
     * @param interface Interface to be used.
     * @param applicationStatus Application state.
     * @throws std::invalid_argument When the application state is invalid.
     * @return Scene to be run.
     */
    std::shared_ptr<CScene> GetSceneByApplicationState(CSDLInterface & interface, EApplicationStatus applicationStatus) const;
};

