#include "neuron.h"

#include <stdlib.h>
#include <stdio.h>

Neuron* createNeuron(int numNeuronsPrevLayer)
{
    Neuron *neuron = calloc(1, sizeof(Neuron));
    neuron->numInputs = numNeuronsPrevLayer;
    neuron->bias = 0.0;
    neuron->weights = calloc(numNeuronsPrevLayer, sizeof(double));
    return neuron;
}

void freeNeuronContents(Neuron *neuron)
{
    free(neuron->weights);
}

void updateWeightsAndBiasNeuron(Neuron *neuron, double *weights, double bias)
{
    for (int i = 0; i < neuron->numInputs; i++)
    {
        neuron->weights[i] = weights[i];
    }
    neuron->bias = bias;
}

double getNeuronOutput(const Neuron *neuron, double *inputs)
{
    double output = 0.0;
    for (int i = 0; i < neuron->numInputs; i++)
    {
        output += inputs[i] * neuron->weights[i];
    }
    output += neuron->bias;
    return output;
}
