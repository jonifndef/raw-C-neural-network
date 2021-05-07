#ifndef BATCHES_AND_LAYERS_TEST_H
#define BATCHES_AND_LAYERS_TEST_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/layer.h"
#include "../src/activationfunctions.h"

START_TEST(batches_and_layers_test)
{
    srand(time(0));

    int numNeuronsPrevLayer = 4;
    int numNeuronsLayer = 3;
    int batchSize = 3;

    double biases_1[3] = {  2,  3,  0.5 };
    double biases_2[3] = { -1,  2, -0.5 };

    // weights matrix
    double weightsRow1[] = {  0.2,   0.8,  -0.5,   1.0  };
    double weightsRow2[] = {  0.5,  -0.91,  0.26, -0.5  };
    double weightsRow3[] = { -0.26, -0.27,  0.17,  0.87 };

    //MatrixDoubles *weights = createMatrixDoubles(numNeuronsLayer, numNeuronsPrevLayer);
    //setMatrixDoublesRow(weights, 0, weightsRow1);
    //setMatrixDoublesRow(weights, 1, weightsRow2);
    //setMatrixDoublesRow(weights, 2, weightsRow3);

    DynamicMatrix *weights_1 = createDynamicMatrix();
    // I wanna be able to do this, but since the matrix does not take over
    // ownership of the array, but rather copies it, we will bleed memory
    pushRow(weights_1, createPopulatedDynamicArr(weightsRow1, 4), DO_TAKE_OWNERSHIP);
    pushRow(weights_1, createPopulatedDynamicArr(weightsRow2, 4), DO_TAKE_OWNERSHIP);
    pushRow(weights_1, createPopulatedDynamicArr(weightsRow3, 4), DO_TAKE_OWNERSHIP);

    double weights2Row1[] = {  0.1, -0.14,  0.5  };
    double weights2Row2[] = { -0.5,  0.12, -0.33 };
    double weights2Row3[] = { -0.44, 0.73, -0.13 };

    //MatrixDoubles *weights2 = createMatrixDoubles(numNeuronsLayer, numNeuronsLayer);
    //setMatrixDoublesRow(weights2, 0, weights2Row1);
    //setMatrixDoublesRow(weights2, 1, weights2Row2);
    //setMatrixDoublesRow(weights2, 2, weights2Row3);

    DynamicMatrix *weights_2 = createDynamicMatrix();
    pushRow(weights_2, createPopulatedDynamicArr(weights2Row1, 3), DO_TAKE_OWNERSHIP);
    pushRow(weights_2, createPopulatedDynamicArr(weights2Row2, 3), DO_TAKE_OWNERSHIP);
    pushRow(weights_2, createPopulatedDynamicArr(weights2Row3, 3), DO_TAKE_OWNERSHIP);

    // inputs matrix
    double inputs1[] = {  1,   2,    3,    2.5 };
    double inputs2[] = {  2.0, 5.0, -1.0,  2.0 };
    double inputs3[] = { -1.5, 2.7,  3.3, -0.8 };

    DynamicMatrix *inputs = createDynamicMatrix();
    pushRow(inputs, createPopulatedDynamicArr(inputs1, 4), DO_TAKE_OWNERSHIP);
    pushRow(inputs, createPopulatedDynamicArr(inputs2, 4), DO_TAKE_OWNERSHIP);
    pushRow(inputs, createPopulatedDynamicArr(inputs3, 4), DO_TAKE_OWNERSHIP);

    //MatrixDoubles *inputs = createMatrixDoubles(batchSize, numNeuronsPrevLayer);
    //setMatrixDoublesRow(inputs, 0, inputs1);
    //setMatrixDoublesRow(inputs, 1, inputs2);
    //setMatrixDoublesRow(inputs, 2, inputs3);

    // output matrix

    DynamicMatrix *outputs1 = createDynamicMatrix();
    DynamicMatrix *outputs2 = createDynamicMatrix();

    //MatrixDoubles *outputs1 = createMatrixDoubles(batchSize, numNeuronsLayer);
    //MatrixDoubles *outputs2 = createMatrixDoubles(batchSize, numNeuronsLayer);

    LayerDense *layer1 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsPrevLayer, relu);
    updateWeightsAndBiasesInLayerDense(layer1, weights_1, biases_1);

    LayerDense *layer2 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsLayer, relu);
    updateWeightsAndBiasesInLayerDense(layer2, weights_2, biases_2);

    forwardDense(layer1, inputs);
    outputs1 = getOutputsFromLayerDense(layer1);

    // Correct answers for layer 1:
    //      4.8,     1.21,     2.385
    //      8.9,    -1.81,     0.2
    //      1.41,    1.051,    0.026

    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 0, 0), 4.8);
    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 0, 1), 1.21);
    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 0, 2), 2.385);

    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 1, 0), 8.9);
    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 1, 1), -1.81);
    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 1, 2), 0.2);

    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 2, 0), 1.41);
    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 2, 1), 1.051);
    ck_assert_float_eq(getDynamicMatrixElement(outputs1, 2, 2), 0.026);

    forwardDense(layer2, outputs1);
    outputs2 = getOutputsFromLayerDense(layer2);

    // Correct answers for layer 2:
    //      0.5031, -1.04185, -2.03875
    //      0.2434, -2.7332,  -5.7633
    //     -0.99314, 1.41254, -0.35655

    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 0, 0), 0.5031);
    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 0, 1), -1.04185);
    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 0, 2), -2.03875);

    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 1, 0), 0.2434);
    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 1, 1), -2.7332);
    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 1, 2), -5.7633);

    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 2, 0), -0.99314);
    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 2, 1), 1.41254);
    ck_assert_float_eq(getDynamicMatrixElement(outputs2, 2, 2), -0.35655);

    freeDynamicMatrix(outputs1);
    freeDynamicMatrix(outputs2);

    freeLayerDenseContents(layer1);
    freeLayerDenseContents(layer2);
}
END_TEST

#endif // BATCHES_AND_LAYERS_TEST_H
