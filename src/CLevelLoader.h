/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "CBoard.h"
#include "CSDLInterface.h"
#include "Messages.h"


class CLevelLoader
{
public:
    CLevelLoader(CSDLInterface * interface)
            : m_Interface(interface)
    {}
    ~CLevelLoader() = default;
    CLevelLoader(const CLevelLoader &mapLoader) = delete;
    CLevelLoader operator=(const CLevelLoader &mapLoader) = delete;

    CBoard *GetBoard(int playersCount, CSettings *settings);

    bool LoadLevel(CBoard &board, size_t level);

protected:
    static const std::string MAP_FILE_NAME;
    // map size
    static const size_t MAP_WIDTH = 24;
    static const size_t MAP_HEIGHT = 13;
    static const size_t MAX_PLAYERS = 2;
    CSDLInterface *m_Interface;

    CGameObject *** LoadMap();
    std::vector<CPlayer *> LoadPlayers(int count);
};

