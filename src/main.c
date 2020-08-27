#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "layer.h"
#include "activationfunctions.h"

int main(int argc, char *argv[])
{
    MatrixDoubles *mrx = calloc(1, sizeof(MatrixDoubles));
    if (!readSampleData("/home/jonas/Development/raw_C_neural_network/nnfs_python/output_X.txt", mrx))
    //if (!readSampleData("/home/jonas/Development/ollebolle_test.txt", mrx))
        printf("invalid format\n");
    return 0;

    srand(time(0));

    int numNeuronsPrevLayer = 4;
    int numNeuronsLayer = 3;
    int batchSize = 3;

    double biases[3] = { 2, 3, 0.5 };
    double biases2[3] = { -1, 2, -0.5 };

    // weights matrix
    double weightsRow1[] = { 0.2, 0.8, -0.5, 1.0 };
    double weightsRow2[] = { 0.5, -0.91, 0.26, -0.5 };
    double weightsRow3[] = { -0.26, -0.27, 0.17, 0.87 };

    MatrixDoubles *weights = createMatrixDoubles(numNeuronsLayer, numNeuronsPrevLayer);
    setMatrixDoublesRow(weights, 0, weightsRow1);
    setMatrixDoublesRow(weights, 1, weightsRow2);
    setMatrixDoublesRow(weights, 2, weightsRow3);

    double weights2Row1[] = { 0.1, -0.14, -0.5 };
    double weights2Row2[] = { -0.5, 0.12, -0.33 };
    double weights2Row3[] = { -0.44, 0.73, -0.13 };

    MatrixDoubles *weights2 = createMatrixDoubles(numNeuronsLayer, numNeuronsLayer);
    setMatrixDoublesRow(weights2, 0, weights2Row1);
    setMatrixDoublesRow(weights2, 1, weights2Row2);
    setMatrixDoublesRow(weights2, 2, weights2Row3);

    // inputs matrix
    double inputs1[] = { 1, 2, 3, 2.5 };
    double inputs2[] = { 2.0, 5.0, -1.0, 2.0 };
    double inputs3[] = { -1.5, 2.7, 3.3, -0.8 };

    MatrixDoubles *inputs = createMatrixDoubles(batchSize, numNeuronsPrevLayer);
    setMatrixDoublesRow(inputs, 0, inputs1);
    setMatrixDoublesRow(inputs, 1, inputs2);
    setMatrixDoublesRow(inputs, 2, inputs3);

    // output matrix
    MatrixDoubles *outputs1 = createMatrixDoubles(batchSize, numNeuronsLayer);
    MatrixDoubles *outputs2 = createMatrixDoubles(batchSize, numNeuronsLayer);

    LayerDense *layer1 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsPrevLayer, relu);
    updateWeightsAndBiasesInLayerDense(layer1, weights, biases);

    LayerDense *layer2 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsLayer, relu);
    updateWeightsAndBiasesInLayerDense(layer2, weights2, biases2);

    forwardDense(layer1, inputs);
    outputs1 = getOutputsFromLayerDense(layer1);

    printf("== Output form layer 1: ===\n");
    for (int i = 0; i < batchSize; i++)
    {
        for (int j = 0; j < numNeuronsLayer; j++)
        {
            double element = getMatrixDoublesElement(outputs1, i, j);
            printf("%.3f ", element);
        }
        printf("\n");
    }

    printf("\n");

    forwardDense(layer2, outputs1);
    outputs2 = getOutputsFromLayerDense(layer2);

    printf("=== Output form layer 2: ===\n");
    for (int i = 0; i < batchSize; i++)
    {
        for (int j = 0; j < numNeuronsLayer; j++)
        {
            double element = getMatrixDoublesElement(outputs2, i, j);
            printf("%.3f ", element);
        }
        printf("\n");
    }
    freeMatrixDoublesContents(outputs1);
    freeMatrixDoublesContents(outputs2);

    freeLayerDenseContents(layer1);
    freeLayerDenseContents(layer2);

    return 0;
}
