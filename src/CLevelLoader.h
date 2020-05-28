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
    CLevelLoader(CSDLInterface *interface)
            : m_Interface(interface)
    {}

    ~CLevelLoader() = default;

    CLevelLoader(const CLevelLoader &mapLoader) = delete;

    CLevelLoader operator=(const CLevelLoader &mapLoader) = delete;

    CBoard *GetBoard(int playersCount, CSettings *settings);

    bool LoadLevel(CBoard *board, size_t level);

protected:
    static const std::string MAP_FILE_NAME;
    static const std::string LEVEL_FILE_NAME;
    // Saved map size
    static const size_t FILE_MAP_WIDTH = 24;
    static const size_t FILE_MAP_HEIGHT = 13;
    // Real map size (Real map is smaller because the map is saved as binary file. I have to remember which bits are valid)
    static const size_t MAP_WIDTH = 23;
    static const size_t MAP_HEIGHT = 13;

    static const size_t MAX_PLAYERS = 2;
    CSDLInterface *m_Interface;

    std::vector<std::vector<CWall *>> LoadMap();
    std::vector<CPlayer *> LoadPlayers(int count);
    /**
     * Get object which will be rendered as ground.
     * @return Ground object
     */
    CGround * LoadGround();

    /**
     * Generate obstacles for game map.
     * @param board Gameboard
     * @param level Level number
     * @param count Obstacles count
     * @return Container of obstacles.
     */
     void GenerateObstacles(CBoard *board, size_t level, size_t count);


    std::shared_ptr<CTexturePack> LoadBombTexturePack();

    std::shared_ptr<CTexturePack> LoadFireTexturePack();
};

