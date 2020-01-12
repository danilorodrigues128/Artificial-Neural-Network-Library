#include <ANNL.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

#define M_E 2.718281828459045235360287

NeuralNetwork::NeuralNetwork(act_func _activationFunction)
{
	n_layers = 0;
	n_neurons = NULL;
	layers = NULL;
	
	activationFunction = _activationFunction;
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

	layers[_Layer].setNeurons(_nNeurons);
	n_neurons[_Layer] = _nNeurons;
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

	layers[_fromLayer].neurons[_fromNeuron].setWeight(_toNeuron, _Weight);
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

	layers[_Layer].neurons[_Neuron].setBias(_Bias);
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

float NeuralNetwork::getBias(int _Layer, int _Neuron)
{
	return layers[_Layer].neurons[_Neuron].getBias();
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

void NeuralNetwork::save(const char _Path[])
{
	std::ofstream FILE;
	FILE.open(_Path);
	for (int i = 0; i < n_layers - 1; i++)
		for (int j = 0; j < n_neurons[i]; j++)
			for (int k = 0; k < n_neurons[i + 1]; k++)
				FILE << getWeight(i, j, k) << " ";

	for (int i = 1; i < n_layers; i++)
		for (int j = 0; j < n_neurons[i]; j++)
			FILE << layers[i].neurons[j].getBias() << " ";
		
	FILE.close();
}

void NeuralNetwork::load(const char _Path[])
{
	std::ifstream FILE;
	int Parameter, Bias, cLayer = 0, cNeuron = 0, tNeuron = 0;
	bool flagBias = false;
	FILE.open(_Path);
	while (FILE >> Parameter)
	{
		if (flagBias)
		{
			layers[cLayer].neurons[cNeuron].setBias(Parameter);

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
			setWeight(cLayer, cNeuron, tNeuron, Parameter);

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

float* NeuralNetwork::outputNeurons()
{
	double sum = 0;
	float* output = NULL;

	if (n_neurons[n_layers - 1] > 0)
		output = new float[n_neurons[n_layers - 1]];

	//--------------------[HIDDEN LAYERS]--------------------//
	for (int i = 1; i < n_layers - 1; i++) // i -> Current layer
	{
		for (int j = 0; j < n_neurons[i]; j++) // j -> Current neuron
		{
			sum = 0;
			for (int k = 0; k < n_neurons[i - 1]; k++) // k -> Neuron behind
			{
				sum += layers[i].neurons[j].getPulse(k); // Sums all the weighted pulses from the layer behind
			}
			
			sum += layers[i].neurons[j].getBias(); // Sums the neuron bias

			//------[ACTIVATION FUNCTIONS]------//
			switch (activationFunction)
			{
			case LINEAR:
				break;
			case BINARY_STEP:
				if (sum < 0)
					sum = 0;
				else
					sum = 1;
				break;
			case SIGMOID:
				sum = 1 / (1 + pow(M_E, -1 * sum));
				break;
			case TANH:
				sum = tanh(sum);
				break;
			case RELU:
				if (sum <= 0)
					sum = 0;
				break;
			case GAUSSIAN:
				sum = pow(M_E, -1 * pow(sum, 2));
				break;
			case SINC:
				if (sum == 0)
					sum = 1;
				else
					sum = sin(sum) / sum;
				break;
			case BENT_IDENTITY:
				sum = (sqrt(pow(sum, 2) + 1) - 1) / 2 + sum;
				break;
			case SOFTPLUS:
				sum = log(1 + pow(M_E, sum));
				break;
			case SOFTSIGN:
				sum = sum / (1 + fabs(sum));
				break;
			}
			//----------------------------------//

			for (int k = 0; k < n_neurons[i + 1]; k++) // k -> Neuron forward
			{
				layers[i + 1].neurons[k].resetPulse(j);
				layers[i + 1].neurons[k].recievePulse(j, sum * layers[i].neurons[j].getWeight(k)); // Sends the weighted pulse to the forward neurons
			}
		}
	}
	//-------------------------------------------------------//

	//--------------------[OUTPUT LAYER]--------------------//
	for (int j = 0; j < n_neurons[n_layers - 1]; j++)
	{
		sum = 0;
		for (int k = 0; k < n_neurons[n_layers - 2]; k++)
		{
			sum += layers[n_layers - 1].neurons[j].getPulse(k);
		}

		sum += layers[n_layers - 1].neurons[j].getBias();

		//------[ACTIVATION FUNCTIONS]------//
		switch (activationFunction)
		{
		case LINEAR:
			break;
		case BINARY_STEP:
			if (sum < 0)
				sum = 0;
			else
				sum = 1;
			break;
		case SIGMOID:
			sum = 1 / (1 + pow(M_E, -1 * sum));
			break;
		case TANH:
			sum = tanh(sum);
			break;
		case RELU:
			if (sum <= 0)
				sum = 0;
			break;
		case GAUSSIAN:
			sum = pow(M_E, -1 * pow(sum, 2));
			break;
		case SINC:
			if (sum == 0)
				sum = 1;
			else
				sum = sin(sum) / sum;
			break;
		case BENT_IDENTITY:
			sum = (sqrt(pow(sum, 2) + 1) - 1) / 2 + sum;
			break;
		case SOFTPLUS:
			sum = log(1 + pow(M_E, sum));
			break;
		case SOFTSIGN:
			sum = sum / (1 + fabs(sum));
			break;
		}
		//----------------------------------//

		output[j] = sum;
	}
	//------------------------------------------------------//

	return output;
}