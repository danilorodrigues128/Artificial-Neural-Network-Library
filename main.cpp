#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ANNL.h>

using namespace std;

int main(int argc, char** argv)
{
	srand(time(NULL));

	NeuralNetwork neuro;

	neuro.setLayers(4);

	neuro.setNeurons(0, 5);
	neuro.setNeurons(1, 3);
	neuro.setNeurons(2, 4);
	neuro.setNeurons(3, 3);

	neuro.config();
	/*
	for (int i = 0; i < neuro.getNLayers() - 1; i++)
		for (int j = 0; j < neuro.getNNeurons(i); j++)
			for (int k = 0; k < neuro.getNNeurons(i + 1); k++)
				neuro.setWeight(i, j, k, (rand() % 2001) - 1000);*/

	neuro.loadWeights("weights.txt");

	neuro.sendPulse(0, 200);
	neuro.sendPulse(1, 100);
	neuro.sendPulse(2, 200);
	neuro.sendPulse(3, 100);
	neuro.sendPulse(4, 200);

	float* output = neuro.outputNeurons();

	for (int i = 0; i < neuro.getNNeurons(neuro.getNLayers() - 1); i++)
	{
		std::cout << output[i] << std::endl;
	}
	std::cout << "----------------" << std::endl;
	for (int i = 0; i < neuro.getNLayers() - 1; i++)
		for (int j = 0; j < neuro.getNNeurons(i); j++)
			for (int k = 0; k < neuro.getNNeurons(i + 1); k++)
				std::cout << neuro.getWeight(i, j, k) << std::endl;

	//neuro.saveWeights("weights.txt");

	return 0;
}