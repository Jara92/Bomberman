/**
 * @author Jaroslav Fikar
 * 
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <random>
#include <chrono>
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
    { }

    ~CLevelLoader() = default;

    CLevelLoader(const CLevelLoader &mapLoader) = delete;

    CLevelLoader operator=(const CLevelLoader &mapLoader) = delete;

    std::shared_ptr<CBoard> GetBoard(int playersCount, CSettings *settings);

    bool LoadLevel(const std::shared_ptr<CBoard> &board, size_t level);

protected:
    static const std::string MAP_FILE_NAME;
    static const std::string LEVEL_FILE_NAME;
    /* Saved map size */
    static const size_t FILE_MAP_WIDTH = 24;
    static const size_t FILE_MAP_HEIGHT = 13;
    /* Real map size (Real map is smaller because the map is saved as binary file. I have to remember which bits are valid) */
    static const size_t MAP_WIDTH = 23;
    static const size_t MAP_HEIGHT = 13;

    static const size_t MAX_PLAYERS = 2;
    CSDLInterface *m_Interface;

    /**
     * Load map from the file.
     * @return Map saved in 2D vector.
     * @throws std::ios:failure When
     */
    std::vector<std::vector<CWall *>> LoadMap();

    /**
     * Get players from game.
     * @param count Players count.
     * @return
     */
    std::vector<CPlayer *> LoadPlayers(int count);

    /**
     * Get object which will be rendered as ground.
     * @return Ground object
     */
    std::shared_ptr<CGround> LoadGround();

    /**
     * Generate obstacles for game map.
     * @param board Gameboard
     * @param level Level number
     * @param count Obstacles count
     * @return Container of obstacles.
     */
    void GenerateObstacles(std::shared_ptr<CBoard> board, size_t level, size_t count);

    /**
    * Get bomb texture pack.
    * @return Texture pack
    */
    std::shared_ptr<CTexturePack> LoadBombTexturePack();

    /**
     * Get fire texture pack.
     * @return Texture pack
     */
    std::shared_ptr<CTexturePack> LoadFireTexturePack();
};

