#include "include/Level.hpp"
#include "include/ItemType.hpp"
#include "include/GameObject.hpp"

Level::Level(json playerInfo, json obstacles, json items, json enemies, int lengthx, int lengthy) : lengthx{lengthx}, lengthy{lengthy}
{
    this->obstacles = obstacles;
    id = playerInfo["ID"].get<int>();
    playerx = playerInfo["gridx"].get<int>();
    playery = playerInfo["gridy"].get<int>();

    std::string type;
    for (auto x : items)
    {
        type = x["type"];
        Item y{Item::getItemType(type), x["ID"], x["gridy"], x["gridx"]};
        this->items.push_back(y);
    }
    for (auto x : enemies)
    {
        type = x["type"];
        Enemy y{x["ID"], x["gridy"], x["gridx"], type};
        this->enemies.push_back(y);
    }
}

void Level::start(std::shared_ptr<Level> level)
{
    //
    // Genetic Lab Tasks to set initial values
    // set velocities
    // set other values
    //
    for (auto &enemy : enemies)
    {
        enemy.activate(level);

        ce::debuglog("---------------------------");
        ce::debuglog("\n", enemy.getID());
        ce::debuglog(enemy.getTypeS());
        Pathfinding astar(getSimpleMatrix());
        auto demo = astar.AStarSearch(enemy.enemyPos(), playerPos());
        for (auto x : demo)
        {
            auto y = MoveGenerator::directionToString(x);
            std::cout << y << " == ";
        }
        ce::debuglog("---------------------------");
    }
    //ce::errorlog("pauser");
}
void Level::finish()
{
    //Do something
}
gmatrix &Level::getSimpleMatrix()
{
    return state;
}

void Level::updateMatrix(bool printMatrix)
{
    gmatrix simpleMatrix;
    for (int i = 0; i < lengthy; i++)
    {
        ce::list<int> y(1, lengthx);
        simpleMatrix.push_back(y);
    }
    int x;
    int y;
    for (auto obs : obstacles)
    {
        x = obs["gridx"];
        y = obs["gridy"];
        simpleMatrix[y][x] = 0;
    }
    if (!items.empty())
    {
        for (auto item : items)
        {
            x = item.getX();
            y = item.getY();
            simpleMatrix[y][x] = 0;
        }
    }
    if (!enemies.empty())
    {
        for (auto enemy : enemies)
        {
            x = enemy.getX();
            y = enemy.getY();
            simpleMatrix[y][x] = 0;
        }
    }

    if (printMatrix)
    {
        ce::list<ce::list<int>> inverted = ce::list<ce::list<int>>::getInverse(simpleMatrix);
        inverted[lengthy - playery - 1][playerx] = 2;
        for (auto fila : inverted)
        {
            ce::debuglog(fila.toString());
        }
    }
    state = simpleMatrix;
}
void Level::manageEvent(json event)
{
    std::string cmd(event["cmd"]);
    if (cmd == "move-player")
    {
        playerx = event["valx"].get<int>();
        playery = event["valy"].get<int>();
        instructions.push_back({{"cmd", "hemlo"}});
    }
    else if (cmd == "kill-enemy")
    {
        int enemyID = event["target"].get<int>();
        for (auto &enemy : enemies)
        {
            if (enemyID == enemy.getID())
                enemy.die();
        }
    }
    else if (cmd == "hit-enemy")
    {
        int enemyID = event["target"].get<int>();
        for (auto &enemy : enemies)
        {
            if (enemyID == enemy.getID())
            {
                enemy.chase_count++;
                triggerGroupCall(enemyID);
            }
        }
    }
    else if (cmd == "movePlayer")
    {
    }
    else if (cmd == "movePlayer")
    {
    }
    else if (cmd == "movePlayer")
    {
    }
    else if (cmd == "no-action")
    {
    }
    updateMatrix();
    for (auto &x : enemies)
    {
        x.update();
    }
}
void Level::triggerGroupCall(int id)
{
    {
        for (auto &enemy : enemies)
        {
            if (enemy.getID() != id)
            {
                enemy.groupCall();
            }
        }
    }
}
json Level::getInstructions()
{
    json res = instructions;
    instructions = json::array();
    return res;
}
Pair Level::playerPos() const
{
    return std::make_pair(playery, playerx);
}
