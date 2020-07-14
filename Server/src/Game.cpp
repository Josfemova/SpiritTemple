#include "include/Game.hpp"
#include "include/utilities.hpp"
#include "include/GameObject.hpp"
#include <memory>

using json = nlohmann::json;
void Game::startLevel()
{
    std::ifstream ifs("/home/jose/Desktop/githubU/SpiritTemple/Extra/initialData.json");
    json initialData;
    ifs >> initialData;
    int lengthx = initialData["lengthx"];
    int lengthy = initialData["lengthy"];
    //_________________/ PLAYER DATA /_________________
    json player = initialData["player"];
    //_________________/ ENEMIES DATA /_________________
    json enemies = initialData["enemies"];
    for(auto x : enemies){
        ce::debuglog(x);
    }
    json items = initialData["items"];
    for(auto x : items){
        ce::debuglog(x);
    }
    //_________________/ OTHER OBJECTS DATA /_________________
    json otherObj = initialData["otherObj"];
    for(auto x : otherObj){
        ce::debuglog(x);
    }
    std::shared_ptr<Level> newLevel(new Level(player,otherObj, items,enemies));
    currentLevel = newLevel;
    //currentLevel->getMatrix();
}

std::string Game::getResponse(std::string action)
{
    std::ifstream ifs("/home/jose/Desktop/githubU/SpiritTemple/Extra/clientAction.json");
    json clientAction;
    ifs >> clientAction;
    std::string reqType = clientAction["reqType"];
    ce::debuglog(reqType);
    return reqType;
}

