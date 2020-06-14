/**
 * @author Jaroslav Fikar
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <sstream>
#include <iterator>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "CBoard.h"
#include "CSDLInterface.h"
#include "blocks/collectibles/CBoost.h"
#include "blocks/collectibles/CDoor.h"
#include "enums/ECollectibleType.h"
#include "enums/EEnemyType.h"
#include "Messages.h"

class CLevelLoader
{
public:
    CLevelLoader(CSDLInterface &interface, std::string mapFileName = "map", std::string levelFileName = "levels/level");

    ~CLevelLoader() = default;

    CLevelLoader(const CLevelLoader &mapLoader) = delete;

    CLevelLoader &operator=(const CLevelLoader &mapLoader) = delete;

    std::shared_ptr<CBoard> GetBoard(int playersCount, const std::shared_ptr<CSettings> &settings);

    /**
     * Load new level.
     * @param board Game board.
     * @param level Level to be loaded.
     * @param loadLevelFile Load level items from the level file?
     * @return True - success.
     */
    bool LoadLevel(std::shared_ptr<CBoard> &board, size_t level, bool loadLevelFile = true);

protected:
    std::string m_MapFileName;
    std::string m_LevelFileName;
    /* Saved map size. Widht must be divisible by eight (Binary file).*/
    static const unsigned int FILE_MAP_WIDTH = 24, FILE_MAP_HEIGHT = 13;
    /* Real map size (Real map is smaller because the map is saved as binary file. I have to remember which bits are valid) */
    static const unsigned int MAP_WIDTH = 23, MAP_HEIGHT = 13;

    static const unsigned int MAX_PLAYERS = 2;
    /** How many properties collectible item should have? */
    static const unsigned int COLLECTIBLE_ITEM_PROPERTIES_COUNT = 4;
    /** How many properties enemy item should have? */
    static const unsigned int ENEMY_ITEM_PROPERTIES_COUNT = 6;

    CSDLInterface &m_Interface;

    /** Texture packs used for dynamically added objects. */
    std::vector<std::shared_ptr<CTexturePack>> m_EnemyTexturePacks, m_CollectibleTexturePacks;

    /**
     * Load map from the file.
     * @return Map saved in 2D vector.
     * @throws std::ios:failure When
     */
    std::vector<std::vector<CBlock *>> LoadMap();

    /**
     * Get players from game.
     * @param count Players count.
     * @return Players for game.
     */
    std::vector<CPlayer *> LoadPlayers(int count);

    /**
     * Get object which will be rendered as ground.
     * @return Ground object
     */
    std::shared_ptr<CBlock> LoadGround() const;

    /**
     * Generate obstacles for game map.
     * @param board Gameboard
     * @param level Level number
     * @param count Obstacles count
     * @return Container of obstacles.
     */
    void GenerateObstacles(std::shared_ptr<CBoard> &board, size_t level, size_t count);

    /**
     * Load config data from file.
     * @param board Game board.
     * @param level Level to be loaded.
     * @param loadLevelObjects Load collectible objects from the file or use existing collectibles?
     * @throws std::ios::failure When level file not found.
     */
    void LoadLevelFile(std::shared_ptr<CBoard> &board, unsigned int level, std::vector<CCollectible *> &collectibles);

    /**
     * Move every collectible to random location and attach it to assign it to the wall in the same position.
     * @param board Game board.
     */
    void ReorganizeLevelObjects(std::shared_ptr<CBoard> &board, std::vector<CCollectible *> &collectibles);

    /**
     * Read one property from the input array.
     * @param input Input array.
     * @param index Index to be read.
     * @return Property value.
     * @throws std::out_of_range If index doesnt exist.
     */
    std::string ReadProperty(const std::vector<std::string> &input, std::vector<std::string>::size_type index) const;

    /**
     * Decode input and save new item from the file input.
     * @param board Game board.
     * @param input Input array.
     * @param itemType Item type.
     * @return True - success.
     */
    bool ReadItem(std::shared_ptr<CBoard> &board, const std::vector<std::string> &input, const std::string &itemType,
                  std::vector<CCollectible *> &collectibles);

    /**
     * Create new CCollectible at random location and attach it to CWall.
     * @param collectibles Collectibles list.
     * @param type Collectible type.
     * @param score Score to be achieved.
     * @param duration Collectible duration.
     * @throws std::invalid_argument Unknown collectible type.
     */
    void CreateCollectible(std::vector<CCollectible *> &collectibles, ECollectibleType type, std::size_t score,
                           std::size_t duration);

    /**
     * Create new CEnemy at random location.
     * @param board Game board.
     * @param type Enemy type.
     * @param lives Number of enemy lives
     * @param score Score to be achieved.
     * @param speed Enemy moving speed.
     * @param wallPass Can the enemy walk through the walls?
     */
    void
    CreateEnemy(std::shared_ptr<CBoard> &board, EEnemyType type, std::size_t lives, std::size_t score, double speed,
                bool wallPass);

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
