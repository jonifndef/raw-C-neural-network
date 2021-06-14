#include <stdlib.h>
#include <stdio.h> // debug

#include "layer.h"

static DynamicMatrix* getWeightsMatrix(const LayerDense *layer)
{
    if (layer->numNeurons < 1)
    {
        return NULL;
    }

    uint numRows = layer->numNeurons;
    uint numColumns = layer->neurons[0].numInputs;

    DynamicMatrix *weights = createDynamicMatrixWithCapacity(numRows, numColumns);
    if (!weights)
    {
        return NULL;
    }

    for (int i = 0; i < layer->numNeurons; i++)
    {
        DynamicArray *weightsRow = createDynamicArrWithCapacity(numColumns);
        if (!weightsRow)
        {
            return NULL;
        }

        for (int j = 0; j < layer->neurons[0].numInputs; j++)
        {
            if (!pushBackDynamicArr(weightsRow, layer->neurons[i].weights[j]))
            {
                return NULL;
            }
        }
        if (!pushRow(weights, weightsRow, DO_TAKE_OWNERSHIP))
        {
            return NULL;
        }
    }
    return weights;
}

static bool addBiasesToOutput(LayerDense *layer)
{
    for (int i = 0; i < layer->outputs->rows; i++)
    {
        for (int j = 0; j < layer->numNeurons; j++)
        {
            double element = layer->outputs->data[i]->data[j] + layer->neurons[j].bias;
            if (!setDynamicMatrixElement(layer->outputs, i, j, element))
            {
                return false;
            }
        }
    }
    return true;
}

LayerDense *createLayerDense(int numNeurons,
                             int batchSize,
                             int numNeuronsPrevLayerDense,
                             double (*activationFunction)(double))
{
    LayerDense *layer= calloc(1, sizeof(LayerDense));
    layer->numNeurons = numNeurons;
    layer->neurons = calloc(numNeurons, sizeof(Neuron));
    //layer->outputs = createMatrixDoubles(batchSize, numNeurons);
    layer->outputs = createDynamicMatrix();

    for (int i = 0; i < numNeurons; i++)
    {
        layer->neurons[i] = *(createNeuron(numNeuronsPrevLayerDense, activationFunction));
    }

    return layer;
}

void freeLayerDenseContents(LayerDense *layer)
{
    free(layer->neurons);
    freeDynamicMatrix(layer->outputs);
}

void updateWeightsAndBiasesInLayerDense(LayerDense *layer,
                                        const DynamicMatrix *weights,
                                        const double *biases)
{
    for (int i = 0; i < layer->numNeurons; i++)
    {
        updateWeightsAndBiasNeuron(&layer->neurons[i], getDynamicMatrixRowRef(weights, i), biases[i]);
    }
}

bool forwardDense(LayerDense* layer,
                  const DynamicMatrix *inputs)
{
    // The rows in the inputs matrix represent the batches
    // We want to calculate the the output of each neuron for each of the batches
    DynamicMatrix *weights = getWeightsMatrix(layer);
    if (!weights)
    {
        return false;
    }

    printf("printing weights matrix:\n");
    printDynamicMatrix(weights);

    layer->outputs = createDynamicMatrixTranspose(
            dotProductDynamicMatrix(weights, createDynamicMatrixTranspose(inputs))
    );

    if (!layer->outputs)
    {
        return false;
    }

    if (!addBiasesToOutput(layer))
    {
        return false;
    }

    return true;
}

DynamicMatrix* getOutputsFromLayerDense(const LayerDense* layer)
{
    return layer->outputs;
}
