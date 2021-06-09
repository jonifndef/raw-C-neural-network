#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "layer.h"
#include "activationfunctions.h"
#include "utils/dynamicarray.h"
#include "utils/dynamicmatrix.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    // inputs into the first layer
    int numNeuronsPrevLayer = 4;
    int numNeuronsLayer = 3;
    int batchSize = 3;

    double biases_1[3] = {  2,  3,  0.5 };
    double biases_2[3] = { -1,  2, -0.5 };

    // weights matrix
    double weights1Row1[] = {  0.2,   0.8,  -0.5,   1.0  };
    double weights1Row2[] = {  0.5,  -0.91,  0.26, -0.5  };
    double weights1Row3[] = { -0.26, -0.27,  0.17,  0.87 };

    DynamicMatrix *weights_1 = createDynamicMatrix();
    pushRow(weights_1, createPopulatedDynamicArr(weights1Row1, 4), DO_TAKE_OWNERSHIP);
    pushRow(weights_1, createPopulatedDynamicArr(weights1Row2, 4), DO_TAKE_OWNERSHIP);
    pushRow(weights_1, createPopulatedDynamicArr(weights1Row3, 4), DO_TAKE_OWNERSHIP);

    printf("Printing weights_1:\n");
    printDynamicMatrix(weights_1);

    double weights2Row1[] = {  0.1, -0.14,  0.5  };
    double weights2Row2[] = { -0.5,  0.12, -0.33 };
    double weights2Row3[] = { -0.44, 0.73, -0.13 };

    DynamicMatrix *weights_2 = createDynamicMatrix();
    pushRow(weights_2, createPopulatedDynamicArr(weights2Row1, 3), DO_TAKE_OWNERSHIP);
    pushRow(weights_2, createPopulatedDynamicArr(weights2Row2, 3), DO_TAKE_OWNERSHIP);
    pushRow(weights_2, createPopulatedDynamicArr(weights2Row3, 3), DO_TAKE_OWNERSHIP);

    printf("Printing weights_2:\n");
    printDynamicMatrix(weights_2);

    // inputs matrix
    // The number of rows represent batchsize
    // So from the previous "layer" we have 4 inputs, with 3 samples in one batch
    double inputs1[] = {  1,   2,    3,    2.5 };
    double inputs2[] = {  2.0, 5.0, -1.0,  2.0 };
    double inputs3[] = { -1.5, 2.7,  3.3, -0.8 };

    DynamicMatrix *inputs = createDynamicMatrix();
    pushRow(inputs, createPopulatedDynamicArr(inputs1, 4), DO_TAKE_OWNERSHIP);
    pushRow(inputs, createPopulatedDynamicArr(inputs2, 4), DO_TAKE_OWNERSHIP);
    pushRow(inputs, createPopulatedDynamicArr(inputs3, 4), DO_TAKE_OWNERSHIP);

    printf("Printing inputs:\n");
    printDynamicMatrix(inputs);

    //DynamicMatrix *outputs1 = createDynamicMatrix();
    //DynamicMatrix *outputs2 = createDynamicMatrix();

    LayerDense *layer1 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsPrevLayer, linear);
    updateWeightsAndBiasesInLayerDense(layer1, weights_1, biases_1);

    LayerDense *layer2 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsLayer, linear);
    updateWeightsAndBiasesInLayerDense(layer2, weights_2, biases_2);

    forwardDense(layer1, inputs);
    DynamicMatrix *outputs1 = getOutputsFromLayerDense(layer1);

    // Correct answers for layer 1:
    //      4.8,     1.21,     2.385
    //      8.9,    -1.81,     0.2
    //      1.41,    1.051,    0.026

    printf("Printing outputs1:\n");
    printDynamicMatrix(outputs1);

    forwardDense(layer2, outputs1);
    DynamicMatrix *outputs2 = getOutputsFromLayerDense(layer2);

    // Correct answers for layer 2:
    //      0.5031, -1.04185, -2.03875
    //      0.2434, -2.7332,  -5.7633
    //     -0.99314, 1.41254, -0.35655

    printf("Printing outputs2:\n");
    printDynamicMatrix(outputs2);

    freeDynamicMatrix(inputs);

    freeLayerDenseContents(layer1);
    freeLayerDenseContents(layer2);
    return 0;
}
