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
#include <sstream>
#include <iterator>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "CBoard.h"
#include "CSDLInterface.h"
#include "gameobjects/collectibles/CBoost.h"
#include "gameobjects/collectibles/CDoor.h"
#include "Messages.h"
#include "ECollectibleType.h"

class CLevelLoader
{
public:
    CLevelLoader(CSDLInterface *interface, std::string mapFileName = "map", std::string levelFileName = "levels/level");

    ~CLevelLoader() = default;

    CLevelLoader(const CLevelLoader &mapLoader) = default;

    CLevelLoader & operator=(const CLevelLoader &mapLoader) = default;

    std::shared_ptr<CBoard> GetBoard(int playersCount, const std::shared_ptr<CSettings> & settings);

    bool LoadLevel(std::shared_ptr<CBoard> &board, size_t level);

protected:
    std::string m_MapFileName;
    std::string m_LevelFileName;
    /* Saved map size */
    static const size_t FILE_MAP_WIDTH = 24;
    static const size_t FILE_MAP_HEIGHT = 13;
    /* Real map size (Real map is smaller because the map is saved as binary file. I have to remember which bits are valid) */
    static const size_t MAP_WIDTH = 23;
    static const size_t MAP_HEIGHT = 13;

    static const size_t MAX_PLAYERS = 2;
    /** How many properties collectible item should have? */
    static const size_t COLLECTIBLE_ITEM_PROPERTIES_COUNT = 4;
    /** How many properties enemy item should have? */
    static const size_t ENEMY_ITEM_PROPERTIES_COUNT = 7;

    CSDLInterface *m_Interface;

    /* Texture packs used for dynamically added objects. */
    std::vector<std::shared_ptr<CTexturePack>> m_EnemyTexturePacks;
    std::vector<std::shared_ptr<CTexturePack>> m_CollectibleTexturePacks;

    /**
     * Get random location in game board.
     * @param board Game board.
     * @return Random location.
     */
    CCoord GetRandomBoardLocation(std::shared_ptr<CBoard> & board) const;

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
    std::shared_ptr<CGround> LoadGround() const;

    /**
     * Generate obstacles for game map.
     * @param board Gameboard
     * @param level Level number
     * @param count Obstacles count
     * @return Container of obstacles.
     */
    void GenerateObstacles(std::shared_ptr<CBoard> & board, size_t level, size_t count);

    /**
     * Load config data from file.
     * @param board Game board.
     * @param level Level to be loaded.
     * @throws std::ios::failure When level file not found.
     */
    void LoadLevelFile(std::shared_ptr<CBoard> &board, unsigned int level,  bool loadCollectibles = true);

    /**
     * Move every collectible to random location and attach it to assign it to the wall in the same position.
     * @param board Game board.
     */
    void ReorganizeCollectibles(std::shared_ptr<CBoard> & board);

    /**
     * Read one property from the input array.
     * @param input Input array.
     * @param index Index to be read.
     * @return Property value.
     * @throws std::out_of_range If index doesnt exist.
     */
    std::string ReadProperty(const std::vector<std::string> & input, std::vector<std::string>::size_type index) const;

    /**
     * Decode input and save new item from the file input.
     * @param board Game board.
     * @param input Input array.
     * @param itemType Item type.
     * @return True - success.
     */
    bool ReadItem(std::shared_ptr<CBoard> &board, const std::vector<std::string> & input, const std::string & itemType);

    /**
     * Create new CCollectible at random location and attach it to CWall.
     * @param type Collectible type.
     * @param score Score to be achieved.
     * @param duration Collectible duration.
     * @throws std::invalid_argument Unknown collectible type.
     * @return True - success.
     */
    bool CreateCollectibleAtRandomLocation(std::shared_ptr<CBoard> &board, ECollectibleType type, std::size_t score, std::size_t duration);

    /**
    * Get bomb texture pack.
    * @return Texture pack
    */
    std::shared_ptr<CTexturePack> LoadBombTexturePack() const;

    /**
     * Get fire texture pack.
     * @return Texture pack
     */
    std::shared_ptr<CTexturePack> LoadFireTexturePack() const;

    /**
     * Get texture packs for enemies.
     * @return Texture packs.
     */
    std::vector<std::shared_ptr<CTexturePack>> LoadEnemyTexturePacks() const;

    /**
     * Get texture packs for collectibles.
     * @return Texture packs.
     */
    std::vector<std::shared_ptr<CTexturePack>> LoadCollectiblesTexturePacks() const;
};

