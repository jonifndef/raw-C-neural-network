#ifndef LOSS_WITH_SPIRAL_DATA_TEST_H
#define LOSS_WITH_SPIRAL_DATA_TEST_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../src/layer.h"
#include "../../src/activationfunctions.h"
#include "../../src/loss.h"
#include "../../src/utils/fileIO.h"

START_TEST(loss_with_spiral_data_test)
{
    DynamicMatrix *X = createDynamicMatrix();
    DynamicMatrix *y = createDynamicMatrix();

    if (!readSampleData("/home/jonas/Development/raw-C-neural-network/nnfs_python/output_X.txt", " ", X))
    {
        printf("hej1ff\n");
    }

    if (!readSampleData("/home/jonas/Development/raw-C-neural-network/nnfs_python/output_y.txt", " ", y))
    {
        printf("dåff\n");
    }

    printf("olle\n");
    LayerDense *layer1 = createLayerDense(3, 1, 2, relu);
    LayerDense *layer2 = createLayerDense(3, 1, 3, softmax);

    DynamicMatrix *output1 = createDynamicMatrix();
    DynamicMatrix *output2 = createDynamicMatrix();

    printf("bolle\n");
    if (forwardDense(layer1, X))
        printf("whhops 1");

    if (getOutputCopyFromLayerDense(layer1, output1))
        printf("whhops 2");

    if (forwardDense(layer2, output1))
        printf("whhops 3");

    if (getOutputCopyFromLayerDense(layer2, output2))
        printf("whhops 4");

    printf("kalle\n");
    DynamicArray *loss = createDynamicArr();
    loss = categorialCrossEntropy(output2, y);
    printf("nisse\n");

    printDynamicArr(loss);
    printf("mean loss: %f\n", getAvrageDynamicAarr(loss));
}
END_TEST

#endif // LOSS_WITH_SPIRAL_DATA_TEST_H
