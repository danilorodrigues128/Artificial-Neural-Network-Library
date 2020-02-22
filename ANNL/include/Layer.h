#ifndef LAYER_H
#define LAYER_H

class Layer
{
public:
	float** del_C;
	float* gamma;

	float** weights;
	float* biases;
	float* activations;

	Layer();
};

#endif;