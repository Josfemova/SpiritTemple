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
    int lengthx = initialData["lengthx"].get<int>();
    int lengthy = initialData["lengthy"].get<int>();
    json playerInfo = initialData["player"];
    json enemies = initialData["enemies"];
    json items = initialData["items"];
    json otherObj = initialData["otherObj"];

    std::shared_ptr<Level> newLevel(new Level(playerInfo, otherObj, items, enemies, lengthx, lengthy));
    currentLevel = newLevel;
    currentLevel->start(currentLevel);
    json loadLevelResponse = {
        {"playerLives", playerLives}};
    return loadLevelResponse.dump(); //returns the amount of initial health
}

std::string Game::getResponse(std::string &action)
{
    json clientAction = json::parse(action);
    currentLevel->manageEvent(clientAction);
    currentLevel->getSimpleMatrix();
    json instructions = currentLevel->getInstructions();
    return instructions.dump();
}
int Game::randomInt(int lowerLimit, int upperLimit)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> randomGen(lowerLimit, upperLimit);
}