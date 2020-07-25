#ifndef GAMESERVER_GAME_HPP
#define GAMESERVER_GAME_HPP

#include <string>
#include "nlohmannJson.hpp"
#include "Level.hpp"
#include <memory>
#include "GeneticLab.hpp"
class Game
{
private:
    std::shared_ptr<Level> currentLevel = nullptr;
    int health = 3;
    int score;
    GeneticLab lab{};
public:
    /**
     * @brief generates a random Integer between the given limits
     * 
     * @param lowerLimit minimal value
     * @param upperLimit maximum value
     * @return int random value
     */
    static int randomInt(int lowerLimit, int upperLimit);
    /**
     * @brief Loads level information based on what-s send by the client
     * 
     * @return std::string 
     */
    std::string startLevel(std::string &);

    /**
     * @brief Get the json instructions as a stringified json
     * 
     * @return std::string request to be handled
     */
    std::string getResponse(std::string &);
    void addLife();
    bool takeLife();
    void addToScore(int toAdd);
    int getLifes();
    int getScore();
};

#endif //GAMESERVER_GAME_HPP
