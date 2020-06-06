/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once
#include <queue>
#include "CSDLInterface.h"
#include "CGameManager.h"
#include "CMenuManager.h"
#include "CSettingsManager.h"
#include "Messages.h"

class CApplication
{
public:
    CApplication() = default;
    ~CApplication() = default;
    CApplication (const CApplication & other) = default;
    CApplication & operator = (const CApplication & other) = default;

    int Run(int argc, char * argv[]);

protected:
    std::shared_ptr<CSettings> Init(int argc, char * argv[]);

    std::shared_ptr<CWindowManager> GetWindowManagerByState(CSDLInterface * interface, EApplicationStatus applicationStatus) const;
};

