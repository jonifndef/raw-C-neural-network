#ifndef LOSS_TEST_H
#define LOSS_TEST_H

#include <check.h>
#include <stdio.h>

#include "../../src/utils/dynamicmatrix.h"
#include "../../src/loss.h"

START_TEST(loss_test)
{
    double olle[3][3] = {{ 0.7,  0.1, 0.2 },
                         { 0.1,  0.5, 0.4 },
                         { 0.02, 0.9, 0.08 }};

    DynamicMatrix *outputs = createDynamicMatrixWithCapacity(3, 3);

    pushRow(outputs, createPopulatedDynamicArr(olle[0], 3), DO_TAKE_OWNERSHIP);
    pushRow(outputs, createPopulatedDynamicArr(olle[1], 3), DO_TAKE_OWNERSHIP);
    pushRow(outputs, createPopulatedDynamicArr(olle[2], 3), DO_TAKE_OWNERSHIP);

    printDynamicMatrix(outputs);

    double classTargetSparse[] = { 0, 1, 1 };
    DynamicArray *classTargetsArr = createPopulatedDynamicArr(classTargetSparse, 3);
    DynamicMatrix *classTargets = createDynamicMatrix();
    pushRow(classTargets, classTargetsArr, DO_TAKE_OWNERSHIP);

    DynamicArray *loss = createDynamicArr();
    loss = categorialCrossEntropy(outputs, classTargets);

    printDynamicArr(loss);

    double avg = getAvrageDynamicAarr(loss);
    printf("avg sparse: %f\n", avg);

    double classTargetOneHot[3][3] = {{ 1, 0, 0 },
                                      { 0, 1, 0 },
                                      { 0, 1, 0 }};
    freeDynamicMatrix(classTargets);

    DynamicMatrix *classTargetsHot = createDynamicMatrixWithCapacity(3, 3);

    pushRow(classTargetsHot, createPopulatedDynamicArr(classTargetOneHot[0], 3), DO_TAKE_OWNERSHIP);
    pushRow(classTargetsHot, createPopulatedDynamicArr(classTargetOneHot[1], 3), DO_TAKE_OWNERSHIP);
    pushRow(classTargetsHot, createPopulatedDynamicArr(classTargetOneHot[2], 3), DO_TAKE_OWNERSHIP);

    clearDynamicArr(loss);

    printDynamicMatrix(classTargetsHot);

    loss = categorialCrossEntropy(outputs, classTargetsHot);

    printDynamicArr(loss);

    avg = getAvrageDynamicAarr(loss);
    printf("avg one hot: %f\n", avg);
}
#endif // LOSS_TEST_H
