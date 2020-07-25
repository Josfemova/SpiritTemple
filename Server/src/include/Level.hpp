#ifndef GAMESERVER_LEVEL_HPP
#define GAMESERVER_LEVEL_HPP

#include "list.hpp"
#include "nlohmannJson.hpp"
#include "Item.hpp"
#include "Enemy.hpp"
#include "GeneticLab.hpp"

typedef ce::list<std::string> lvlInstructions;
typedef std::pair<int, int> Pair;
using json = nlohmann::json;

class GeneticLab;
class Enemy;
class Item;
class Level
{
private:
    friend class GeneticLab;
    int id;
    int playerx;
    int playery;
    json obstacles;
    json instructions;
    ce::list<Item> items;
    ce::list<Enemy> enemies;
    gmatrix state;

public:
    /**
     * @brief adds a json request to the payload to be sent to the client
     * 
     * @param instruction 
     */
    void addInstruction(json instruction)
    {
        instructions.push_back(instruction);
    }
    const int lengthx;
    const int lengthy;
    /**
     * @brief Construct a new Level based on the Json information from the client
     * 
     * @param playerInfo json with player information
     * @param obstacles json  array with obstacle positions
     * @param items json with item information
     * @param enemies json array with enemy information
     * @param lengthx horizontal size of the level
     * @param lengthy vertical size of the level
     */
    Level(json playerInfo, json obstacles, json items, json enemies, int lengthx, int lengthy);
    /**
     * @brief ends the level
     * 
     */
    void finish();
    /**
     * @brief Performs initial tasks related to the level start
     * 
     * @param level 
     */
    void start(std::shared_ptr<Level> level);
    /**
     * @brief refreshes the game matrix
     * 
     * @param printMatrix print the matrix to the console
     */
    void updateMatrix(bool printMatrix = false);
    /**
     * @brief returns the game matrix representing the current state
     * 
     * @return gmatrix& 
     */
    gmatrix &getSimpleMatrix();

    /**
     * @brief handles events communicated by the client
     * 
     * @param event json information about the event
     */
    void manageEvent(json event);
    /**
     * @brief and enemy can call this method to trigger the groupCall method of all it's pears
     * 
     * @param id 
     */
    void triggerGroupCall(int id);
    /**
     * @brief Get the Instructions objectreturn json array with all the stores instructions so far
     * 
     * @return json 
     */
    json getInstructions();
    /**
     * @brief returns player position as an YX coordinate
     * 
     * @return Pair 
     */
    Pair playerPos() const;
};

#endif //GAMESERVER_LEVEL_HPP
