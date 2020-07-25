#ifndef GAMESERVER_GENETICLAB_HPP
#define GAMESERVER_GENETICLAB_HPP

#include "Enemy.hpp"
#include "list.hpp"
class Level;
class Enemy;
class GeneticLab
{
private:
    int cicle = 0;
    const int normal_v = 0;
    const int chase_v = 1;
    const int v_radius = 2;
    const int death_order = 3;
    const int chase_cnt = 4;

public:
    void assignProperties(Level &level, Level& lastLevel, bool verify = true);
    ce::list<ce::list<int>> spectrumListToArray(ce::list<Enemy &> spectrum);
    ce::list<ce::list<int>> randomValues(int size);
    ce::list<ce::list<int>> geneticAlgorithm(ce::list<ce::list<int>> population);
};

#endif //GAMESERVER_GENETICLAB_HPP
