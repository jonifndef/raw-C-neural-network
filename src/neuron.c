#include "neuron.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Neuron* createNeuron(int numNeuronsPrevLayer, double(*activationFunction)(double))
{
    Neuron *neuron = calloc(1, sizeof(Neuron));
    neuron->numInputs = numNeuronsPrevLayer;
    neuron->activationFunction = activationFunction;

    // biases should idealy be initialized with 0, but if the network is "dead", try 1 or similar
    neuron->bias = 0.0;
    neuron->weights = calloc(numNeuronsPrevLayer, sizeof(double));

    // weights should idealy be initialized with a value between -1.0 and 1.0
    for (int i = 0; i < numNeuronsPrevLayer; i++)
    {
        double randNum = rand() % 201 - 100;
        randNum /= 100;
        neuron->weights[i] = randNum;
    }

    return neuron;
}

void freeNeuronContents(Neuron *neuron)
{
    free(neuron->weights);
}

void updateWeightsAndBiasNeuron(Neuron *neuron, DynamicArray *weights, double bias)
{
    for (int i = 0; i < neuron->numInputs; i++)
    {
        neuron->weights[i] = getDynamicArrElement(weights, i);
    }
    neuron->bias = bias;
}

double getNeuronOutput(const Neuron *neuron, DynamicArray *inputs)
{
    double output = 0.0;
    for (int i = 0; i < neuron->numInputs; i++)
    {
        output += getDynamicArrElement(inputs, i) * neuron->weights[i];
    }
    output += neuron->bias;

    return neuron->activationFunction(output);
}
