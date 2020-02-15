#ifndef NEURON_H
#define NEURON_H

#include <iostream>

class Neuron
{
private:
	
	int neuronsBehind;
	int neuronsForward;
	float* pulses; //Stores the all the weighted pulses from the layer behind
	float* weights;
	float Bias;
public:
	float myPulse;

	Neuron();

	float getPulse(int _Id);

	float* multiplyWeights(float _Pulse);

	void setWeight(int _Id, float _Weight);

	void setBias(float _Bias);

	float getWeight(int _Id);

	float getBias();

	void setNeuronsAround(int _nBehind, int _nForward);

	void allocateWeight();

	void allocatePulses();

	void resetPulse(int _Neuron);

	void recievePulse(int _Neuron, float _Pulse);
};

#endif
