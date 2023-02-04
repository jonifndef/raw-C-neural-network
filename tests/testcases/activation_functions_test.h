#ifndef ACTIVATION_FUNCTIONS_TEST_H
#define ACTIVATION_FUNCTIONS_TEST_H

#include <check.h>

#include "../../src/layer.h"
#include "../../src/activationfunctions.h"

START_TEST(activation_functions_test)
{
    uint numInputs = 3;
    uint batchSize = 4;
    uint numNeurons = 3;

    LayerDense *layer = createLayerDense(numNeurons, batchSize, numInputs, softmax);

    //DynamicMatrix *weights = createDynamicMatrixWithCapacity(3, 3);
    //double row_1 = { 2.1,
    //pushRow(weights, createPopulatedDynamicArr(), DO_TAKE_OWNERSHIP);

    //bool updated = updateWeightsAndBiasesInLayerDense(layer, weights, biases);

    DynamicMatrix *inputs = createDynamicMatrixWithCapacity(batchSize, numInputs);
    double batch_1[] = {  1.45,  4,21,  9.01  };
    double batch_2[] = {  0.41, -0.18, -2.98  };
    double batch_3[] = {  4.63,  0.02,  5.07  };
    double batch_4[] = { -13.34, 0.94,  22.05 };

    pushRow(inputs, createPopulatedDynamicArr(batch_1, 3), DO_TAKE_OWNERSHIP);
    pushRow(inputs, createPopulatedDynamicArr(batch_2, 3), DO_TAKE_OWNERSHIP);
    pushRow(inputs, createPopulatedDynamicArr(batch_3, 3), DO_TAKE_OWNERSHIP);
    pushRow(inputs, createPopulatedDynamicArr(batch_4, 3), DO_TAKE_OWNERSHIP);

    forwardDense(layer, inputs);


    DynamicMatrix *outputs = createDynamicMatrix();
    getOutputCopyFromLayerDense(layer, outputs);
    printDynamicMatrix(outputs);

    freeDynamicMatrix(outputs);
    freeDynamicMatrix(inputs);
    freeLayerDenseContents(layer);
}
END_TEST

#endif // ACTIVATION_FUNCTIONS_TEST_H
