#ifndef DYNAMIC_MATRIX_TEST_H
#define DYNAMIC_MATRIX_TEST_H

#include <stdlib.h>
#include <check.h>

#include "../src/utils/dynamicmatrix.h"

START_TEST(dynamicMatrixTest)
{
    DynamicMatrix *matrix = createDynamicMatrix();
    DynamicArray *arr1 = createDynamicArr();
    DynamicArray *arr2 = createDynamicArr();
    DynamicArray *arr3 = createDynamicArr();
    DynamicArray *arr4 = createDynamicArr();

    double row1[] = { 3.24, 1.2, 66.359, 7.0, 0.0, 1.445 };
    setDynamicArrRow(arr1, row1, 6);
    pushRow(matrix, arr1);
    freeDynamicArr(arr1);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 5), 1.445);

    double row2[] = { 2.14, 5.1, 0.02, 0.79, 99.99, 59238.39 };
    setDynamicArrRow(arr2, row2, 6);
    pushRow(matrix, arr2);
    freeDynamicArr(arr2);

    double row3[] = { 0.01, 31.14, 0.09, 99.12 };
    setDynamicArrRow(arr3, row3, 4);
    pushRow(matrix, arr3);
    freeDynamicArr(arr3);

    double row4[] = { 2.78, 49,98, 2.30 };
    setDynamicArrRow(arr4, row4, 3);
    pushRow(matrix, arr4);
    freeDynamicArr(arr4);

    printDynamicMatrix(matrix);

    freeDynamicMatrix(matrix);
}
END_TEST

#endif //DYNAMIC_MATRIX_TEST_H

