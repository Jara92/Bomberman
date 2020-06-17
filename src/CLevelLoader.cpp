/**
 * @author Jaroslav Fikar
*/

#include "CLevelLoader.h"

CLevelLoader::CLevelLoader(CSDLInterface &interface, std::string mapFileName, std::string levelFileName)
        : m_MapFileName(std::move(mapFileName)), m_LevelFileName(std::move(levelFileName)), m_Interface(interface)
{
    this->m_EnemyTexturePacks = this->LoadEnemyTexturePacks();
    this->m_CollectibleTexturePacks = this->LoadCollectiblesTexturePacks();
}

/*====================================================================================================================*/
bool CLevelLoader::LoadLevel(std::shared_ptr<CBoard> &board, size_t level, bool loadLevelFile)
{
    std::vector<CCollectible *> collectibles;

    // Prepare board for next level.
    board->PrepareBoard(loadLevelFile, collectibles);

    // Generate random obstacles.
    size_t obstaclesCount = (board->GetBoardSize().m_X * board->GetBoardSize().m_Y) * 0.15;
    this->GenerateObstacles(board, level, obstaclesCount);

    // Load enemies and boosts from the file.
    if (loadLevelFile)
    {
        // Delete old level collectibles because new level objects will be loaded.
        for (std::vector<CCollectible *>::size_type i = 0; i < collectibles.size(); i++)
        { delete collectibles[i]; }
        collectibles.clear();

        this->LoadLevelFile(board, level, collectibles);
    }
        // Random location for every collectable and enemy object.
    else
    { this->NextRoundPrepare(board, collectibles); }

    return true;
}

/*====================================================================================================================*/
std::shared_ptr<CBoard> CLevelLoader::GetBoard(int playersCount, const std::shared_ptr<CSettings> &settings)
{
    // calc cellsize
    unsigned int cellSize = static_cast<unsigned int>((settings->GetGameScreenSize().m_Y) /
                                                      (CLevelLoader::MAP_HEIGHT + settings->GetOffset().m_Y));

    // Create new board using loaded objects.
    return std::make_shared<CBoard>(settings, this->LoadMap(), this->LoadPlayers(playersCount),
                                    CCoord<unsigned int>(CLevelLoader::MAP_WIDTH, CLevelLoader::MAP_HEIGHT),
                                    this->LoadGround(), this->LoadBombTexturePack(), this->LoadFireTexturePack(),
                                    cellSize);
}

/*====================================================================================================================*/
std::vector<std::vector<CBlock *>> CLevelLoader::LoadMap()
{
    // Create indestructible wall texture pack.
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/SolidBlock.png"}}}};
    std::shared_ptr<CTexturePack> texturePack = std::make_shared<CTexturePack>(this->m_Interface, textures);

    // Init 2D array
    std::vector<std::vector<CBlock *>> map;
    map.resize(CLevelLoader::MAP_WIDTH);

    for (unsigned int i = 0; i < map.size(); i++)
    { map[i].resize(CLevelLoader::MAP_HEIGHT, nullptr); }

    unsigned int row = 0, col = 0;
    std::ifstream fileReader(this->m_Interface.GetSettings()->GetDataPath() + this->m_MapFileName,
                             std::ios::binary | std::ios::in);

    // Is file reader ok?
    if (!fileReader || !fileReader.is_open() || fileReader.eof() || fileReader.bad())
    { throw std::ios::failure(MESSAGE_MAP_NOT_FOUND); }

    unsigned char input = '\0';
    while ((fileReader >> std::noskipws >> input) && !fileReader.eof())
    {
        // Read by bite
        for (unsigned int i = 0; i < 8; i++)
        {
            // if i-bite=1 -> Build wall on this position
            if (static_cast<unsigned int>((input >> (7u - i))) & 1u)
            {
                CCoord<unsigned int> wallLocation{(col * 8 + i), row};
                // We just need to fill array MAP_WIDTH x MAP_HEIGHT - we are not interested in the remaining data
                if (wallLocation.m_X >= MAP_WIDTH || wallLocation.m_Y >= MAP_HEIGHT)
                { break; }
                map[wallLocation.m_X][wallLocation.m_Y] = new CWall(texturePack, false);
            }
        }

        // Increment col with every read byte and Jump to next row if required.
        col++;
        if (col >= FILE_MAP_WIDTH / 8)
        {
            col = 0;
            row++;
        }
    }

    fileReader.close();
    return map;
}

/*====================================================================================================================*/
std::vector<CPlayer *> CLevelLoader::LoadPlayers(int count)
{
    CInput controls[MAX_PLAYERS] = {
            {SDL_SCANCODE_W,  SDL_SCANCODE_S,    SDL_SCANCODE_A,    SDL_SCANCODE_D,     SDL_SCANCODE_J,    SDL_SCANCODE_K},
            {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_KP_4, SDL_SCANCODE_KP_5}
    };

    // Setup texturepack for the players.
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{
                    {"Bomberman/Front/front0.png"},
                    {"Bomberman/Front/front1.png"},
                    {"Bomberman/Front/front2.png"},
                    {"Bomberman/Front/front3.png"},
                    {"Bomberman/Front/front4.png"},
                    {"Bomberman/Front/front5.png"},
                    {"Bomberman/Front/front6.png"},
                    {"Bomberman/Front/front7.png"}
            }},
             {ETextureType::TEXTURE_BACK,  std::vector<std::string>{
                     {"Bomberman/Back/back0.png"},
                     {"Bomberman/Back/back1.png"},
                     {"Bomberman/Back/back2.png"},
                     {"Bomberman/Back/back3.png"},
                     {"Bomberman/Back/back4.png"},
                     {"Bomberman/Back/back5.png"},
                     {"Bomberman/Back/back6.png"},
                     {"Bomberman/Back/back7.png"}
             }},
             {ETextureType::TEXTURE_LEFT,  std::vector<std::string>{
                     {"Bomberman/Left/left0.png"},
                     {"Bomberman/Left/left1.png"},
                     {"Bomberman/Left/left2.png"},
                     {"Bomberman/Left/left3.png"},
                     {"Bomberman/Left/left4.png"},
                     {"Bomberman/Left/left5.png"},
                     {"Bomberman/Left/left6.png"},
                     {"Bomberman/Left/left7.png"}
             }},
             {ETextureType::TEXTURE_RIGHT, std::vector<std::string>{
                     {"Bomberman/Right/right0.png"},
                     {"Bomberman/Right/right1.png"},
                     {"Bomberman/Right/right2.png"},
                     {"Bomberman/Right/right3.png"},
                     {"Bomberman/Right/right4.png"},
                     {"Bomberman/Right/right5.png"},
                     {"Bomberman/Right/right6.png"},
                     {"Bomberman/Right/right7.png"}
             }}};

    std::vector<std::map<ETextureType, const std::vector<std::string>>> texturePacks{{textures},
                                                                                     {textures}};

    // Setup default locations
    CCoord<> startingLocation[CLevelLoader::MAX_PLAYERS] = {{1,  1},
                                                            {21, 11}};

    SDL_Color playerColor[CLevelLoader::MAX_PLAYERS] = {{255, 255, 255, 255},
                                                        {255, 215, 0,   255}};
    std::vector<CPlayer *> players;

    // return only required players
    for (int i = 0; i < count; i++)
    {
        // Create texture pack using right color.
        auto texturePack = std::make_shared<CTexturePack>(this->m_Interface, texturePacks[i], false, CCoord<>(1, 2));
        texturePack->SetTextureColorMod(playerColor[i]);
        players.push_back(new CPlayer(texturePack, startingLocation[i], CCoord<>(0.60, 0.60), controls[i]));
    }

    return players;
}

/*====================================================================================================================*/
void CLevelLoader::GenerateObstacles(std::shared_ptr<CBoard> &board, size_t level, size_t count)
{
    // Create texture pack for destructible wall.
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/ExplodableBlock.png"}}}};
    std::shared_ptr<CTexturePack> texturePack = std::make_shared<CTexturePack>(this->m_Interface, textures);

    // Generate obstables to protect the player when the game starts.
    board->m_Map[3][1] = new CWall(texturePack, true);
    board->m_Map[1][3] = new CWall(texturePack, true);

    if (board->m_Players.size() > 1)
    {
        board->m_Map[19][11] = new CWall(texturePack, true);
        board->m_Map[21][9] = new CWall(texturePack, true);
    }

    for (unsigned int i = 0; i < count; i++)
    {
        // Generate random location until the location is free.
        CCoord<unsigned int> random;
        do
        { random = board->GetRandomBoardLocation(); }
        while (!board->PositionFree(random) || !board->PlayersAreaFree(random, CPlayer::OBSTACLES_SAVE_ZONE));

        board->m_Map[random.m_X][random.m_Y] = new CWall(texturePack, true);
    }
}

/*====================================================================================================================*/
std::shared_ptr<CBlock> CLevelLoader::LoadGround() const
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/BackgroundTile.png"}}}};

    std::shared_ptr<CTexturePack> texturePack = std::make_shared<CTexturePack>(this->m_Interface, textures);
    // create reference wall to make copies
    return std::make_shared<CBlock>(CBlock(texturePack, CCoord<>(1, 1), true));
}

/*====================================================================================================================*/
std::shared_ptr<CTexturePack> CLevelLoader::LoadBombTexturePack() const
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Bomb/Bomb_f01.png"},
                                                                    {"Bomb/Bomb_f02.png"},
                                                                    {"Bomb/Bomb_f03.png"}}}};

    return std::make_shared<CTexturePack>(this->m_Interface, textures, true, CCoord<>(0.65, 0.65));
}

/*====================================================================================================================*/
std::shared_ptr<CTexturePack> CLevelLoader::LoadFireTexturePack() const
{
    std::map<ETextureType, const std::vector<std::string>> textures
            {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Flame/Flame_f00.png"},
                                                                    {"Flame/Flame_f01.png"},
                                                                    {"Flame/Flame_f02.png"},
                                                                    {"Flame/Flame_f03.png"},
                                                                    {"Flame/Flame_f04.png"}}}};

    return std::make_shared<CTexturePack>(this->m_Interface, textures, true, CCoord<>(0.7, 0.7));
}

/*====================================================================================================================*/
std::vector<std::shared_ptr<CTexturePack>> CLevelLoader::LoadEnemyTexturePacks() const
{
    // Save textures in right order
    std::vector<std::map<ETextureType, const std::vector<std::string>>> textures
            {{
                     {ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Creep/Pink/Front/Front_f00.png"},
                                                                            {"Creep/Pink/Front/Front_f01.png"},
                                                                            {"Creep/Pink/Front/Front_f02.png"},
                                                                            {"Creep/Pink/Front/Front_f03.png"},
                                                                            {"Creep/Pink/Front/Front_f04.png"},
                                                                            {"Creep/Pink/Front/Front_f05.png"}}},
                     {ETextureType::TEXTURE_BACK, std::vector<std::string>{{"Creep/Pink/Back/Back_f00.png"},
                                                                           {"Creep/Pink/Back/Back_f01.png"},
                                                                           {"Creep/Pink/Back/Back_f02.png"},
                                                                           {"Creep/Pink/Back/Back_f03.png"},
                                                                           {"Creep/Pink/Back/Back_f04.png"},
                                                                           {"Creep/Pink/Back/Back_f05.png"}}},
                     {ETextureType::TEXTURE_LEFT, std::vector<std::string>{{"Creep/Pink/Left/Left_f00.png"},
                                                                           {"Creep/Pink/Left/Left_f01.png"},
                                                                           {"Creep/Pink/Left/Left_f02.png"},
                                                                           {"Creep/Pink/Left/Left_f03.png"},
                                                                           {"Creep/Pink/Left/Left_f04.png"},
                                                                           {"Creep/Pink/Left/Left_f05.png"}}},
                     {ETextureType::TEXTURE_RIGHT, std::vector<std::string>{{"Creep/Pink/Right/Right_f00.png"},
                                                                            {"Creep/Pink/Right/Right_f01.png"},
                                                                            {"Creep/Pink/Right/Right_f02.png"},
                                                                            {"Creep/Pink/Right/Right_f03.png"},
                                                                            {"Creep/Pink/Right/Right_f04.png"},
                                                                            {"Creep/Pink/Right/Right_f05.png"}}}}};
    std::vector<CCoord<>> sizes{{1, 1}};

    std::vector<SDL_Color> textureColors = {{50,  255, 30,  255},
                                            {255, 255, 255, 255}};

    // Create texture packs shared pointers.
    std::vector<std::shared_ptr<CTexturePack>> texturePacks;
    for (size_t i = 0; i < textureColors.size(); i++)
    {
        texturePacks.push_back(std::make_shared<CTexturePack>(this->m_Interface, textures[0], true, sizes[0]));
        texturePacks.back()->SetTextureColorMod(textureColors[i]);
    }

    return texturePacks;
}

/*====================================================================================================================*/
std::vector<std::shared_ptr<CTexturePack>> CLevelLoader::LoadCollectiblesTexturePacks() const
{
    // Save textures in right order - ECollectibleType texturePack = textures[(int)ECollectibleType)]
    std::vector<std::map<ETextureType, const std::vector<std::string>>> textures
            {
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/SpeedPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/FlamePowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/BombPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/RemoteExplosionPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/BombPassPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/WallPassPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/FireImunityPowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/ScorePowerup.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Blocks/Portal.png"}}}},
                    {{ETextureType::TEXTURE_FRONT, std::vector<std::string>{{"Powerups/LivesPowerup.png"}}}}};

    std::vector<CCoord<>> sizes{{0.7, 0.7},
                                {0.7, 0.7},
                                {0.7, 0.7},
                                {0.7, 0.7},
                                {0.7, 0.7},
                                {0.7, 0.7},
                                {0.7, 0.7},
                                {0.7, 0.7},
                                {1,   1},
                                {0.7, 0.7}};

    // Create texture packs shared pointers.
    std::vector<std::shared_ptr<CTexturePack>> texturePacks;
    for (size_t i = 0; i < textures.size(); i++)
    { texturePacks.push_back(std::make_shared<CTexturePack>(this->m_Interface, textures[i], true, sizes[i])); }

    return texturePacks;
}

/*====================================================================================================================*/
void CLevelLoader::LoadLevelFile(std::shared_ptr<CBoard> &board, unsigned int level,
                                 std::vector<CCollectible *> &collectibles)
{
    std::ifstream fileReader(
            (this->m_Interface.GetSettings()->GetDataPath() + this->m_LevelFileName) + std::to_string(level),
            std::ios::in);

    // Is file reader ok?
    if (!fileReader || !fileReader.is_open() || fileReader.eof() || fileReader.bad())
    { throw std::ios::failure(MESSAGE_LEVEL_NOT_AVAIBLE); }

    // Read all lines and crate object for every line
    std::string line;
    while (std::getline(fileReader, line))
    {
        // Split string
        std::istringstream iss(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        // Skip empty
        if (results.empty())
        { break; }

        // Read item type and
        std::string itemType = this->ReadProperty(results, 0);

        // Process this line and save the object.
        this->ReadItem(board, results, itemType, collectibles);
    }

    fileReader.close();

    if (collectibles.size() >= 20)
    { throw std::runtime_error(MESSAGE_MAXIMUM_COLLECTIBLES_REACHES); }
}

/*====================================================================================================================*/
std::string
CLevelLoader::ReadProperty(const std::vector<std::string> &input, std::vector<std::string>::size_type index) const
{
    if (index >= input.size())
    { throw std::out_of_range(MESSAGE_INDEX_OUT_OF_BOUND); }

    return input[index];
}

/*====================================================================================================================*/
void CLevelLoader::NextRoundPrepare(std::shared_ptr<CBoard> &board, std::vector<CCollectible *> &collectibles)
{
    // NextLevel all collectibles (random location, attach to random wall...)
    for (auto collectible = collectibles.begin(); collectible != collectibles.end(); collectible++)
    { (*collectible)->NextLevel(*board, false); }
    collectibles.clear();

    // NextLevel all objects (random location, attach to random wall...)
    for (auto object = board->m_Movables.begin(); object != board->m_Movables.end(); object++)
    { (*object)->NextLevel(*board, false); }
}

/*====================================================================================================================*/
void
CLevelLoader::CreateCollectible(std::shared_ptr<CBoard> &board, std::vector<CCollectible *> &collectibles,
                                ECollectibleType type, std::size_t score,
                                std::size_t duration)
{
    // Lamda which are used to apply / deactivate collectable item.
    std::function<void(CPlayer *)> applyFunc;
    std::function<void(CPlayer *)> deactivateFunc;
    CCoord<> boostSize = CCoord<>(0.7, 0.7);
    unsigned int typeInt = static_cast<unsigned int>(type);

    CCollectible *newCollectible = nullptr;
    // Create new boost.
    switch (type)
    {
        case ECollectibleType::COLLECTIBLE_TYPE_SPEED:
            applyFunc = [](CPlayer *player)
            { player->SpeedUp(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_EXPLOSION_RADIUS:
            applyFunc = [](CPlayer *player)
            { player->IncreseExplosionRadius(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_MAX_BOMBS:
            applyFunc = [](CPlayer *player)
            { player->IncreseMaxBombs(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_REMOTE_EXPLOSION:
            applyFunc = [](CPlayer *player)
            { player->ActivateRemoteExplosion(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_BOMB_PASS:
            applyFunc = [](CPlayer *player)
            { player->ActivateBombPass(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_WALL_PASS:
            applyFunc = [](CPlayer *player)
            { player->ActivateWallPass(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_FIRE_IMUNITY:
            applyFunc = [](CPlayer *player)
            { player->ActivateFireImmunity(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_SCORE_BONUS:
            applyFunc = [](CPlayer *player)
            {};
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_DOOR:
            newCollectible = new CDoor(this->m_CollectibleTexturePacks[typeInt], CCoord<>(0.2, 0.2), score);
            break;
        case ECollectibleType::COLLECTIBLE_TYPE_LIVE_BONUS:
            applyFunc = [](CPlayer *player)
            { player->IncreseLiveCount(); };
            newCollectible = new CBoost(this->m_CollectibleTexturePacks[typeInt], applyFunc, boostSize, score);
            break;
        default:
            throw std::invalid_argument(MESSAGE_UNKNOWN_COLLECTIBLE_TYPE);
    }

    if (newCollectible)
    {
        newCollectible->NextLevel(*board, false);
        collectibles.push_back(newCollectible);
    }
}

/*====================================================================================================================*/
void CLevelLoader::CreateEnemy(std::shared_ptr<CBoard> &board, EEnemyType type, std::size_t lives,
                               std::size_t score, double speed, bool wallPass)
{
    unsigned int typeInt = static_cast<unsigned int>(type);
    CCoord<> enemySize = CCoord<>(0.60, 0.60);

    CEnemy *newEnemy = nullptr;

    switch (type)
    {
        case EEnemyType::ENEMY_TYPE_DUMP:
            newEnemy = new CEnemyDumb(this->m_EnemyTexturePacks[typeInt], CCoord<>(0, 0), enemySize, score, speed,
                                      wallPass, lives);
            break;
        case EEnemyType::ENEMY_TYPE_SMART:
            newEnemy = new CEnemySmart(this->m_EnemyTexturePacks[typeInt], CCoord<>(0, 0), enemySize, score, speed,
                                       wallPass, lives);
            break;
        default:
            throw std::invalid_argument(MESSAGE_UNKNOWN_ENEMY_TYPE);
    }

    if (newEnemy)
    {
        newEnemy->NextLevel(*board, false);
        board->m_Movables.push_back(newEnemy);
    }
}

/*====================================================================================================================*/
bool CLevelLoader::ReadItem(std::shared_ptr<CBoard> &board, const std::vector<std::string> &input,
                            const std::string &itemType, std::vector<CCollectible *> &collectibles)
{
    try
    {
        // Collectible item
        if (itemType == "collectible" && input.size() == COLLECTIBLE_ITEM_PROPERTIES_COUNT)
        {
            // Load other properties.
            unsigned int collectibleTypeId = std::stoi(this->ReadProperty(input, 1));
            std::size_t score = std::stoi(this->ReadProperty(input, 2));
            std::size_t duration = std::stoi(this->ReadProperty(input, 3));

            // Invalid collectible type id detection.
            if (collectibleTypeId >= this->m_CollectibleTexturePacks.size())
            { throw std::invalid_argument(MESSAGE_UNKNOWN_COLLECTIBLE_TYPE); }

            ECollectibleType collectibleType = static_cast<ECollectibleType >(collectibleTypeId);

            this->CreateCollectible(board, collectibles, collectibleType, score, duration);
        }
            // Enemy+ std::to_string(" ")
        else if (itemType == "enemy" && input.size() == ENEMY_ITEM_PROPERTIES_COUNT)
        {
            unsigned int enemyTypeId = std::stoi(this->ReadProperty(input, 1));
            std::size_t score = std::stoi(this->ReadProperty(input, 2));
            std::size_t lives = std::stoi(this->ReadProperty(input, 3));
            double speed = (std::stoi(this->ReadProperty(input, 4)) / 10000.0);
            std::size_t wallPass = (std::stoi(this->ReadProperty(input, 5)) == 1);

            // Invalid enemy type id detection.
            if (enemyTypeId >= this->m_EnemyTexturePacks.size())
            { throw std::invalid_argument(MESSAGE_UNKNOWN_ENEMY_TYPE); }

            EEnemyType enemyType = static_cast<EEnemyType >(enemyTypeId);

            this->CreateEnemy(board, enemyType, lives, score, speed, wallPass);
        }
            // Invalid item format.
        else
        {
            std::cerr << MESSAGE_INVALID_ITEM << itemType << std::endl;
            for (std::vector<std::string>::size_type i = 0; i < input.size(); i++)
            { std::cerr << input[i] << " "; }
            std::cerr << std::endl;
            return false;
        }
    }
    catch (std::invalid_argument &ex)
    {
        std::cerr << MESSAGE_INVALID_ARGUMENT << " " << ex.what() << std::endl;
        return false;
    }
    catch (std::out_of_range &ex)
    {
        std::cerr << MESSAGE_ARGUMENT_OUT_OF_RANGE << " " << ex.what() << std::endl;
        return false;
    }

    return true;
}
