#include "include/Game.hpp"
#include "include/utilities.hpp"
#include "include/GameObject.hpp"
#include <memory>
#include <sstream>

using json = nlohmann::json;
std::string Game::startLevel(std::string &levelData)
{
    ce::log("loading level");
    json initialData = json::parse(levelData);
    int lengthx = initialData["lengthx"];
    int lengthy = initialData["lengthy"];
    json playerInfo = initialData["player"];
    json enemies = initialData["enemies"];
    json items = initialData["items"];
    json otherObj = initialData["otherObj"];

    std::shared_ptr<Level> newLevel(new Level(playerInfo, otherObj, items, enemies, lengthx, lengthy));
    currentLevel = newLevel;
    currentLevel->getSimpleMatrix();
    json loadLevelResponse = {
        {"playerLives", playerLives}};
    return loadLevelResponse.dump(); //returns the amount of initial health
}

std::string Game::getResponse(std::string &action)
{
    json clientAction = json::parse(action);
    ce::debuglog(clientAction);
    currentLevel->manageEvent(clientAction);
    currentLevel->getSimpleMatrix();
    json instructions = currentLevel->getInstructions();
    return instructions.dump();
}
