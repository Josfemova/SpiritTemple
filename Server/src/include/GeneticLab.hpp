#ifndef GAMESERVER_GENETICLAB_HPP
#define GAMESERVER_GENETICLAB_HPP

class GeneticLab
{
public:
    int spectrumCount;
    int spectrums[][5];
    void printMatrix(int spectrums[][5]);
    void initSpectrums();
    int geneticAlgorithm();
    int fitness(int harm, int deathOrder, int chasesAmount);
    int *generateFitnessArray();
    void printFitnessArray(int fitnessArr[]);
    int selectMax(int arr[], int arrSize);
    int *selection(int fitnessArr[]);
    void crossover();
    void mutation();
};

#endif //GAMESERVER_GENETICLAB_HPP
