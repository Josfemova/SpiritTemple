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

    int player[3] = {initialData["player"]["ID"], initialData["player"]["gridx"], initialData["player"]["gridy"]};
    ce::debuglog("\nplayer: ");
    for (int i = 0; i < 3; i++)
    {
        ce::debuglog(player[i],", ");
    }

    //_________________/ ENEMIES DATA /_________________

    int num_enemies = (initialData["enemies"]).size(); //numero de enemigos
    int enemies[num_enemies][4];                       //matriz de enemigos: enemies[columnas][filas]

    for (int i = 0; i < num_enemies; i++)
    {
        enemies[i][0] = initialData["enemies"][i]["ID"];
        enemies[i][1] = 0; //type (string)
        enemies[i][2] = initialData["enemies"][i]["gridx"];
        enemies[i][3] = initialData["enemies"][i]["gridy"];
    }

    ce::debuglog("\nenemies: ");
    for (int i = 0; i < num_enemies; i++)
    {
        ce::debuglog("[ ");
        for (int j = 0; j < 4; j++)
        {
            if (j == 3)
            {
                ce::debuglog(enemies[i][j]);
            }
            else
            {
                ce::debuglog(enemies[i][j],",");
            }
        }
        ce::debuglog(" ], ");
    }

    //_________________/ OTHER OBJECTS DATA /_________________

    int num_otherObj = (initialData["otherObj"]).size(); //numero de otherObj
    int otherObj[num_otherObj][5];                       //matriz de enemigos otherObj[columnas][filas]

    for (int i = 0; i < num_otherObj; i++)
    {
        otherObj[i][0] = initialData["otherObj"][i]["ID"];
        otherObj[i][1] = initialData["otherObj"][i]["xmin"];
        otherObj[i][2] = initialData["otherObj"][i]["xmax"];
        otherObj[i][3] = initialData["otherObj"][i]["ymin"];
        otherObj[i][4] = initialData["otherObj"][i]["ymax"];
    }

    ce::debuglog("\notherObj: ");
    for (int i = 0; i < num_otherObj; i++)
    {
        ce::debuglog("[ ");
        for (int j = 0; j < 4; j++)
        {
            if (j == 3)
            {
                ce::debuglog(otherObj[i][j]);
            }
            else
            {
                ce::debuglog(otherObj[i][j],", ");
            }
        }
        ce::debuglog(" ], ");
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

