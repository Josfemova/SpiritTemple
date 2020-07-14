cmake_minimum_required(VERSION 3.12)
project(gameserver VERSION 1.0.0 LANGUAGES CXX)
INCLUDE(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(DEFAULT_BUILD_TYPE "Release")


set(INCL src/include)
set(HEADERS ${INCL}/list.hpp ${INCL}/nlohmannJson.hpp
        ${INCL}/Server.hpp ${INCL}/Game.hpp ${INCL}/GeneticLab.hpp
        ${INCL}/Level.hpp ${INCL}/GOType.hpp ${INCL}/Direction.hpp
        ${INCL}/EnemyType.hpp ${INCL}/MoveGenerator.hpp ${INCL}/Enemy.hpp
        ${INCL}/GameObject.hpp ${INCL}/Pathfinding.hpp ${INCL}/RouteType.hpp
        ${INCL}/utilities.hpp ${INCL}/ItemType.hpp ${INCL}/Item.hpp)

set(SOURCE_FILES
        src/main.cpp
        src/Server.cpp src/Game.cpp src/GeneticLab.cpp
        src/Level.cpp src/MoveGenerator.cpp src/Enemy.cpp
        src/GameObject.cpp src/Item.cpp src/Pathfinding.cpp)

add_executable(server ${SOURCE_FILES} ${HEADERS})