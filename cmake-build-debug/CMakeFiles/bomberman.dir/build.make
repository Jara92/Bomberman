# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jaroslav/CLionProjects/bomberman

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jaroslav/CLionProjects/bomberman/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bomberman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bomberman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bomberman.dir/flags.make

CMakeFiles/bomberman.dir/src/main.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bomberman.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/main.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/main.cpp

CMakeFiles/bomberman.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/main.cpp > CMakeFiles/bomberman.dir/src/main.cpp.i

CMakeFiles/bomberman.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/main.cpp -o CMakeFiles/bomberman.dir/src/main.cpp.s

CMakeFiles/bomberman.dir/src/CBoard.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/CBoard.cpp.o: ../src/CBoard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bomberman.dir/src/CBoard.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/CBoard.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/CBoard.cpp

CMakeFiles/bomberman.dir/src/CBoard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/CBoard.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/CBoard.cpp > CMakeFiles/bomberman.dir/src/CBoard.cpp.i

CMakeFiles/bomberman.dir/src/CBoard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/CBoard.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/CBoard.cpp -o CMakeFiles/bomberman.dir/src/CBoard.cpp.s

CMakeFiles/bomberman.dir/src/CApplication.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/CApplication.cpp.o: ../src/CApplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/bomberman.dir/src/CApplication.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/CApplication.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/CApplication.cpp

CMakeFiles/bomberman.dir/src/CApplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/CApplication.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/CApplication.cpp > CMakeFiles/bomberman.dir/src/CApplication.cpp.i

CMakeFiles/bomberman.dir/src/CApplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/CApplication.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/CApplication.cpp -o CMakeFiles/bomberman.dir/src/CApplication.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.o: ../src/gameobjects/CGameObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CGameObject.cpp

CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CGameObject.cpp > CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CGameObject.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.s

CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.o: ../src/CSDLInterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/CSDLInterface.cpp

CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/CSDLInterface.cpp > CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.i

CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/CSDLInterface.cpp -o CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.s

CMakeFiles/bomberman.dir/src/CGameManager.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/CGameManager.cpp.o: ../src/CGameManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/bomberman.dir/src/CGameManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/CGameManager.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/CGameManager.cpp

CMakeFiles/bomberman.dir/src/CGameManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/CGameManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/CGameManager.cpp > CMakeFiles/bomberman.dir/src/CGameManager.cpp.i

CMakeFiles/bomberman.dir/src/CGameManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/CGameManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/CGameManager.cpp -o CMakeFiles/bomberman.dir/src/CGameManager.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.o: ../src/gameobjects/CWall.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CWall.cpp

CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CWall.cpp > CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CWall.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.o: ../src/gameobjects/movables/CPlayer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CPlayer.cpp

CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CPlayer.cpp > CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CPlayer.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.o: ../src/gameobjects/CGround.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CGround.cpp

CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CGround.cpp > CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CGround.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.o: ../src/gameobjects/movables/CEnemy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemy.cpp

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemy.cpp > CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemy.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.o: ../src/gameobjects/CBomb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CBomb.cpp

CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CBomb.cpp > CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CBomb.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.o: ../src/gameobjects/CFire.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CFire.cpp

CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CFire.cpp > CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/CFire.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.o: ../src/gameobjects/collectibles/CCollectible.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CCollectible.cpp

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CCollectible.cpp > CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CCollectible.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.s

CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.o: ../src/CLevelLoader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/CLevelLoader.cpp

CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/CLevelLoader.cpp > CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.i

CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/CLevelLoader.cpp -o CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.s

CMakeFiles/bomberman.dir/src/CTexturePack.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/CTexturePack.cpp.o: ../src/CTexturePack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/bomberman.dir/src/CTexturePack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/CTexturePack.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/CTexturePack.cpp

CMakeFiles/bomberman.dir/src/CTexturePack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/CTexturePack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/CTexturePack.cpp > CMakeFiles/bomberman.dir/src/CTexturePack.cpp.i

CMakeFiles/bomberman.dir/src/CTexturePack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/CTexturePack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/CTexturePack.cpp -o CMakeFiles/bomberman.dir/src/CTexturePack.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.o: ../src/gameobjects/movables/CMovable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CMovable.cpp

CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CMovable.cpp > CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CMovable.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.o: ../src/gameobjects/collectibles/CDoor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CDoor.cpp

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CDoor.cpp > CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CDoor.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.o: ../src/gameobjects/collectibles/CBoost.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CBoost.cpp

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CBoost.cpp > CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/collectibles/CBoost.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.o: ../src/gameobjects/movables/CEnemyDump.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemyDump.cpp

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemyDump.cpp > CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemyDump.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.s

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.o: ../src/gameobjects/movables/CEnemySmart.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building CXX object CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemySmart.cpp

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemySmart.cpp > CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.i

CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/gameobjects/movables/CEnemySmart.cpp -o CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.s

CMakeFiles/bomberman.dir/src/CAnimation.cpp.o: CMakeFiles/bomberman.dir/flags.make
CMakeFiles/bomberman.dir/src/CAnimation.cpp.o: ../src/CAnimation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building CXX object CMakeFiles/bomberman.dir/src/CAnimation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bomberman.dir/src/CAnimation.cpp.o -c /home/jaroslav/CLionProjects/bomberman/src/CAnimation.cpp

CMakeFiles/bomberman.dir/src/CAnimation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bomberman.dir/src/CAnimation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jaroslav/CLionProjects/bomberman/src/CAnimation.cpp > CMakeFiles/bomberman.dir/src/CAnimation.cpp.i

CMakeFiles/bomberman.dir/src/CAnimation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bomberman.dir/src/CAnimation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jaroslav/CLionProjects/bomberman/src/CAnimation.cpp -o CMakeFiles/bomberman.dir/src/CAnimation.cpp.s

# Object files for target bomberman
bomberman_OBJECTS = \
"CMakeFiles/bomberman.dir/src/main.cpp.o" \
"CMakeFiles/bomberman.dir/src/CBoard.cpp.o" \
"CMakeFiles/bomberman.dir/src/CApplication.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.o" \
"CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.o" \
"CMakeFiles/bomberman.dir/src/CGameManager.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.o" \
"CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.o" \
"CMakeFiles/bomberman.dir/src/CTexturePack.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.o" \
"CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.o" \
"CMakeFiles/bomberman.dir/src/CAnimation.cpp.o"

# External object files for target bomberman
bomberman_EXTERNAL_OBJECTS =

bomberman: CMakeFiles/bomberman.dir/src/main.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/CBoard.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/CApplication.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/CGameObject.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/CSDLInterface.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/CGameManager.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/CWall.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/movables/CPlayer.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/CGround.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemy.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/CBomb.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/CFire.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CCollectible.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/CLevelLoader.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/CTexturePack.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/movables/CMovable.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CDoor.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/collectibles/CBoost.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemyDump.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/gameobjects/movables/CEnemySmart.cpp.o
bomberman: CMakeFiles/bomberman.dir/src/CAnimation.cpp.o
bomberman: CMakeFiles/bomberman.dir/build.make
bomberman: CMakeFiles/bomberman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Linking CXX executable bomberman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bomberman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bomberman.dir/build: bomberman

.PHONY : CMakeFiles/bomberman.dir/build

CMakeFiles/bomberman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bomberman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bomberman.dir/clean

CMakeFiles/bomberman.dir/depend:
	cd /home/jaroslav/CLionProjects/bomberman/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jaroslav/CLionProjects/bomberman /home/jaroslav/CLionProjects/bomberman /home/jaroslav/CLionProjects/bomberman/cmake-build-debug /home/jaroslav/CLionProjects/bomberman/cmake-build-debug /home/jaroslav/CLionProjects/bomberman/cmake-build-debug/CMakeFiles/bomberman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bomberman.dir/depend

