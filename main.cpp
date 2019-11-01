
//-----[EXAMPLE]-----//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ANNL.h>

using namespace std;

int main(int argc, char** argv)
{
	NeuralNetwork Net;

	Net.setLayers(4);

	Net.setNeurons(0, 5);
	Net.setNeurons(1, 3);
	Net.setNeurons(2, 4);
	Net.setNeurons(3, 3);

	Net.config();
	
	srand(time(NULL));
	for (int i = 0; i < Net.getNLayers() - 1; i++)
		for (int j = 0; j < Net.getNNeurons(i); j++)
			for (int k = 0; k < Net.getNNeurons(i + 1); k++)
				Net.setWeight(i, j, k, (rand() % 2001) - 1000);

	Net.sendPulse(0, 200);
	Net.sendPulse(1, 100);
	Net.sendPulse(2, 200);
	Net.sendPulse(3, 100);
	Net.sendPulse(4, 200);

	float* output = Net.outputNeurons();

	for (int i = 0; i < Net.getNNeurons(Net.getNLayers() - 1); i++)
		std::cout << output[i] << std::endl;

	return 0;
}