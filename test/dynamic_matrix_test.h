#ifndef DYNAMIC_MATRIX_TEST_H
#define DYNAMIC_MATRIX_TEST_H

#include <stdlib.h>
#include <check.h>

#include "../src/utils/dynamicmatrix.h"

START_TEST(dynamicMatrixTest)
{
    DynamicMatrix *matrix = createDynamicMatrix();

    double row0[] = { 3.24, 1.2, 66.359, 7.0, 0.0, 1.445 };
    DynamicArray *arr0 = createDynamicArr();
    setDynamicArrRow(arr0, row0, 6);
    pushRow(matrix, arr0);
    freeDynamicArr(arr0);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 5), 1.445);

    double row1[] = { 2.14, 5.1, 0.02, 0.79, 99.99, 59238.39 };
    DynamicArray *arr1 = createDynamicArr();
    setDynamicArrRow(arr1, row1, 6);
    pushRow(matrix, arr1);

    double row2[] = { 0.01, 31.14, 0.09, 99.12 };
    DynamicArray *arr2 = createDynamicArr();
    setDynamicArrRow(arr2, row2, 4);
    pushRow(matrix, arr2);

    double row3[] = { 2.78, 49.98, 2.30 };
    DynamicArray *arr3 = createDynamicArr();
    setDynamicArrRow(arr3, row3, 3);
    pushRow(matrix, arr3);
    pushRow(matrix, arr3);
    freeDynamicArr(arr3);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 5), 0.0);

    DynamicArray *arr4 = calloc(1, sizeof(DynamicArray));
    ck_assert_ptr_nonnull(arr4);

    // Make sure the content of the second row of the matrix
    // is the same as its 'source array'
    copyDynamicArr(arr4, getDynamicMatrixRowRef(matrix, 1));
    ck_assert_mem_eq(arr4->data, arr1->data, getDynamicArrSize(arr1));
    ck_assert_int_eq(arr4->size, arr1->size);
    ck_assert_int_eq(arr4->capacity, arr1->capacity);
    freeDynamicArr(arr1);

    DynamicArray *arr5 = calloc(1, sizeof(DynamicArray));
    ck_assert_ptr_nonnull(arr5);

    // Make sure that the length of the third row of the matrix
    // is longer than its 'source array', since the row should be padded with zeroes
    copyDynamicArr(arr5, getDynamicMatrixRowRef(matrix, 2));
    ck_assert_int_ne(arr5->size, arr2->size);
    ck_assert_mem_ne(arr5->data, arr2->data, sizeof(double) * getDynamicArrSize(arr5));
    freeDynamicArr(arr2);

    freeDynamicArr(arr4);
    freeDynamicArr(arr5);

    ck_assert_int_eq(matrix->columns, getDynamicMatrixRowRef(matrix, 3)->size);
    ck_assert_int_eq(matrix->columnCapacity, getDynamicMatrixRowRef(matrix, 2)->capacity);
    ck_assert_int_eq(matrix->rows, 5);

    // Test if you can edit elements in-place with the "getDynMatRowRef"-function
    ck_assert_double_eq(getDynamicArrElement(getDynamicMatrixRowRef(matrix, 1), 1), 5.1);
    setDynamicArrElement(getDynamicMatrixRowRef(matrix, 1), 1, 4.33);
    ck_assert_double_eq(getDynamicArrElement(getDynamicMatrixRowRef(matrix, 1), 1), 4.33);

    printDynamicMatrix(matrix);

    //printDynamicMatrix(matrix);

    // Insert some columns
    double column6[] = { 2.51, 0.009, 1093.1, 4.0, 0.63 };
    DynamicArray *arr6 = createDynamicArr();
    setDynamicArrRow(arr6, column6, 5);
    pushColumn(matrix, arr6);
    pushColumn(matrix, arr6);
    pushColumn(matrix, arr6);
    freeDynamicArr(arr6);

    double column7[] = { 4.76, 1.25, 9.01 };
    DynamicArray *arr7 = createDynamicArr();
    setDynamicArrRow(arr7, column7, 3);
    pushColumn(matrix, arr7);
    freeDynamicArr(arr7);

    double column8[] = { 1.01, 2.02, 3.03, 4.04, 5.05, 2.52, 3.12, 7.57, 0.01 };
    DynamicArray *arr8 = createDynamicArr();
    setDynamicArrRow(arr8, column8, 9);
    pushColumn(matrix, arr8);
    freeDynamicArr(arr8);

    ck_assert_int_eq(matrix->columnCapacity, getDynamicMatrixRowRef(matrix, 0)->capacity);


    DynamicArray *column9 = getDynamicMatrixColumnRef(matrix, 2);
    printDynamicArr(column9);
    setDynamicArrElement(column9, 0, 66.66);


    printDynamicMatrix(matrix);
    freeDynamicMatrix(matrix);


    matrix = createDynamicMatrix();
}
END_TEST

#endif //DYNAMIC_MATRIX_TEST_H

