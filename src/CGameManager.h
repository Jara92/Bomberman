/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CSDLInterface.h"
#include "CClock.h"
#include "CBoard.h"
#include "CLevelLoader.h"

class CGameManager
{
public:
    CGameManager(CSDLInterface *interface);
    ~CGameManager() = default;
    CGameManager (const CGameManager & other) = delete;
    CGameManager & operator = (const CGameManager & other) = delete;

    void Init();
    void Run();

protected:
    CSDLInterface * m_Interface;
    CBoard * m_Board;
    CLevelLoader * m_LevelLoader;
    CClock m_Clock;
    bool m_GameIsRunning;

    void Draw() const;
    void Update(int deltaTime);
};

