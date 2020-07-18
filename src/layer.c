#include <stdlib.h>
#include <time.h>
#include <stdio.h> // debug

#include "layer.h"

Layer *createLayer(int numNeurons, int numNeuronsPrevLayer)
{
    srand(time(0));

    Layer *layer = calloc(1, sizeof(Layer));
    layer->numNeurons = numNeurons;
    layer->neurons = calloc(numNeurons, sizeof(Neuron));

    for (int i = 0; i < numNeurons; i++)
    {
        layer->neurons[i] = *(createNeuron(numNeuronsPrevLayer));
    }

    // weights should idealy be initialized with a value between -1.0 and 1.0
    for (int k = 0; k < 10; k++)
    {
        double randNum = rand() % 200 - 100;
        randNum /= 100;
        printf("random num: %.2f\n", randNum);
    }

    // biases should idealy be initialized with 0, but if the network is "dead", try 1 or similar

    return layer;
}

void freeLayerContents(Layer *layer)
{
    free(layer->neurons);
}

void updateWeightsAndBiasesInLayer(Layer *layer, MatrixDoubles *weights, double *biases)
{
    for (int i = 0; i < layer->numNeurons; i++)
    {
        updateWeightsAndBiasNeuron(&layer->neurons[i], getMatrixDoublesRow(weights, i), biases[i]);
    }
}

// Memory leak here, how to allocate memory for output in main function?
MatrixDoubles* getOutputsFromLayer(Layer* layer, MatrixDoubles *inputs)
{
    MatrixDoubles *outputMatrix = createMatrixDoubles(inputs->rows, layer->numNeurons);
    for (int i = 0; i < inputs->rows; i++)
    {
        double *outputs = calloc(layer->numNeurons, sizeof(double));
        for (int j = 0; j < layer->numNeurons; j++)
        {
            outputs[j] = getNeuronOutput(&layer->neurons[j], getMatrixDoublesRow(inputs, i));
        }
        setMatrixDoublesRow(outputMatrix, i, outputs);
        free(outputs);
    }
    return outputMatrix;
}
