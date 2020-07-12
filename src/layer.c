#include <stdlib.h>

#include "layer.h"

Layer *createLayer(int numNeurons, int numNeuronsPrevLayer)
{
    Layer *layer = calloc(1, sizeof(Layer));
    layer->numNeurons = numNeurons;
    layer->neurons = calloc(numNeurons, sizeof(Neuron));

    for (int i = 0; i < numNeurons; i++)
    {
        layer->neurons[i] = *(createNeuron(numNeuronsPrevLayer));
    }

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

    //for (int i = 0; i < layer->numNeurons; i++)
    //{
    //    layer->outputs[i] = getNeuronOutput(&layer->neurons[i], inputs);
    //}
    //return layer->outputs;
}
