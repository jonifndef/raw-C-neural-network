#include <stdlib.h>
#include <stdio.h> // debug
#include <time.h>

#include "layer.h"

static bool srandRun = false;

static bool initializeWeights(LayerDense *layer,
                              const uint numInputs,
                              const uint numNeurons)
{
    for (int i = 0; i < layer->weights->rowCapacity; i++)
    {
        DynamicArray *row = createDynamicArrWithCapacity(layer->weights->columnCapacity);
        if (!row)
        {
            return false;
        }

        for (int j = 0; j < layer->weights->columnCapacity; j++)
        {
            double randNum = rand() % 201 - 100;
            randNum /= 100;
            if (!pushBackDynamicArr(row, randNum))
            {
                return false;
            }
        }

        if (!pushRow(layer->weights, row, DO_TAKE_OWNERSHIP))
        {
            return false;
        }
    }

    return true;
}

static bool addBiasesToOutput(DynamicMatrix *output, const double *biases)
{
    for (int i = 0; i < output->rows; i++)
    {
        for (int j = 0; j < output->columns; j++)
        {
            double element = getDynamicMatrixElement(output, i, j) + biases[j];
            if (!setDynamicMatrixElement(output, i, j, element))
            {
                return false;
            }
        }
    }

    return true;
}

static bool pushIntoOutputs(DynamicMatrix *layerOutputs,
                            const DynamicMatrix *source)
{
    for (int i = 0; i < source->rows; i++)
    {
        if (!pushRow(layerOutputs, getDynamicMatrixRowCopy(source, i), DO_TAKE_OWNERSHIP))
        {
            return false;
        }
    }

    return true;
}

LayerDense *createLayerDense(uint numNeurons,
                             uint batchSize,
                             uint numInputs,
                             bool (*activationFunction)(DynamicMatrix*))
{
    // Only run srand once, the first time we create a layer
    if (!srandRun)
    {
        srand(time(0));
        srandRun = true;
    }

    LayerDense *layer= calloc(1, sizeof(LayerDense));
    if (!layer)
    {
        return NULL;
    }

    layer->numNeurons = numNeurons;
    // biases should be initialized as 0, which calloc does
    layer->biases = calloc(numNeurons, sizeof(double));
    if (!layer->biases)
    {
        return NULL;
    }

    layer->weights = createDynamicMatrixWithCapacity(numInputs, numNeurons);
    if (!layer->weights)
    {
        return NULL;
    }

    if (!initializeWeights(layer, numInputs, numNeurons))
    {
        return NULL;
    }

    layer->outputs = createDynamicMatrixWithCapacity(batchSize, numNeurons);
    if (!layer->outputs)
    {
        return NULL;
    }

    layer->activationFunction = activationFunction;

    return layer;
}

void freeLayerDenseContents(LayerDense *layer)
{
    freeDynamicMatrix(layer->weights);
    freeDynamicMatrix(layer->outputs);
    free(layer->biases);
    free(layer);
}

bool updateWeightsAndBiasesInLayerDense(LayerDense *layer,
                                        const DynamicMatrix *weights,
                                        const double *biases)
{
    // Should this function take ownership of the weights and biases parameters?
    if (!copyDynamicMatrix(layer->weights, weights))
    {
        return false;
    }

    for (int i = 0; i < layer->numNeurons; i++)
    {
        layer->biases[i] = biases[i];
    }

    return true;
}

bool forwardDense(LayerDense* layer,
                  const DynamicMatrix *inputs)
{
    // The rows in the inputs matrix represent the batches
    // The number of columns represent the number of neurons in previous layer
    // Or, "one row is one batch"
    DynamicMatrix *outputs = dotProductDynamicMatrix(inputs, layer->weights);

    if (!outputs)
    {
        return false;
    }

    if (!addBiasesToOutput(outputs, layer->biases))
    {
        return false;
    }

    printf("output before activationFunction\n");
    printDynamicMatrix(outputs);

    if (!layer->activationFunction(outputs))
    {
        return false;
    }

    // if outputs is being used for the first time
    if (layer->outputs->rows == 0 ||
        layer->outputs->columns == 0)
    {
        if (!pushIntoOutputs(layer->outputs, outputs))
        {
            return false;
        }
    }
    else
    {
        if (!copyDynamicMatrixElements(layer->outputs, outputs))
        {
            return false;
        }
    }

    freeDynamicMatrix(outputs);
    return true;
}

bool getOutputCopyFromLayerDense(const LayerDense* layer, DynamicMatrix *outputDestination)
{
    return copyDynamicMatrix(outputDestination, layer->outputs);
}
