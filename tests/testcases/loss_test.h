#ifndef LOSS_TEST_H
#define LOSS_TEST_H

#include <check.h>

#include "../../src/utils/dynamicmatrix.h"
#include "../../src/loss.h"

START_TEST(loss_test)
{
    //double first  = { 0.7, 0.1, 0.2 };
    //double second = { 0.1, 0.5, 0.4 };
    //double third  = { 0.02, 0.9, 0.08 };

    double olle[3][3] = {{ 0.7,  0.1, 0.2 },
                         { 0.1,  0.5, 0.4 },
                         { 0.02, 0.9, 0.08 }};

    DynamicMatrix *outputs = createDynamicMatrixWithCapacity(3, 3);

    pushRow(outputs, createPopulatedDynamicArr(olle[0], 3), DO_TAKE_OWNERSHIP);
    pushRow(outputs, createPopulatedDynamicArr(olle[1], 3), DO_TAKE_OWNERSHIP);
    pushRow(outputs, createPopulatedDynamicArr(olle[2], 3), DO_TAKE_OWNERSHIP);

    printf("yoyoyoy\n");
    printDynamicMatrix(outputs);

    uint classTarget[] = { 0, 1, 1 };

    DynamicArray *loss = categorialCrossEntropy(outputs, classTarget);

    printDynamicArr(loss);
}
#endif // LOSS_TEST_H
