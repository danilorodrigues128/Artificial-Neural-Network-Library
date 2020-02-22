# Artificial Neural Network Library

## Description
The Artificial Neural Network Library (ANNL) is a C++ project aimed to help on the development of Artificial Intelligence Algorithms. Its flexibility allows the developer to create Neural Networks with any number of layers, add different numbers of neurons at each one, set the weights and biases of the connections and manipulate the output of the algorithm as a simple array.

## Installation
- Download the library

- Copy the "include" folder to your project directory

- Include all the downloaded files in your project

- Add to the top of your 'main.cpp' file:
```
#include <include/ANNL.h>
```

## Contributing
Danilo O. Rodrigues: github.com/danilorodrigues128

## License
This code is licensed under MIT License

## Contact
- Instagram: @danilorodrigues128

# Reference

## Backpropagation
```
void backpropagation(float _Hypothesis[])
```

**Description**  
- Calculate the gradient of the Cost Function according to the last feedforwarded sample.  
**NOTE:** If your project requires the Backpropagation Algorithm, you must call the function _backpropagation()_ after every _feedforward()_ method.

**Parameters**  
- *float Hypothesis[]*: An one dimensional array containing the expected output for the Neural Network.

## Config
```
void config(void)
```

**Description**  
- Configure arrays used during feedforward and backpropagation.  
**NOTE:** _config()_ must be called after _setNeurons()_.

## Feedforward
```
float* feedforward(void)
```

**Description**  
- Propagate the pulses through the Network.  
**NOTE:** _feedforward()_ must be called after using the _sendPulse()_ method at every input neuron.

**Return**  
- An one dimensional array containing the activations of the output neurons.

## GetBias
```
float getBias(int _Layer, int _Neuron)
```

**Description**  
- Returns the bias of a specifc neuron.

**Parameters**  
- *int \_Layer*: The layer of the neuron  
- *int \_Neuron*: The neuron

**Return**  
- A float containing the bias of the neuron.
