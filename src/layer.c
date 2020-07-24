#include <stdlib.h>
#include <stdio.h> // debug

#include "layer.h"

LayerDense *createLayerDense(int numNeurons, int batchSize, int numNeuronsPrevLayerDense)
{
    LayerDense *layer= calloc(1, sizeof(LayerDense));
    layer->numNeurons = numNeurons;
    layer->neurons = calloc(numNeurons, sizeof(Neuron));
    layer->outputs = createMatrixDoubles(batchSize, numNeurons);

    for (int i = 0; i < numNeurons; i++)
    {
        layer->neurons[i] = *(createNeuron(numNeuronsPrevLayerDense));
    }

    return layer;
}

void freeLayerDenseContents(LayerDense *layer)
{
    free(layer->neurons);
    free(layer->outputs);
}

void updateWeightsAndBiasesInLayerDense(LayerDense *layer, MatrixDoubles *weights, double *biases)
{
    for (int i = 0; i < layer->numNeurons; i++)
    {
        updateWeightsAndBiasNeuron(&layer->neurons[i], getMatrixDoublesRow(weights, i), biases[i]);
    }
}

void forwardDense(LayerDense* layer, MatrixDoubles *inputs)
{
    // The rows in this instance represent the batches
    // We want to calculate the the output of each neuron for each of the batches
    for (int i = 0; i < inputs->rows; i++)
    {
        for (int j = 0; j < layer->numNeurons; j++)
        {
            layer->outputs->data[i][j] = getNeuronOutput(&layer->neurons[j], getMatrixDoublesRow(inputs, i));
        }
    }
}

MatrixDoubles* getOutputsFromLayerDense(LayerDense* layer)
{
    return layer->outputs;
}
