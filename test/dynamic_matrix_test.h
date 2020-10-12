#ifndef DYNAMIC_MATRIX_TEST_H
#define DYNAMIC_MATRIX_TEST_H

#include <stdlib.h>
#include <check.h>

#include "../src/utils/dynamicmatrix.h"

START_TEST(dynamicMatrixTest)
{
    DynamicMatrix *matrix = createDynamicMatrix();
    DynamicArray *arr1 = createDynamicArr();

    double row1[] = { 3.24, 1.2, 66.359, 7.0, 0.0, 1.445 };
    setDynamicArrRow(arr1, row1, 6);
    pushRow(matrix, arr1);
    freeDynamicArr(arr1);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 5), 1.445);

    freeDynamicMatrix(matrix);
}
END_TEST

#endif //DYNAMIC_MATRIX_TEST_H

