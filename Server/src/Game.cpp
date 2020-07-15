#include "include/Game.hpp"
#include "include/utilities.hpp"
#include "include/GameObject.hpp"
#include <memory>
#include <sstream>

using json = nlohmann::json;
std::string Game::startLevel(std::string& levelData)
{
    json initialData = json::parse(levelData);

    int lengthx = initialData["lengthx"];
    int lengthy = initialData["lengthy"];
    json player = initialData["player"];
    json enemies = initialData["enemies"];
    json items = initialData["items"];
    json otherObj = initialData["otherObj"];

    std::shared_ptr<Level> newLevel(new Level(player,otherObj,items,enemies,lengthx, lengthy));
    currentLevel = newLevel;
    currentLevel->getSimpleMatrix();
    json loadLevelResponse = {
        {"playerLives",playerLives}
    };

    return loadLevelResponse.dump();//returns the amount of initial health
}

std::string Game::getResponse(std::string& action)
{
    std::ifstream ifs("/home/jose/Desktop/githubU/SpiritTemple/Extra/clientAction.json");
    json clientAction;
    ifs >> clientAction;
    std::string reqType = clientAction["reqType"];
    ce::debuglog(reqType);
    return reqType;
}

