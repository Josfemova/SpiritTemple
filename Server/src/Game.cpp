#include "include/Game.hpp"
#include "include/utilities.hpp"
#include "include/GameObject.hpp"
#include <memory>
#include <random>

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
    std::shared_ptr<Level> lastLevel = currentLevel;
    currentLevel = newLevel;
    currentLevel->setParent(std::shared_ptr<Game>(this));
    currentLevel->updateMatrix();
    currentLevel->start(currentLevel);
    if(lastLevel==nullptr){
        ce::debuglog("arriba");
        lab.assignProperties(*currentLevel, *currentLevel);
    }else{
        lab.assignProperties(*currentLevel, *lastLevel);
    }
    json loadLevelResponse;
    loadLevelResponse.push_back({
        {"cmd", "set-lives"},
        {"otherval",health}
    });
    json response = {
        {"commands", loadLevelResponse}
    };
    std::string resp =response.dump();
    //ce::debuglog(resp);
    return resp; //returns the amount of initial health
}

std::string Game::getResponse(std::string &action)
{
    json clientAction = json::parse(action);
    currentLevel->manageEvent(clientAction);

    json instructions = currentLevel->getInstructions();
    std::string resp;
    if (instructions.empty())
    {
        resp = "{\"commands\":[{\"cmd\":\"no-action\"}]}";
    }
    else
    {
        json response = {{"commands",instructions}};
        resp = response.dump();
    }
    return resp;
}
int Game::randomInt(int lowerLimit, int upperLimit)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> randomGen(lowerLimit, upperLimit);
    return randomGen(rng);
}
void Game::addToScore(int toAdd){
    score+=toAdd;
}
void Game::addLife(){
    if(health<5){
        ++health;
    }
}
bool Game::takeLife(){
    if(health==1){
        return false;
    }else{
        --health;
        return true;
    }
}
int Game::getScore(){
    return score;
}
int Game::getLifes(){
    return health;
}