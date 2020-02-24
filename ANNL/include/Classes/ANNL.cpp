#include <ANNL.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

#define M_E 2.718281828459045235360287

NeuralNetwork::NeuralNetwork(act_func _activationFunction, bool _backpropagation)
{
	n_layers = 0;
	n_neurons = NULL;
	layers = NULL;

	activationFunction = _activationFunction;
	backpropagationFlag = _backpropagation;
}

void NeuralNetwork::config(void)
{
	allocateWeights();

	if (backpropagationFlag)
	{
		if (activationFunction == BINARY_STEP)
		{
			std::cout << "[ERROR] The activation function 'BINARY_STEP' cannot be backpropagated!" << std::endl;
			exit(0);
		}
		else if (activationFunction == RELU)
		{
			std::cout << "[ERROR] The activation function 'RELU' cannot be backpropagated!" << std::endl;
			exit(0);
		}

		for (int i = 0; i < n_neurons[0]; i++)
			Pulse.push_back(0);

		for(int i = 0;i < n_neurons[n_layers - 1]; i++)
			Hypothesis.push_back(0);

		del_C_Weights = new float** [n_layers];
		del_C_Biases = new float* [n_layers];

		for (int i = 1; i < n_layers; i++)
		{
			layers[i].del_C = new float* [n_neurons[i]];
			del_C_Weights[i] = new float* [n_neurons[i]];
			for (int c = 0; c < n_neurons[i]; c++)
			{
				layers[i].del_C[c] = new float[n_neurons[i - 1]];
				del_C_Weights[i][c] = new float[n_neurons[i - 1]];
			}

			layers[i].gamma = new float[n_neurons[i]];
			del_C_Biases[i] = new float[n_neurons[i]];

			for (int j = 0; j < n_neurons[i]; j++)
			{
				for (int k = 0; k < n_neurons[i - 1]; k++)
				{
					layers[i].del_C[j][k] = 0;
					del_C_Weights[i][j][k] = 0;
				}
				layers[i].gamma[j] = 0;
				del_C_Biases[i][j] = 0;
			}
		}
	}
}

void NeuralNetwork::setLayers(int _nLayers)
{
	if (_nLayers < 2)
	{
		std::cout << "[ERROR] _nLayers must be greater than 1!" << std::endl;
		exit(0);
	}
	
	n_layers = _nLayers;
	n_neurons = new int[_nLayers];
	layers = new Layer[_nLayers];
}

void NeuralNetwork::allocateWeights(void)
{
	for (int i = 1; i < n_layers; i++)
	{
		layers[i].biases = new float[n_neurons[i]];

		layers[i].weights = new float* [n_neurons[i]];
		for (int j = 0; j < n_neurons[i]; j++)
			layers[i].weights[j] = new float[n_neurons[i - 1]];
	}
}

void NeuralNetwork::setNeurons(int _Layer, int _nNeurons)
{
	if (_Layer > n_layers - 1 || _Layer < 0)
	{
		std::cout << "[ERROR] Layer '" << _Layer << "' not found!" << std::endl;
		exit(0);
	}
	else if(_nNeurons < 0)
	{
		std::cout << "[ERROR] _nNeurons must be a positive number!" << std::endl;
		exit(0);
	}


	layers[_Layer].activations = new float[_nNeurons];
	n_neurons[_Layer] = _nNeurons;
}

void NeuralNetwork::setWeight(int _fromLayer, int _fromNeuron, int _toNeuron, float _Weight)
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

	layers[_fromLayer + 1].weights[_toNeuron][_fromNeuron] = _Weight;
}

void NeuralNetwork::setBias(int _Layer, int _Neuron, float _Bias)
{
	if (_Layer <= 0)
	{
		std::cout << "[ERROR] Layer '" << _Layer << "' must be greater than 0!" << std::endl;
		exit(0);
	}
	else if (_Neuron < 0 || _Neuron >= n_neurons[_Layer])
	{
		std::cout << "[ERROR] Neuron '" << _Neuron << "' not found on layer '" << _Layer << "'" << std::endl;
		exit(0);
	}

	layers[_Layer].biases[_Neuron] = _Bias;
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

int NeuralNetwork::getNLayers(void)
{
	return n_layers;
}

float NeuralNetwork::getWeight(int _fromLayer, int _fromNeuron, int _toNeuron)
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

	return layers[_fromLayer + 1].weights[_toNeuron][_fromNeuron];
}

float NeuralNetwork::getBias(int _Layer, int _Neuron)
{
	return layers[_Layer].biases[_Neuron];
}

float NeuralNetwork::getNeuronPulse(int _Layer, int _Neuron)
{
	return layers[_Layer].activations[_Neuron];
}

void NeuralNetwork::backpropagation(void)
{
	backprop_count++;

	int max = 0;
	for (int i = 0; i < n_layers; i++)
		if (n_neurons[i] > max)
			max = n_neurons[i];

	float** functionDerivative = new float* [n_layers];
	float** weightedSum = new float* [n_layers];
	for (int i = 0; i < n_layers; i++)
	{
		functionDerivative[i] = new float[max];
		weightedSum[i] = new float[max];
	}

	//----[WEIGHTED-SUM]----//
	for (int i = n_layers - 1; i > 0; i--)
	{
		for (int j = 0; j < n_neurons[i]; j++)
		{
			weightedSum[i][j] = 0;
			for (int k = 0; k < n_neurons[i - 1]; k++)
				weightedSum[i][j] += layers[i - 1].activations[k] * layers[i].weights[j][k];
			weightedSum[i][j] += layers[i].biases[j];
		}
	}

	//----[FUNCTIONS-DERIVATIVES]----//
	switch (activationFunction)
	{
	case LINEAR:
		for (int i = n_layers - 1; i > 0; i--)
			for (int j = 0; j < n_neurons[i]; j++)
				functionDerivative[i][j] = 1;
		break;
	case SIGMOID:
		for (int i = n_layers - 1; i > 0; i--)
			for (int j = 0; j < n_neurons[i]; j++)
				functionDerivative[i][j] = (1 / (1 + pow(M_E, -1 * weightedSum[i][j]))) * (1 - (1 / (1 + pow(M_E, -1 * weightedSum[i][j]))));
		break;
	case TANH:
		for (int i = n_layers - 1; i > 0; i--)
			for (int j = 0; j < n_neurons[i]; j++)
				functionDerivative[i][j] = 1 - pow(tanh(weightedSum[i][j]), 2);
		break;
	case GAUSSIAN:
		for (int i = n_layers - 1; i > 0; i--)
			for (int j = 0; j < n_neurons[i]; j++)
				functionDerivative[i][j] = -2 * weightedSum[i][j] * pow(M_E, -1 * pow(weightedSum[i][j], 2));
		break;
	case SINC:
		for (int i = n_layers - 1; i > 0; i--)
		{
			for (int j = 0; j < n_neurons[i]; j++)
			{
				if (weightedSum[i][j] == 0)
					functionDerivative[i][j] = 0;
				else
					functionDerivative[i][j] = (weightedSum[i][j] * cos(weightedSum[i][j]) - sin(weightedSum[i][j])) / pow(weightedSum[i][j], 2);
			}
		}
		break;
	case BENT_IDENTITY:
		for (int i = n_layers - 1; i > 0; i--)
			for (int j = 0; j < n_neurons[i]; j++)
				functionDerivative[i][j] = weightedSum[i][j] / (2 * sqrt(pow(weightedSum[i][j], 2) + 1)) + 1;
		break;
	case SOFTPLUS:
		for (int i = n_layers - 1; i > 0; i--)
			for (int j = 0; j < n_neurons[i]; j++)
				functionDerivative[i][j] = pow(M_E, weightedSum[i][j]) / (1 + pow(M_E, weightedSum[i][j]));
		break;
	case SOFTSIGN:
		for (int i = n_layers - 1; i > 0; i--)
			for (int j = 0; j < n_neurons[i]; j++)
				functionDerivative[i][j] = 1 / pow(1 + fabs(weightedSum[i][j]), 2);
		break;
	}

	//----[GAMMA-OUTPUT]----//
	for (int j = 0; j < n_neurons[n_layers - 1]; j++)
	{
		layers[n_layers - 1].gamma[j] = (layers[n_layers - 1].activations[j] - Hypothesis.at(j)) * functionDerivative[n_layers - 1][j];
		del_C_Biases[n_layers - 1][j] += layers[n_layers - 1].gamma[j];
	}

	//----[DEL_C-OUTPUT]----//
	for (int n = 0; n < n_neurons[n_layers - 1]; n++)
	{
		for (int m = 0; m < n_neurons[n_layers - 2]; m++)
		{
			layers[n_layers - 1].del_C[n][m] = layers[n_layers - 1].gamma[n] * layers[n_layers - 2].activations[m];
			del_C_Weights[n_layers - 1][n][m] += layers[n_layers - 1].del_C[n][m];
		}
	}

	for (int i = n_layers - 2; i > 0; i--)
	{
		//----[GAMMA-HIDDEN]----//
		for (int k = 0; k < n_neurons[i]; k++)
		{
			for (int j = 0; j < n_neurons[i + 1]; j++)
			{
				layers[i].gamma[k] += getWeight(i, k, j) * layers[i + 1].gamma[j];
			}

			layers[i].gamma[k] *= functionDerivative[i][k];
			del_C_Biases[i][k] += layers[i].gamma[k];
		}

		//----[DEL_C-HIDDEN]----//
		for (int k = 0; k < n_neurons[i]; k++)
		{
			for (int q = 0; q < n_neurons[i - 1]; q++)
			{
				layers[i].del_C[k][q] = layers[i].gamma[k] * layers[i - 1].activations[q];
				del_C_Weights[i][k][q] += layers[i].del_C[k][q];
			}
		}
	}
}

void NeuralNetwork::recalculateParameters(float _Epsilon)
{
	if (!backpropagationFlag)
	{
		std::cout << "[ERROR] 'backpropagationFlag' was set 'false'" << std::endl;
		exit(0);
	}

	float del_C_Module = 0;
	for (int i = n_layers - 1; i > 0; i--)
	{
		for (int j = 0; j < n_neurons[i]; j++)
		{
			for (int k = 0; k < n_neurons[i - 1]; k++)
			{
				del_C_Weights[i][j][k] /= backprop_count;
				del_C_Module += pow(del_C_Weights[i][j][k], 2);
			}
			del_C_Biases[i][j] /= backprop_count;
			del_C_Module += pow(del_C_Biases[i][j], 2);
		}
	}
	del_C_Module = sqrt(del_C_Module);
	backprop_count = 0;

	float n = _Epsilon / del_C_Module;

	for (int i = n_layers - 1; i > 0; i--)
	{
		for (int j = 0; j < n_neurons[i]; j++)
		{
			for (int k = 0; k < n_neurons[i - 1]; k++)
			{
				layers[i].weights[j][k] -= n * del_C_Weights[i][j][k];
			}
			layers[i].biases[j] -= n * del_C_Biases[i][j];
		}
	}

	for (int i = 1; i < n_layers; i++)
	{
		for (int j = 0; j < n_neurons[i]; j++)
		{
			for (int k = 0; k < n_neurons[i - 1]; k++)
			{
				layers[i].del_C[j][k] = 0;
				del_C_Weights[i][j][k] = 0;
			}
			layers[i].gamma[j] = 0;
			del_C_Biases[i][j] = 0;
		}
	}
}

void NeuralNetwork::save(const char _Path[])
{
	std::ofstream FILE;
	FILE.open(_Path);
	for (int i = 1; i < n_layers; i++)
		for (int j = 0; j < n_neurons[i]; j++)
			for (int k = 0; k < n_neurons[i - 1]; k++)
				FILE << layers[i].weights[j][k] << " ";

	for (int i = 1; i < n_layers; i++)
		for (int j = 0; j < n_neurons[i]; j++)
			FILE << layers[i].biases[j] << " ";
		
	FILE.close();
}

void NeuralNetwork::load(const char _Path[])
{
	std::ifstream FILE;
	float Parameter, Bias;
	int cLayer = 0, cNeuron = 0, tNeuron = 0;
	bool flagBias = false;
	FILE.open(_Path);
	while (FILE >> Parameter)
	{
		if (flagBias)
		{
			layers[cLayer].biases[cNeuron] = Parameter;

			if (cNeuron < n_neurons[cLayer] - 1)
			{
				cNeuron++;
			}
			else
			{
				cNeuron = 0;
				if (cLayer < n_layers - 1)
				{
					cLayer++;
				}
				else
				{
					break;
				}
			}

			continue;
		}

		if (cLayer <= n_layers - 2)
			layers[cLayer + 1].weights[tNeuron][cNeuron] = Parameter;

		if (tNeuron < n_neurons[cLayer + 1] - 1)
		{
			tNeuron++;
		}
		else
		{
			tNeuron = 0;
			if (cNeuron < n_neurons[cLayer] - 1)
			{
				cNeuron++;
			}
			else
			{
				cNeuron = 0;
				if (cLayer < n_layers - 2)
				{
					cLayer++;
				}
				else
				{
					flagBias = true; //Starts the Bias loading
					cLayer = 1;
					cNeuron = 0;

					continue;
				}
			}
		}
	}
	FILE.close();
}

float* NeuralNetwork::feedforward(void)
{
	//------[INPUT-LAYER]------//
	if (Pulse.empty())
	{
		std::cout << "[ERROR] Vector 'Pulse' is empty" << std::endl;
		exit(0);
	}
	else if (Pulse.size() < n_neurons[0])
	{
		std::cout << "[ERROR] Vector 'Pulse' has too few elements" << std::endl;
		exit(0);
	}
	else if (Pulse.size() > n_neurons[0])
	{
		std::cout << "[ERROR] Vector 'Pulse' has too many elements" << std::endl;
		exit(0);
	}

	for (int i = 0; i < Pulse.size(); i++)
		layers[0].activations[i] = Pulse.at(i);
	//-------------------------//

	for (int i = 1; i < n_layers; i++) // i -> Current layer
	{
		for (int j = 0; j < n_neurons[i]; j++) // j -> Current neuron
		{
			layers[i].activations[j] = 0;
			for (int k = 0; k < n_neurons[i - 1]; k++)
				layers[i].activations[j] += layers[i].weights[j][k] * layers[i - 1].activations[k];
			layers[i].activations[j] += layers[i].biases[j];

			//------[ACTIVATION FUNCTIONS]------//
			switch (activationFunction)
			{
			case LINEAR:
				break;
			case BINARY_STEP:
				if (layers[i].activations[j] < 0)
					layers[i].activations[j] = 0;
				else
					layers[i].activations[j] = 1;
				break;
			case SIGMOID:
				layers[i].activations[j] = 1 / (1 + pow(M_E, -1 * layers[i].activations[j]));
				break;
			case TANH:
				layers[i].activations[j] = tanh(layers[i].activations[j]);
				break;
			case RELU:
				if (layers[i].activations[j] <= 0)
					layers[i].activations[j] = 0;
				break;
			case GAUSSIAN:
				layers[i].activations[j] = pow(M_E, -1 * pow(layers[i].activations[j], 2));
				break;
			case SINC:
				if (layers[i].activations[j] == 0)
					layers[i].activations[j] = 1;
				else
					layers[i].activations[j] = sin(layers[i].activations[j]) / layers[i].activations[j];
				break;
			case BENT_IDENTITY:
				layers[i].activations[j] = (sqrt(pow(layers[i].activations[j], 2) + 1) - 1) / 2 + layers[i].activations[j];
				break;
			case SOFTPLUS:
				layers[i].activations[j] = log(1 + pow(M_E, layers[i].activations[j]));
				break;
			case SOFTSIGN:
				layers[i].activations[j] = layers[i].activations[j] / (1 + fabs(layers[i].activations[j]));
				break;
			}
		}
	}

	if (backpropagationFlag)
	{
		if (Hypothesis.empty())
		{
			std::cout << "[ERROR] Vector 'Hypothesis' is empty" << std::endl;
			exit(0);
		}
		else if (Hypothesis.size() < n_neurons[n_layers - 1])
		{
			std::cout << "[ERROR] Vector 'Hypothesis' has too few elements" << std::endl;
			exit(0);
		}
		else if (Hypothesis.size() > n_neurons[n_layers - 1])
		{
			std::cout << "[ERROR] Vector 'Hypothesis' has too many elements" << std::endl;
			exit(0);
		}

		backpropagation();
	}

	return layers[n_layers - 1].activations;
}