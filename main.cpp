
//-----[EXAMPLE]-----//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ANNL.h>

int main(int argc, char** argv)
{
	NeuralNetwork Net(NeuralNetwork::LINEAR, true); //Creates the Neural Network

	Net.setLayers(4); //Sets 4 layers

	Net.setNeurons(0, 5); //5 neurons on the layer 0
	Net.setNeurons(1, 3); //3 neurons on the layer 1
	Net.setNeurons(2, 4); //4 neurons on the layer 2
	Net.setNeurons(3, 3); //3 neurons on the layer 3

	Net.config(); //Configure arrays used during feedforward and backpropagation

	srand(time(NULL));
	for (int i = 0; i < Net.getNLayers() - 1; i++)
	{
		for (int j = 0; j < Net.getNNeurons(i); j++)
		{
			for (int k = 0; k < Net.getNNeurons(i + 1); k++)
			{
				Net.setWeight(i, j, k, (rand() % 2001) - 1000); //Sets random weights
				if (i > 0)
					Net.setBias(i, j, (rand() % 201) - 100); //Sets random biases
			}
		}
	}

	Net.Pulse = { 2, 4, 6, 8, 10 }; //Sets (2, 4, 6, 8, 10) as the input for the Neural Network
	Net.Hypothesis = { 5, 10, 15 }; //Sets (5, 10, 15) as the Network's expected output

	for (int i = 0; i < 1000; i++) //1000 epochs
	{
		system("cls");
		
		float* output = Net.feedforward(); //Propagate the pulse through the Network and backpropagate the Cost
		
		for (int i = 0; i < Net.getNNeurons(Net.getNLayers() - 1); i++)
			std::cout << output[i] << std::endl;
		
		Net.recalculateParameters(0.05); //Calculate the new weights and biases according to the average gradient of the Cost Function
	}

	Net.save("Param.ANNL"); //Saves the weights and biases

	return 0;
}
