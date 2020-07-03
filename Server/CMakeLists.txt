cmake_minimum_required(VERSION 3.5)
project(gameserver VERSION 1.0.0 LANGUAGES CXX C)
INCLUDE(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DEFAULT_BUILD_TYPE "Release")


set(INCL src/include)
set(HEADERS ${INCL}/list.hpp ${INCL}/nlohmannJson.hpp
        ${INCL}/Server.hpp ${INCL}/Game.hpp ${INCL}/GeneticLab.hpp
        ${INCL}/Level.hpp ${INCL}/GOType.hpp ${INCL}/Direction.hpp
        ${INCL}/EnemyType.hpp ${INCL}/MoveGenerator.hpp ${INCL}/Enemy.hpp
        ${INCL}/GameObject.hpp ${INCL}/Pathfinding.hpp ${INCL}/RouteType)

set(SOURCE_FILES
        src/main.cpp
        src/Server.cpp src/Game.cpp src/GeneticLab.cpp
        src/Level.cpp src/MoveGenerator.cpp src/Enemy.cpp
        src/GameObject.cpp)

add_executable(server ${SOURCE_FILES} ${HEADERS})