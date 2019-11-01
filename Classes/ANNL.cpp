#include <ANNL.h>
#include <iostream>
#include <fstream>
#include <string>

NeuralNetwork::NeuralNetwork()
{
	n_layers = 0;
	n_neurons = NULL;
	layers = NULL;
}

void NeuralNetwork::config()
{
	setSynapses();
	allocateWeights();
	allocatePulses();
}

void NeuralNetwork::setLayers(int _Layers)
{
	if (_Layers < 2)
	{
		std::cout << "[ERROR] _Layers must be greater than 1!" << std::endl;
		exit(0);
	}
	
	n_layers = _Layers;
	n_neurons = new int[_Layers];
	layers = new Layer[_Layers];
}

void NeuralNetwork::allocateWeights()
{
	for (int i = 0; i < n_layers; i++)
		for (int j = 0; j < n_neurons[i]; j++)
			layers[i].neurons[j].allocateWeight();
}

void NeuralNetwork::allocatePulses()
{
	for (int i = 0; i < n_layers; i++)
		for (int j = 0; j < n_neurons[i]; j++)
			layers[i].neurons[j].allocatePulses();
}

void NeuralNetwork::setNeurons(int _Layer, int _nNeuron)
{
	if (_Layer > n_layers - 1 || _Layer < 0)
	{
		std::cout << "[ERROR] Layer '" << _Layer << "' not found!" << std::endl;
		exit(0);
	}
	else if(_nNeuron < 0)
	{
		std::cout << "[ERROR] _nNeurons must be a positive number!" << std::endl;
		exit(0);
	}

	layers[_Layer].setNeurons(_nNeuron);
	n_neurons[_Layer] = _nNeuron;
}

void NeuralNetwork::setSynapses()
{
	for (int i = 0; i < n_layers; i++)
	{
		for (int j = 0; j < n_neurons[i]; j++)
		{
			int nB = 0, nF = 0;
			if (i == 0)
			{
				nB = 0;
				nF = n_neurons[1];
			}
			else if (i == n_layers - 1)
			{
				nB = n_neurons[n_layers - 2];
				nF = 0;
			}
			else
			{
				nB = n_neurons[i - 1];
				nF = n_neurons[i + 1];
			}

			layers[i].neurons[j].setNeuronsAround(nB, nF);
		}
	}
}

void NeuralNetwork::setWeight(int _fromLayer, int _fromNeuron, int _toNeuron, int _Weight)
{
	if (_fromLayer < 0 || _fromLayer > n_layers - 2)
	{
		std::cout << "[ERROR] Layer '" << _fromLayer << "' not found!" << std::endl;
		exit(0);
	}
	else if (_fromNeuron < 0 || _fromNeuron > n_neurons[_fromLayer] - 1)
	{
		std::cout << "[ERROR] Neuron '" << _fromNeuron << "' not found on layer '" << _fromLayer << "'" << std::endl;
		exit(0);
	}
	else if (_toNeuron < 0 || _toNeuron > n_neurons[_fromLayer + 1] - 1)
	{
		std::cout << "[ERROR] Neuron '" << _toNeuron << "' not found on layer '" << _fromLayer + 1 << "'!" << std::endl;
		exit(0);
	}
	else if (_Weight < -1000 || _Weight > 1000)
	{
		std::cout << "[ERROR] _Weight must be an integer between -1000 and 1000!" << std::endl;
		exit(0);
	}

	layers[_fromLayer].neurons[_fromNeuron].setWeight(_toNeuron, _Weight);
}

int NeuralNetwork::getNNeurons(int _Layer)
{
	if (_Layer < 0 || _Layer > n_layers - 1)
	{
		std::cout << "[ERROR] Layer '" << _Layer << "' not found!" << std::endl;
		exit(0);
	}

	return n_neurons[_Layer];
}

int NeuralNetwork::getNLayers()
{
	return n_layers;
}

int NeuralNetwork::getWeight(int _fromLayer, int _fromNeuron, int _toNeuron)
{
	if (_fromLayer < 0 || _fromLayer > n_layers - 1)
	{
		if (_fromLayer == n_layers - 1)
		{
			std::cout << "[ERROR] Layer '" << _fromLayer << "' does not store weights!" << std::endl;
			exit(0);
		}
		std::cout << "[ERROR] Layer '" << _fromLayer << "' not found!" << std::endl;
		exit(0);
	}
	else if (_fromNeuron < 0 || _fromNeuron > n_neurons[_fromLayer] - 1)
	{
		std::cout << "[ERROR] Neuron '" << _fromNeuron << "' not found on layer '" << _fromLayer << "'" << std::endl;
		exit(0);
	}
	else if (_toNeuron < 0 || _toNeuron > n_neurons[_fromLayer + 1] - 1)
	{
		std::cout << "[ERROR] Neuron '" << _toNeuron << "' not found on layer '" << _fromLayer + 1 << "'!" << std::endl;
		exit(0);
	}

	return layers[_fromLayer].neurons[_fromNeuron].getWeight(_toNeuron);
}

void NeuralNetwork::sendPulse(int _fromNeuron, float _Pulse)
{
	if (_fromNeuron < 0 || _fromNeuron > n_neurons[0] - 1)
	{
		std::cout << "[ERROR] Neuron '" << _fromNeuron << "' not found on layer '" << 0 << "'" << std::endl;
		exit(0);
	}

	float* mult = layers[0].neurons[_fromNeuron].multiplyWeights(_Pulse);
	
	for (int i = 0; i < n_neurons[1]; i++)
	{
		layers[1].neurons[i].resetPulse(_fromNeuron);
		layers[1].neurons[i].recievePulse(_fromNeuron, mult[i]);
	}
}

void NeuralNetwork::saveWeights(const char _Path[])
{
	std::ofstream FILE;
	FILE.open(_Path);
	for (int i = 0; i < n_layers - 1; i++)
		for (int j = 0; j < n_neurons[i]; j++)
			for (int k = 0; k < n_neurons[i + 1]; k++)
				FILE << getWeight(i, j, k) << "\n";
	FILE.close();
}

void NeuralNetwork::loadWeights(const char _Path[])
{
	std::ifstream FILE;
	int line;
	FILE.open(_Path);
	while (FILE >> line)
	{
		std::cout << line << std::endl;
	}
	FILE.close();
}

float* NeuralNetwork::outputNeurons()
{
	float sum = 0;
	float* output = NULL;

	if (n_neurons[n_layers - 1] > 0)
		output = new float[n_neurons[n_layers - 1]];

	for (int i = 1; i < n_layers - 1; i++)
	{
		for (int j = 0; j < n_neurons[i]; j++)
		{
			sum = 0;
			for (int k = 0; k < n_neurons[i - 1]; k++)
			{
				sum += layers[i].neurons[j].getPulse(k);
			}

			if (sum < 0)
				sum = 0;

			for (int k = 0; k < n_neurons[i + 1]; k++)
			{
				layers[i + 1].neurons[k].resetPulse(j);
				layers[i + 1].neurons[k].recievePulse(j, sum * layers[i].neurons[j].getWeight(k));
			}
		}
	}

	for (int j = 0; j < n_neurons[n_layers - 1]; j++)
	{
		sum = 0;
		for (int k = 0; k < n_neurons[n_layers - 2]; k++)
		{
			sum += layers[n_layers - 1].neurons[j].getPulse(k);
		}
		if (sum < 0)
			sum = 0;
		output[j] = sum;
	}

	return output;
}