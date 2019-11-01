#ifndef NEURON_H
#define NEURON_H

#include <iostream>

class Neuron
{
private:
	
	int neuronsBehind;
	int neuronsForward;
	float* pulses;
	int* weights;
public:
	Neuron();

	float getPulse(int _Id);

	float* multiplyWeights(float _Pulse);

	void setWeight(int _Id, int _Weight);

	int getWeight(int _Id);

	void setNeuronsAround(int _nBehind, int _nForward);

	void allocateWeight();

	void allocatePulses();

	void resetPulse(int _Neuron);

	void recievePulse(int _Neuron, float _Pulse);
};

#endif
