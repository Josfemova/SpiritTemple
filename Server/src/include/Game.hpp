#ifndef GAMESERVER_GAME_HPP
#define GAMESERVER_GAME_HPP
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "./nlohmannJson.hpp"

using json = nlohmann::json;

using namespace std;

class Game
{

public:

    void generateMatrix()

    {
        ifstream ifs("/home/valeria/Documents/SpiritTemple-master/Extra/initialData.json");
        json initialData;
        ifs >> initialData;

        string _comment = initialData["_comment"];
        string _comment2 = initialData["_comment2"];
        string lenghty = initialData["lenghty"];
        string lenghtx = initialData["lenghtx"];

        //_________________/ PLAYER DATA /_________________

        int player[3] = {initialData["player"]["ID"], initialData["player"]["gridx"], initialData["player"]["gridy"]};
        cout << "\nplayer: ";
        for (int i = 0; i < 3; i++)
        {
            cout << player[i] << ", ";
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

        cout << "\nenemies: ";
        for (int i = 0; i < num_enemies; i++)
        {
            cout << "[ ";
            for (int j = 0; j < 4; j++)
            {
                if (j == 3)
                {
                    cout << enemies[i][j];
                }
                else
                {
                    cout << enemies[i][j] << ", ";
                }
            }
            cout << " ], ";
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

        cout << "\notherObj: ";
        for (int i = 0; i < num_otherObj; i++)
        {
            cout << "[ ";
            for (int j = 0; j < 4; j++)
            {
                if (j == 3)
                {
                    cout << otherObj[i][j];
                }
                else
                {
                    cout << otherObj[i][j] << ", ";
                }
            }
            cout << " ], ";
        }
    }
    
};

#endif //GAMESERVER_GAME_HPP
