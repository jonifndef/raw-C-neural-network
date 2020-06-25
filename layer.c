#include <stdlib.h>

#include "layer.h"

Layer *createLayer(int numNeurons, int numNeuronsPrevLayer)
{
    Layer *layer = calloc(1, sizeof(Layer));
    layer->numNeurons = numNeurons;
    layer->neurons = calloc(numNeurons, sizeof(Neuron));
    layer->outputs = calloc(numNeurons, sizeof(double));

    for (int i = 0; i < numNeurons; i++)
    {
        layer->neurons[i] = *(createNeuron(numNeuronsPrevLayer));
    }


    return layer;
}

void freeLayerContents(Layer *layer)
{
    free(layer->neurons);
    free(layer->outputs);
}

void updateNeuronsInLayer(Layer *layer, double *inputs, double weights[3][4], double *biases)
{
    for (int i = 0; i < layer->numNeurons; i++)
    {
        updateNeuron(&layer->neurons[i], inputs, weights[i], biases[i]);
    }
}

double* getLayerOutput(Layer* layer)
{
    for (int i = 0; i < layer->numNeurons; i++)
    {
        layer->outputs[i] = getNeuronOutput(&layer->neurons[i]);
    }
    return layer->outputs;
}
