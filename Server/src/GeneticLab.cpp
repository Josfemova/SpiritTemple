#include "include/GeneticLab.hpp"
#include <iostream>

using namespace std;

//MATRIX SPECTRUMS [vision radius, velocity, harm, deathOrder, chasesAmount]

void GeneticLab::printMatrix(int spectrums[][5])
{

    cout << "SPECTRUMS:\n[ ";
    for (int i = 0; i < spectrumCount; i++)
    {
        cout << "[ ";
        for (int j = 0; j < 5; j++)
        {
            cout << spectrums[i][j] << ", ";
        }
        cout << "]" << endl;
    }
    cout << "]" << endl;
}

void GeneticLab::initSpectrums()
{
    int spectrum1[] = {1, 1, 1, 1, 1};
    int spectrum2[] = {2, 2, 2, 2, 2};
    int spectrum3[] = {3, 3, 3, 3, 3};

    for (int j = 0; j < 5; j++)
    {
        spectrums[0][j] = spectrum1[j];
        spectrums[1][j] = spectrum2[j];
        spectrums[2][j] = spectrum3[j];
    }
    spectrumCount = 3;
}

int GeneticLab::geneticAlgorithm()
{
    initSpectrums();
    selection(generateFitnessArray());
    crossover();
}

int GeneticLab::fitness(int harm, int deathOrder, int chasesAmount)
{
    return harm + deathOrder + chasesAmount;
}

int *GeneticLab::generateFitnessArray()
{
    int *fitnessArr = (int *)malloc(spectrumCount * sizeof(int));

    for (int i = 0; i < spectrumCount; i++)
    {
        int harm = spectrums[i][2];
        int deathOrder = spectrums[i][3];
        int chasesAmount = spectrums[i][4];
        fitnessArr[i] = fitness(harm, deathOrder, chasesAmount);
    }
    printFitnessArray(fitnessArr);
    return fitnessArr;
}

void GeneticLab::printFitnessArray(int fitnessArr[])
{
    cout << "FITNESS: [ ";
    for (int i = 0; i < spectrumCount; i++)
    {
        cout << fitnessArr[i] << ", ";
    }
    cout << "]" << endl;
}

int GeneticLab::selectMax(int arr[], int arrSize)
{
    int maxKey;
    for (int i = 0; i < arrSize; i++)
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
    cout << "MAX: " << arr[maxKey] << endl;
    return maxKey;
}

int *GeneticLab::selection(int fitnessArr[])
{

    spectrumCount = (spectrumCount/2)+1;
    int newSpectrums[spectrumCount][5];
    for(int i = 0; i < spectrumCount; i++)
    {
        int spectrum_key = selectMax(fitnessArr, spectrumCount);
        fitnessArr[spectrum_key] = 0;
        
        for (int j = 0; j < 5; j++)
        {
            newSpectrums[i][j] = spectrums[spectrum_key][j];
            spectrums[i][j] = newSpectrums[i][j];
        }

    }
    
    for (int i = 2; i < spectrumCount; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            spectrums[i][j] = 0;
        }
    }
}

void GeneticLab::crossover()
{
    int crossoverCount = spectrumCount;
    while(crossoverCount >= 2)
    {
        srand((unsigned int)time(NULL));
        int spectrum1 = (((rand() % spectrumCount) + 1)-1);       //Random spectrum
        int spectrum2 = (((rand() % spectrumCount) + 1)-1);
        int trait = ((rand() % 2) + 1)-1;                       // Random trait

        while(spectrum1 == spectrum2)
        {
            spectrum2 = (rand() % spectrumCount) + 1;
        }

        cout << "SPECTRUM 1: " << spectrums[spectrum1][trait] << "\nSPECTRUM 2: " << spectrums[spectrum2][trait] << endl;
        int children[5] = {spectrums[spectrum1][trait], spectrums[spectrum2][trait]};
        spectrums[spectrumCount][0] = spectrums[spectrum1][trait];
        spectrums[spectrumCount][1] = spectrums[spectrum2][trait];
        spectrumCount++;

        crossoverCount = crossoverCount - 2;
    }
}

void GeneticLab::mutation()
{

}
