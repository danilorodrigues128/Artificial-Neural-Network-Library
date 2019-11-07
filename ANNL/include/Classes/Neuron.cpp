#include <Neuron.h>

Neuron::Neuron()
{
	neuronsBehind = 0;
	neuronsForward = 0;
	pulses = NULL;
	weights = NULL;
}

float Neuron::getPulse(int _Id)
{
	return pulses[_Id];
}

float* Neuron::multiplyWeights(float _Pulse)
{
	float* mult = NULL;
	if(neuronsForward > 0)
		mult = new float[neuronsForward];
	for (int i = 0; i < neuronsForward; i++)
		mult[i] = weights[i] * _Pulse;

	return mult;
}

void Neuron::setWeight(int _Id, int _Weight)
{
	if(_Id >= 0 && _Id < neuronsForward)
		weights[_Id] = _Weight;
}

int Neuron::getWeight(int _Id)
{
	return weights[_Id];
}

void Neuron::setNeuronsAround(int _nBehind, int _nForward)
{
	neuronsBehind = _nBehind;
	neuronsForward = _nForward;
}

void Neuron::allocateWeight()
{
	if(neuronsForward > 0)
		weights = new int[neuronsForward];
}

void Neuron::allocatePulses()
{
	pulses = new float[neuronsBehind];
}

void Neuron::resetPulse(int _Neuron)
{
	pulses[_Neuron] = 0;
}

void Neuron::recievePulse(int _Neuron, float _Pulse)
{
	if (_Neuron >= 0)
		pulses[_Neuron] = _Pulse;
}