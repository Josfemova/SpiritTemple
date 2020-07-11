#ifndef GAMESERVER_GENETICLAB_HPP
#define GAMESERVER_GENETICLAB_HPP

class GeneticLab
{
public:
    int fitness(int harm, int deathOrder, int chasesAmount);
    int *generateFitnessArray(int spectrums[][5]);
    int selectMax(int arr[]);
    void selection(int fitnessArr[], int spectrums[][5]);
    void crossover(int spectrums[]);
};

#endif //GAMESERVER_GENETICLAB_HPP
