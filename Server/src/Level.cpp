#include "include/Level.hpp"
#include "include/ItemType.hpp"
#include "include/GameObject.hpp"
#include "include/Game.hpp"
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
    if (shieldReset == 5)
    {
        shieldReset = 0;
        playerShieldRaised = false;
    }
    else
    {
        shieldReset++;
    }
    std::string cmd(event["cmd"]);
    if (cmd == "move-player")
    {
        playerx = event["valx"].get<int>();
        playery = event["valy"].get<int>();
        //instructions.push_back({{"cmd", "hemlo"}});
        ce::log(playerx, "=x=player moved=y=", playerx);
    }
    else if (cmd == "kill-enemy")
    {
        int enemyID = event["target"].get<int>();
        for (auto &enemy : enemies)
        {
            if (enemyID == enemy.getID())
                enemy.die();
        }
        ce::log(enemyID, "= Enemy killed");
        parent->addToScore(20);
        json instruction = {
            {"cmd", "set-score"},
            {"otherval", parent->getScore()}};
        addInstruction(instruction);
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
        ce::log("oh no, the player just made the enemy even more mad!");
    }
    else if (cmd == "open-jar")
    {
        parent->addLife();
        int itemID = event["target"].get<int>();
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].getID() == itemID)
            {
                items.erase(i);
                break;
            }
        }
        json instruction = {
            {"cmd", "set-lives"},
            {"otherval", parent->getLifes()}};
        addInstruction(instruction);
    }
    else if (cmd == "open-chest")
    {
        int loot = parent->randomInt(1, 100);
        parent->addToScore(loot);
        int itemID = event["target"].get<int>();
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].getID() == itemID)
            {
                items.erase(i);
                break;
            }
        }
        json instruction = {
            {"cmd", "set-score"},
            {"otherval", parent->getScore()}};
        addInstruction(instruction);
    }
    else if (cmd == "player-shield")
    {
        playerShieldRaised = false;
        shieldReset = 0;
    }
    else if (cmd == "final-level")
    {
        for(auto&x : enemies){
            x.chase_velocity = 3;
            x.route_velocity = 4;
            x.visibility_radius = 20;
        }
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
void Level::setParent(std::shared_ptr<Game> parent)
{
    this->parent = parent;
}
void Level::resolveEnemyAttack()
{

    if (!playerShieldRaised)
    {
        if (parent->takeLife())
        {
            ce::log("player loosed one life");
            json instruction = {
                {"cmd", "set-lives"},
                {"otherval", parent->getLifes()}};
            addInstruction(instruction);
        }
        else
        {
            ce::log("player is now dead, restarting game");
            json instruction = {
                {"cmd", "kill-player"},
                {"otherval", parent->getScore()}};
            addInstruction(instruction);
        }
        shieldReset = 0;
        playerShieldRaised = true;
    }
}
ce::list<Enemy> &Level::getEnemies()
{
    return enemies;
}