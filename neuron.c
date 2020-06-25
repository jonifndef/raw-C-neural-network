#include "neuron.h"

#include <stdlib.h>

Neuron* createNeuron(int numNeuronsPrevLayer)
{
    Neuron *neuron = calloc(1, sizeof(Neuron));
    neuron->numInputs = numNeuronsPrevLayer;
    neuron->bias = 0.0;
    neuron->inputs = calloc(numNeuronsPrevLayer, sizeof(double));
    neuron->weights = calloc(numNeuronsPrevLayer, sizeof(double));
    return neuron;
}

void freeNeuronContents(Neuron *neuron)
{
    free(neuron->inputs);
    free(neuron->weights);
}

void updateNeuron(Neuron *neuron, double *inputs, double *weights, double bias)
{
    for (int i = 0; i < neuron->numInputs; i++)
    {
        neuron->inputs[i] = inputs[i];
        neuron->weights[i] = weights[i];
    }
    neuron->bias = bias;
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
