#ifndef LAYER_H
#define LAYER_H

#include <Neuron.h>

class Layer
{
private:
	int n_neurons;
public:
	Neuron* neurons;
	float** del_C;
	float* gamma;

	Layer();

	void setNeurons(int _Neurons);
};

#endif;