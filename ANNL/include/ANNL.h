#ifndef ANNL_H
#define ANNL_H

#include <Layer.h>
#include <vector>

class NeuralNetwork
{
public:
	std::vector<float> Hypothesis;
	std::vector<float> Pulse;

	enum act_func { LINEAR, BINARY_STEP, SIGMOID, TANH, RELU, GAUSSIAN, SINC, BENT_IDENTITY, SOFTPLUS, SOFTSIGN };

	NeuralNetwork(act_func _activationFunction, bool _backpropagation = false);

	void config(void);

	void setLayers(int _nLayers);

	void setNeurons(int _Layer, int _nNeurons);

	void setWeight(int _fromLayer, int _fromNeuron, int _toNeuron, float _Weight);

	void setBias(int _Layer, int _Neuron, float _Bias);

	int getNNeurons(int _Layer);

	int getNLayers(void);

	float getWeight(int _fromLayer, int _fromNeuron, int _toNeuron);

	float getBias(int _Layer, int _Neuron);

	float getNeuronPulse(int _Layer, int _Neuron);

	void recalculateParameters(float _Epsilon);

	void save(const char _Path[]);

	void load(const char _Path[]);

	float* feedforward(void);

private:
	int n_layers;
	int* n_neurons;

	bool backpropagationFlag;
	int backprop_count = 0;
	float*** del_C_Weights;
	float** del_C_Biases;

	Layer* layers;
	act_func activationFunction;

	void allocateWeights(void);
	void backpropagation(void);
};

#endif