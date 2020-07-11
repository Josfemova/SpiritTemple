#include "include/GeneticLab.hpp"

//MATRIX SPECTRUMS [vision radius, velocity, harm, deathOrder, chasesAmount]

int GeneticLab::fitness(int harm, int deathOrder, int chasesAmount)
{
    return harm + deathOrder + chasesAmount;
}

int *GeneticLab::generateFitnessArray(int spectrums[][5])
{
    int fitnessArr[sizeof(spectrums)];
    for (int i = 0; i < sizeof(spectrums); i++)
    {
        int harm = spectrums[i][2];
        int deathOrder = spectrums[i][3];
        int chasesAmount = spectrums[i][4];
        fitnessArr[i] = fitness(harm, deathOrder, chasesAmount);
    }
    return fitnessArr;
}

int GeneticLab::selectMax(int arr[])
{
    int maxKey;
    for (int i = 0; i < sizeof(arr); i++)
    {
        if (arr[i] >= arr[i + 1])
        {
            maxKey = i;
        }
        else
        {
            maxKey = i + 1;
        }
    }
    return maxKey;
}

void GeneticLab::selection(int fitnessArr[], int spectrums[][5])
{
    int spectrum1_key = selectMax(fitnessArr);
    fitnessArr[spectrum1_key] = 0;
    int spectrum2_key = selectMax(fitnessArr);
}

void GeneticLab::crossover(int spectrums[])
{
}
