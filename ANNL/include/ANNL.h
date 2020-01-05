#ifndef ANNL_H
#define ANNL_H

#include <Layer.h>

class NeuralNetwork
{
private:
	int n_layers;
	int* n_neurons;
	bool ignoreNegatives;
	Layer* layers;

	void setSynapses();
	void allocateWeights();
	void allocatePulses();
public:
	NeuralNetwork(bool _ignoreNegatives = false);

	void config();

	void setLayers(int _Layers);

	void setNeurons(int _Layer, int _nNeuron);

	void setWeight(int _fromLayer, int _fromNeuron, int _toNeuron, int _Weight);

	void setBias(int _Layer, int _Neuron, float _Bias);

	int getNNeurons(int _Layer);

	int getNLayers();

	int getWeight(int _fromLayer, int _fromNeuron, int _toNeuron);

	void sendPulse(int _fromNeuron, float _Pulse);

	void save(const char _Path[]);

	void load(char* _Path);

	float* outputNeurons();
};

#endif