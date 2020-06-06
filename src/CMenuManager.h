/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include "CWindowManager.h"

class CMenuManager : public CWindowManager
{
public:
    /**
 * Constructor.
 * @param interface Interface to be used.
 */
    explicit CMenuManager(CSDLInterface *interface);

    ~CMenuManager();
    CMenuManager(const CMenuManager &other) = delete;
    CMenuManager &operator=(const CMenuManager &other) = delete;

    virtual EApplicationStatus Run() override ;

protected:
    bool m_IsRunning;

    SDL_Texture * m_Backround;
    SDL_Texture * m_Title;
    SDL_Texture * m_OnePlayerNormal;
    SDL_Texture * m_OnePlayerHover;
    SDL_Texture * m_TwoPlayersNormal;
    SDL_Texture * m_TwoPlayersHover;

    virtual void Update(int deltaTime) override ;

    virtual void UpdateEvents() override ;

    virtual void Draw() const override ;
};


