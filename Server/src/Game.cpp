#include "include/Game.hpp"
#include "include/utilities.hpp"

using json = nlohmann::json;
void Game::generateMatrix()
{

    std::ifstream ifs("/home/jose/Desktop/githubU/SpiritTemple/Extra/initialData.json");
    json initialData;
    ifs >> initialData;
    std::string lenghty = initialData["lenghty"];
    std::string lenghtx = initialData["lenghtx"];

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

}

std::string Game::getResponse(std::string action)
{
    std::ifstream ifs("/home/jose/Desktop/githubU/SpiritTemple/Extra/clientAction.json");
    json clientAction;
    ifs >> clientAction;
    std::string reqType = clientAction["reqType"];
    ce::debuglog(reqType);
}

