#include <stdlib.h>
#include <stdio.h> // debug

#include "layer.h"

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

void forwardDense(LayerDense* layer, const DynamicMatrix *inputs)
{
    // The rows in this instance represent the batches
    // We want to calculate the the output of each neuron for each of the batches
    // TODO: Calculate the dimensions of the output matrix, set output matrix accordingly
    // Do dot product based on transposed matricies instead, this version is too far off the real math
    for (int i = 0; i < inputs->rows; i++)
    {
        DynamicArray *outputArr = createDynamicArr();

        for (int j = 0; j < layer->numNeurons; j++)
        {
            //setDynamicMatrixElement(
            //    layer->outputs, i, j,
            //    getNeuronOutput(&layer->neurons[j], getDynamicMatrixRowRef(inputs, i)));
            pushBackDynamicArr(outputArr,
                               getNeuronOutput(&layer->neurons[j],
                               getDynamicMatrixRowRef(inputs, i)));
        }
        pushRow(layer->outputs, outputArr, DO_NOT_TAKE_OWNERSHIP);
    }
}

DynamicMatrix* getOutputsFromLayerDense(const LayerDense* layer)
{
    return layer->outputs;
}

