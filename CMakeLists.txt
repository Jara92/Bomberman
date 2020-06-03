cmake_minimum_required(VERSION 3.15)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(bomberman src/main.cpp src/CCoord.h src/CCoord.cpp src/CBoard.cpp src/CControls.h src/CBoard.h src/CApplication.cpp src/CApplication.h src/gameobjects/CGameObject.cpp src/gameobjects/CGameObject.h src/CSDLInterface.cpp src/CSDLInterface.h src/CGameManager.cpp src/CGameManager.h src/gameobjects/CGameObject.cpp src/gameobjects/CGameObject.h src/gameobjects/CWall.cpp src/gameobjects/CWall.h src/gameobjects/movables/CPlayer.cpp src/gameobjects/movables/CPlayer.h src/gameobjects/CGround.cpp src/gameobjects/CGround.h src/gameobjects/movables/CEnemy.cpp src/gameobjects/movables/CEnemy.h src/gameobjects/CBomb.cpp src/gameobjects/CBomb.h src/gameobjects/CFire.cpp src/gameobjects/CFire.h src/gameobjects/collectibles/CCollectible.cpp src/gameobjects/collectibles/CCollectible.h src/CLevelLoader.cpp src/CLevelLoader.h src/CTexturePack.cpp src/CTexturePack.h src/gameobjects/movables/CMovable.cpp src/gameobjects/movables/CMovable.h src/EDirection.h src/gameobjects/movables/CMovable.cpp src/gameobjects/movables/CMovable.h src/gameobjects/movables/CPlayer.cpp src/gameobjects/movables/CPlayer.h src/gameobjects/collectibles/CDoor.cpp src/gameobjects/collectibles/CDoor.h src/gameobjects/collectibles/CBoost.cpp src/gameobjects/collectibles/CBoost.h src/gameobjects/movables/CEnemyDump.cpp src/gameobjects/movables/CEnemyDump.h src/gameobjects/movables/CEnemySmart.cpp src/gameobjects/movables/CEnemySmart.h src/ETextureType.h src/CAnimation.cpp src/CAnimation.h src/CScoreManager.cpp src/CScoreManager.h src/CClock.cpp src/EGameStatus.h src/CTimer.cpp src/CTimer.h)

target_link_libraries(bomberman ${SDL2_LIBRARIES} -lSDL2_image -lSDL2_ttf)