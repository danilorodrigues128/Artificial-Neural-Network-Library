#ifndef LAYER_H
#define LAYER_H

#include <Neuron.h>

class Layer
{
private:
	int n_neurons;
public:
	Neuron* neurons;

	Layer();

	void setNeurons(int _Neurons);
};

#endif;