#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "layer.h"

int main(int argc, char *argv[])
{
    int numNeuronsPrevLayer = 4;
    int numNeuronsLayer = 3;
    int batchSize = 3;
    double biases[3] = { 2, 3, 0.5 };

    // weights matrix
    double weightsRow1[]  = { 0.2, 0.8, -0.5, 1.0 };
    double weightsRow2[] =  { 0.5, -0.91, 0.26, -0.5 };
    double weightsRow3[] =  { -0.26, -0.27, 0.17, 0.87 };

    MatrixDoubles *weights = createMatrixDoubles(3, 4);
    setMatrixDoublesRow(weights, 0, weightsRow1);
    setMatrixDoublesRow(weights, 1, weightsRow2);
    setMatrixDoublesRow(weights, 2, weightsRow3);

    // inputs matrix
    double inputs1[] = { 1, 2, 3, 2.5 };
    double inputs2[] = { 2.0, 5.0, -1.0, 2.0 };
    double inputs3[] = { -1.5, 2.7, 3.3, -0.8 };

    MatrixDoubles *inputs = createMatrixDoubles(batchSize, numNeuronsPrevLayer);
    setMatrixDoublesRow(inputs, 0, inputs1);
    setMatrixDoublesRow(inputs, 1, inputs2);
    setMatrixDoublesRow(inputs, 2, inputs3);

    // output matrix
    MatrixDoubles *outputs = createMatrixDoubles(batchSize, numNeuronsLayer);

    Layer *layer = createLayer(numNeuronsLayer, numNeuronsPrevLayer);
    updateWeightsAndBiasesInLayer(layer, weights, biases);
    outputs = getOutputsFromLayer(layer, inputs);

    for (int i = 0; i < batchSize; i++)
    {
        for (int j = 0; j < numNeuronsLayer; j++)
        {
            double element = getMatrixDoublesElement(outputs, i, j);
            printf("%.3f ", element);
        }
        printf("\n");
    }
    free(outputs);

    return 0;
}
