#include "neuron.h"

#include <stdlib.h>

Neuron* createNeuron(int numNeuronsPrevLayer, double bias)
{
    Neuron *neuron = calloc(1, sizeof(Neuron));
    neuron->numInputs = numNeuronsPrevLayer;
    neuron->bias = bias;
    neuron->inputs = calloc(numNeuronsPrevLayer, sizeof(double));
    neuron->weights = calloc(numNeuronsPrevLayer, sizeof(double));
    return neuron;
}

void deleteNeuron(Neuron *neuron)
{
    free(neuron->inputs);
    free(neuron->weights);
}

void updateNeuron(Neuron *neuron, double *inputs, double *weights)
{
    for (int i = 0; i < neuron->numInputs; i++)
    {
        neuron->inputs[i] = inputs[i];
        neuron->weights[i] = weights[i];
    }
}

double getNeuronOutput(const Neuron *neuron)
{
    double output = 0.0;
    for (int i = 0; i < neuron->numInputs; i++)
    {
        output += neuron->inputs[i] * neuron->weights[i];
    }
    output += neuron->bias;
    return output;
}
