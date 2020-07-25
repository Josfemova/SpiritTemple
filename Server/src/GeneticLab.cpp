#include "include/GeneticLab.hpp"
#include <random>
#include "include/Level.hpp"
using namespace ce;
void GeneticLab::assignProperties(Level &level, bool verify)
{
    list<Enemy &> spectrums;
    for (Enemy &enemy : level.enemies)
    {
        if (enemy.enemyType != EnemyType::Mouse && enemy.enemyType != EnemyType::Chuchu)
            spectrums.push_back(enemy);
    }
    int spectrumCnt = spectrums.size();
    list<list<int>> newValues;
    int enemyCnt = spectrumCnt;
    if (cicle == 0)
        newValues = randomValues(spectrumCnt);
    else
        newValues = geneticAlgorithm(spectrumListToArray(spectrums));
    cicle+=1;
    for (int i = 0; i < spectrumCnt; i++)
    {
        Enemy &spec = spectrums[i];
        list<int> values = newValues[i];
        spec.route_velocity = values[normal_v];
        spec.chase_velocity = values[chase_v];
        spec.visibility_radius = values[v_radius];
    }

    if (verify)
    {
        for (Enemy &enemy : level.enemies)
        {
            if (enemy.enemyType != EnemyType::Mouse && enemy.enemyType != EnemyType::Chuchu){
                ce::debuglog(enemy.toString());
            }
                
        }
    }
}
list<list<int>> GeneticLab::spectrumListToArray(list<Enemy &> spectrums)
{
    list<list<int>> result;
    for (auto& x : spectrums)
    {
        result.push_back(list<int>{x.route_velocity, x.chase_velocity, x.visibility_radius, x.deathOrder, x.chase_count});
    }
    return result;
}
ce::list<ce::list<int>> GeneticLab::randomValues(int size)
{
    std::random_device dev;
    std::mt19937 mt(dev());
    auto rng = [&mt]() {
        std::uniform_int_distribution<int> randomGen(5, 10);
        return randomGen(mt);
    };

    ce::list<ce::list<int>> result;
    for (int i = 0; i < size; i++)
    {
        result.push_back(ce::list<int>{rng(), rng(), rng(), 0, 0});
    }

    return result;
}
list<list<int>> GeneticLab::geneticAlgorithm(list<list<int>> population)
{

    // velocity can be up to 11, lower is faster
    // radious can be up to 10, higher is bigger

    //=========================Random lambda utility===============================
    std::random_device dev;
    std::mt19937 rng(dev());
    auto randomInt = [&rng](int lowerLimit, int upperLimit) {
        std::uniform_int_distribution<int> randomGen(lowerLimit, upperLimit);
        return randomGen(rng);
    };
    //===============Lambda functions for genetic algorithm=========================

    auto fitness = [&, this](list<int> chromosome) {
        double fit = chromosome[death_order] * 2 + (chromosome[chase_cnt]);
        return fit;
    };
    auto mutate = [&, this](list<int> chromosome) { //only 0,1,2 are mutable characteristics
        chromosome[randomInt(0, 2)] = randomInt(5, 10);
        return chromosome;
    };
    //returns 1 children;
    auto crossover = [&, this](list<int> parentA, list<int> parentB) {
        list<int> result{0, 0, 0, 0, 0};
        result[normal_v] = (randomInt(1, 10) % 2 == 0) ? parentA[normal_v] : parentB[normal_v];
        result[chase_v] = (randomInt(1, 10) % 2 == 0) ? parentA[chase_v] : parentB[chase_v];
        result[v_radius] = (randomInt(1, 10) % 2 == 0) ? parentA[v_radius] : parentB[v_radius];
        return result;
    };
    //=============================================================================

    //======================Select the most fit=============================
    list<int> bestfit = population.front();
    list<int> secondBest = population.back();

    for (auto &chromosome : population)
    {
        int cfitness = fitness(chromosome);
        if (cfitness > fitness(bestfit))
            bestfit = chromosome;
        else if (cfitness > fitness(secondBest))
            secondBest = chromosome;
    }

    //======================Add crossover and mutate========================
    list<list<int>> result;
    for (int i = 0; i < population.size(); i++)
    {
        result.push_back(mutate(crossover(bestfit, secondBest)));
    }
    return result;

    //======================
}