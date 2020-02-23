# Artificial Neural Network Library
## Summary
- [Description](#description)
- [Installation](#installation)
- [Reference](#reference)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Description
The Artificial Neural Network Library (ANNL) is a C++ project aimed to help on the development of Artificial Intelligence Algorithms. Its flexibility allows the developer to create Neural Networks with any number of layers, add different numbers of neurons at each one, set the weights and biases of the connections and manipulate the output of the algorithm as a simple array.

## Installation
- Download the library

- Copy the ['include'](ANNL) folder to your project directory

- Include all the downloaded files in your project

- Add to the top of your 'main.cpp' file:
```cpp
#include <include/ANNL.h>
```

# Reference
## Classes
### NeuralNetwork
```cpp
NeuralNetwork(act_func _activationFunction, bool _backpropagation = false)
```

**Description**  
- Creates a Neural Network.

**Parameters**  
- *act_func _activationFunction*: The activation function of the Network.  
   - **VALUES:** `{LINEAR, BINARY_STEP, SIGMOID, TANH, RELU, GAUSSIAN, SINC, BENT_IDENTITY, SOFTPLUS, SOFTSIGN}`.
- *bool _backpropagation*: Controls whether the Backpropagation Algorithm is going to be used or not (**DEFAULT:** *false*)

**Example**
```cpp
NeuralNetwork Net(NeuralNetwork::SIGMOID, true);
```

## Methods

### Backpropagation
```cpp
void backpropagation(float _Hypothesis[])
```

**Description**  
- Calculate the gradient of the Cost Function according to the last feedforwarded sample.  
**NOTE:** The _feedforward()_ method must be called before _backpropagation()_.

**Parameters**  
- *float Hypothesis[]*: An one dimensional array containing the expected output for the Neural Network.

### Config
```cpp
void config(void)
```

**Description**  
- Configure arrays used during feedforward and backpropagation.  
**NOTE:** _config()_ must be called after using the _setNeurons()_ method at every layer of the Network.

### Feedforward
```cpp
float* feedforward(void)
```

**Description**  
- Propagate the pulses through the Network.  
**NOTE:** The _sendPulse()_ method must be used at every input neuron before calling _feedforward()_.

**Return**  
- An one dimensional array containing the pulses of the output neurons.

### GetBias
```cpp
float getBias(int _Layer, int _Neuron)
```

**Description**  
- Returns the bias of a specifc neuron.

**Parameters**  
- *int \_Layer*: The layer of the neuron.
- *int \_Neuron*: The neuron.

**Return**  
- A float containing the bias of the neuron.

### GetNeuronPulse
```cpp
float getNeuronPulse(int _Layer, int _Neuron)
```

**Description**  
- Returns the pulse of a specific neuron on a specific layer of the Neural Network.

**Parameters**  
- *int \_Layer*: The layer of the neuron.
- *int \_Neuron*: The neuron.

**Return**  
- A float containing the pulse of the neuron.

### GetNLayers
```cpp
int getNLayers(void)
```

**Description**  
- Returns the number of layer on the Neural Network.

**Return**  
- An integer containing the number of layer on the Network.

### GetNNeurons
```cpp
int getNNeurons(int _Layer)
```

**Description**  
- Returns the number of neurons on a specific layer.

**Parameters**  
- *int \_Layer*: The layer.

**Return**  
- An integer containing the number of neurons on the layer.

### GetWeight
```cpp
float getWeight(int _fromLayer, int _fromNeuron, int _toNeuron)
```

**Description**  
- Returns the weight of the connection between two neurons.

**Parameters**  
- *int \_fromLayer*: The layer of the starting neuron.
- *int \_fromNeuron*: The starting neuron.
- *int \_toNeuron*: The ending neuron.

**Return**  
- A float containing the weight of the connection.

### Load
```cpp
void load(const char _Path[])
```

**Description**  
- Loads the weights and biases saved as a file.

**Parameters**  
- *const char \_Path[]*: The path of the file.

### RecalculateParameters
```cpp
void recalculateParameters(float _Epsilon)
```

**Description**  
- Calculate the new weights and biases according to the average gradient of the Cost Function.  
**NOTE:** The _backpropagation()_ method must be called before _recalculateParameters()_.

**Parameters**  
- *float \_Epsilon*: The learning rate.

### Save
```cpp
void save(const char _Path[])
```

**Description**  
- Saves the weights and biases as a file.

**Parameters**  
- *const char \_Path[]*: The path of the file.

### SendPulse
```cpp
void sendPulse(int _fromNeuron, float _Pulse)
```

**Description**  
- Sends a pulse from a specific input neuron.

**Parameters**  
- *int \_fromNeuron*: The input neuron.
- *float \_Pulse*: The pulse.

### SetBias
```cpp
void setBias(int _Layer, int _Neuron, float _Bias)
```

**Description**  
- Sets the bias of a specific neuron on a specific layer.

**Parameters**  
- *int \_Layer*: The layer of the neuron.
- *int \_Neuron*: The neuron.
- *float \_Bias*: The bias.

### SetLayers
```cpp
void setLayers(int _nLayers)
```

**Description**  
- Sets the number of layers on the Neural Network.

**Parameters**  
- *int \_nLayers*: The number of layers on the Network.

### SetNeurons
```cpp
void setNeurons(int _Layer, int _nNeurons)
```

**Description**  
- Sets the number of neurons on a specific layer.

**Parameters**  
- *int \_Layer*: The layer.
- *int \_nNeurons*: The number of neurons on the layer.

### SetWeight
```cpp
void setWeight(int _fromLayer, int _fromNeuron, int _toNeuron, float _Weight)
```

**Description**  
- Sets the weight of a connection between two neurons.

**Parameters**  
- *int \_fromLayer*: The layer of the starting neuron.
- *int \_fromNeuron*: The starting neuron.
- *int \_toNeuron*: The ending neuron.
- *float \_Weight*: The weight.

## Contributing
- Danilo O. Rodrigues: [github.com/danilorodrigues128](https://github.com/danilorodrigues128)

## License
This code is licensed under [MIT License](https://github.com/angular/angular.js/blob/master/LICENSE)

## Contact
- Instagram: [@danilorodrigues128](https://www.instagram.com/danilorodrigues128/)
