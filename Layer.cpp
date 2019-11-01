#include <Layer.h>

Layer::Layer()
{
	n_neurons = 0;
	neurons = NULL;
}

void Layer::setNeurons(int _Neurons)
{
	neurons = new Neuron[_Neurons];
}