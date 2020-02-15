#ifndef ANNL_H
#define ANNL_H

#include <Layer.h>

class NeuralNetwork
{
public:
	float*** del_C_Weights;
	float** del_C_Biases;
	Layer* layers;

	enum act_func { LINEAR, BINARY_STEP, SIGMOID, TANH, RELU, GAUSSIAN, SINC, BENT_IDENTITY, SOFTPLUS, SOFTSIGN };

	NeuralNetwork(act_func _activationFunction, bool _backpropagation = false);

	void config();

	void setLayers(int _Layers);

	void setNeurons(int _Layer, int _nNeuron);

	void setWeight(int _fromLayer, int _fromNeuron, int _toNeuron, float _Weight);

	void setBias(int _Layer, int _Neuron, float _Bias);

	int getNNeurons(int _Layer);

	int getNLayers();

	float getWeight(int _fromLayer, int _fromNeuron, int _toNeuron);

	float getBias(int _Layer, int _Neuron);

	float getNeuronPulse(int _Layer, int _Neuron);

	void sendPulse(int _fromNeuron, float _Pulse);
	
	void backpropagation(float _Hypothesis[]);

	void recalculateParameters(float _Epsilon);

	void save(const char _Path[]);

	void load(const char _Path[]);

	float* outputNeurons();

private:
	int n_layers;
	int* n_neurons;

	bool backprop;
	int backprop_count = 0;

	act_func activationFunction;

	void setSynapses();
	void allocateWeights();
	void allocatePulses();
};

#endif