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
    setDynamicArr(arr0, row0, 6);
    pushRow(matrix, arr0, DO_NOT_TAKE_OWNERSHIP);
    //freeDynamicArr(arr0);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 5), 1.445);

    double row1[] = { 2.14, 5.1, 0.02, 0.79, 99.99, 59238.39 };
    DynamicArray *arr1 = createDynamicArr();
    setDynamicArr(arr1, row1, 6);
    pushRow(matrix, arr1, DO_NOT_TAKE_OWNERSHIP);

    double row2[] = { 0.01, 31.14, 0.09, 99.12 };
    DynamicArray *arr2 = createDynamicArr();
    setDynamicArr(arr2, row2, 4);
    pushRow(matrix, arr2, DO_NOT_TAKE_OWNERSHIP);

    double row3[] = { 2.78, 49.98, 2.30 };
    DynamicArray *arr3 = createDynamicArr();
    setDynamicArr(arr3, row3, 3);
    pushRow(matrix, arr3, DO_NOT_TAKE_OWNERSHIP);
    pushRow(matrix, arr3, DO_NOT_TAKE_OWNERSHIP);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 0), 3.24);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 1), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 2), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 3), 7.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 5), 1.445);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 0), 2.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 1), 5.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 2), 0.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 3), 0.79);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 4), 99.99);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 5), 59238.39);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 0), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 1), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 2), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 3), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 5), 0.0);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 5), 0.0);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 5), 0.0);

    DynamicArray *arr4 = calloc(1, sizeof(DynamicArray));
    ck_assert_ptr_nonnull(arr4);

    // Make sure the content of the second row of the matrix
    // is the same as its 'source array'
    copyDynamicArr(arr4, getDynamicMatrixRowRef(matrix, 1));

    ck_assert_mem_eq(arr4->data, arr1->data, getDynamicArrSize(arr1));
    ck_assert_int_eq(arr4->size, arr1->size);
    ck_assert_int_eq(arr4->capacity, arr1->capacity);

    //freeDynamicArr(arr1);

    DynamicArray *arr5 = calloc(1, sizeof(DynamicArray));
    ck_assert_ptr_nonnull(arr5);

    // Make sure that the length of the third row of the matrix
    // is longer than its 'source array', since the row should be padded with zeroes
    copyDynamicArr(arr5, getDynamicMatrixRowRef(matrix, 2));
    ck_assert_int_ne(arr5->size, arr2->size);
    ck_assert_mem_ne(arr5->data, arr2->data, sizeof(double) * getDynamicArrSize(arr5));
    //freeDynamicArr(arr2);

    ck_assert_int_eq(matrix->columns, getDynamicMatrixRowRef(matrix, 3)->size);
    ck_assert_int_eq(matrix->columnCapacity, getDynamicMatrixRowRef(matrix, 2)->capacity);
    ck_assert_int_eq(matrix->rows, 5);

    // Test if you can edit elements in-place with the "getDynMatRowRef"-function
    ck_assert_double_eq(getDynamicArrElement(getDynamicMatrixRowRef(matrix, 1), 1), 5.1);
    setDynamicArrElement(getDynamicMatrixRowRef(matrix, 1), 1, 4.33);
    ck_assert_double_eq(getDynamicArrElement(getDynamicMatrixRowRef(matrix, 1), 1), 4.33);

    printDynamicMatrix(matrix);

    ck_assert_int_eq(matrix->columns, 6);

    // Insert some columns
    double column6[] = { 2.51, 0.009, 1093.1, 4.0, 0.63 };
    DynamicArray *arr6 = createDynamicArr();
    setDynamicArr(arr6, column6, 5);
    pushColumn(matrix, arr6);
    pushColumn(matrix, arr6);
    pushColumn(matrix, arr6);

    ck_assert_int_eq(matrix->columns, 9);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 5), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 6), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 7), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 8), 2.51);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 5), 59238.39);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 6), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 7), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 8), 0.009);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 6), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 7), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 8), 1093.1);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 6), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 7), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 8), 4.0);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 6), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 7), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 8), 0.63);

    double column7[] = { 4.76, 1.25, 9.01 };
    DynamicArray *arr7 = createDynamicArr();
    setDynamicArr(arr7, column7, 3);
    pushColumn(matrix, arr7);

    ck_assert_int_eq(matrix->rows, 5);

    double column8[] = { 1.01, 2.02, 3.03, 4.04, 5.05, 2.52, 3.12, 7.57, 0.01 };
    DynamicArray *arr8 = createDynamicArr();
    setDynamicArr(arr8, column8, 9);
    pushColumn(matrix, arr8);

    ck_assert_int_eq(matrix->rows, 9);
    ck_assert_int_eq(matrix->columnCapacity, getDynamicMatrixRowRef(matrix, 0)->capacity);

    DynamicArray *arr9 = createDynamicArr();
    pushBackDynamicArr(arr9, 1.01);
    pushBackDynamicArr(arr9, 2.02);
    pushBackDynamicArr(arr9, 3.03);
    pushBackDynamicArr(arr9, 4.04);
    pushBackDynamicArr(arr9, 5.05);
    pushBackDynamicArr(arr9, 2.52);
    pushBackDynamicArr(arr9, 3.12);
    pushBackDynamicArr(arr9, 7.57);
    pushBackDynamicArr(arr9, 0.01);

    ck_assert_int_eq(matrix->rowCapacity, arr9->capacity);

    freeDynamicArr(arr9);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 8), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 9), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 10), 1.01);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 8), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 9), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 10), 2.02);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 8), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 9), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 10), 3.03);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 8), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 9), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 10), 4.04);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 8), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 9), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 10), 5.05);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 8), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 9), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 10), 2.52);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 8), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 9), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 10), 3.12);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 8), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 9), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 10), 7.57);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 8), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 9), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 10), 0.01);

    DynamicArray *column9 = createDynamicMatrixColumnCopy(matrix, 2);
    printDynamicArr(column9);
    setDynamicArrElement(column9, 0, 66.66);

    ck_assert_double_ne(getDynamicMatrixElement(matrix, 2, 0), 66.66);

    freeDynamicArr(column9);

    //printDynamicMatrix(matrix);
    freeDynamicMatrix(matrix);

    // ============================================== //
    //                   new matrix                   //
    // ============================================== //

    matrix = createDynamicMatrix();
    pushColumn(matrix, arr7); //3
    pushColumn(matrix, arr8); //9
    pushColumn(matrix, arr8); //9
    pushColumn(matrix, arr6); //5
    pushRow(matrix, arr3, DO_NOT_TAKE_OWNERSHIP); //3
    printDynamicMatrix(matrix);

    // 10x4
    //
    // arr7: 4.76, 1.25, 9.01
    // arr8: 1.01, 2.02, 3.03, 4.04, 5.05, 2.52, 3.12, 7.57, 0.01
    // arr6: 2.51, 0.009, 1093.1, 4.0, 0.63
    // arr3: 2.78, 49.98, 2.30
    //
    // Resulting matrix should look as follows:
    //  4.76   1.01   1.01   2.51
    //  1.25   2.02   2.02   0.009
    //  9.01   3.03   3.03   1093.1
    //  0.0    4.04   4.04   4.0
    //  0.0    5.05   5.05   0.63
    //  0.0    2.52   2.52   0.0
    //  0.0    3.12   3.12   0.0
    //  0.0    7.57   7.57   0.0
    //  0.0    0.01   0.01   0.0
    //  2.78   49.98  2.30   0.0

    ck_assert_int_eq(matrix->rows, 10);
    ck_assert_int_eq(matrix->columns, 4);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 0), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 1), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 3), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 0, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 0), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 1), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 3), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 1, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 0), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 1), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 2), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 3), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 2, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 1), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 2), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 3), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 3, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 1), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 3), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 4, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 1), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 2), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 5, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 1), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 6, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 1), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 7, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 1), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 2), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 8, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrix, 9, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 9, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 9, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 9, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrix, 9, 4), -999);


    //freeDynamicArr(arr3);
    freeDynamicArr(arr6);
    freeDynamicArr(arr7);
    freeDynamicArr(arr8);

    DynamicMatrix *matrixCopy = createDynamicMatrix();
    copyDynamicMatrix(matrixCopy, matrix);

    ck_assert_int_eq(matrix->rows, matrixCopy->rows);
    ck_assert_int_eq(matrix->columns, matrixCopy->columns);
    ck_assert_int_eq(matrix->rowCapacity, matrixCopy->rowCapacity);
    ck_assert_int_eq(matrix->columnCapacity, matrixCopy->columnCapacity);

    freeDynamicMatrix(matrix);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 0), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 1), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 2), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 3), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 1), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 2), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 3), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 1), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), -999);

    printDynamicMatrix(matrixCopy);

    pushRowElement(matrixCopy, 4, 0.360);
    pushColumnElement(matrixCopy, 1, 0.894);

    // Resulting matrix should look as follows:
    //  4.76   1.01   1.01   2.51   0.0
    //  1.25   2.02   2.02   0.009  0.0
    //  9.01   3.03   3.03   1093.1 0.0
    //  0.0    4.04   4.04   4.0    0.0
    //  0.0    5.05   5.05   0.63   0.360
    //  0.0    2.52   2.52   0.0    0.0
    //  0.0    3.12   3.12   0.0    0.0
    //  0.0    7.57   7.57   0.0    0.0
    //  0.0    0.01   0.01   0.0    0.0
    //  2.78   49.98  2.30   0.0    0.0
    //  0.0    0.894  0.0    0.0    0.0

    ck_assert_int_eq(matrixCopy->rows, 11);
    ck_assert_int_eq(matrixCopy->columns, 5);

    printDynamicMatrix(matrixCopy);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.36);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), -999);

    insertDynamicMatrixRow(matrixCopy, 5, arr3);
    ck_assert_int_eq(matrixCopy->columns, 5);

    // Resulting matrix should look as follows:
    //  4.76   1.01   1.01   2.51   0.0
    //  1.25   2.02   2.02   0.009  0.0
    //  9.01   3.03   3.03   1093.1 0.0
    //  0.0    4.04   4.04   4.0    0.0
    //  0.0    5.05   5.05   0.63   0.360
    //  2.78   49.98  2.30   0.0    0.0
    //  0.0    2.52   2.52   0.0    0.0
    //  0.0    3.12   3.12   0.0    0.0
    //  0.0    7.57   7.57   0.0    0.0
    //  0.0    0.01   0.01   0.0    0.0
    //  2.78   49.98  2.30   0.0    0.0
    //  0.0    0.894  0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 0), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 1), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 2), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 3), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 1), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 2), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 3), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.360);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 1), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 1), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 2), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), -999);


    insertDynamicMatrixRow(matrixCopy, 0, arr1);
    ck_assert_int_eq(matrixCopy->columns, 6);

    // Resulting matrix should look as follows:
    //  2.14   5.1    0.02   0.79   99.99  59238.39
    //  4.76   1.01   1.01   2.51   0.0    0.0
    //  1.25   2.02   2.02   0.009  0.0    0.0
    //  9.01   3.03   3.03   1093.1 0.0    0.0
    //  0.0    4.04   4.04   4.0    0.0    0.0
    //  0.0    5.05   5.05   0.63   0.360  0.0
    //  2.78   49.98  2.30   0.0    0.0    0.0
    //  0.0    2.52   2.52   0.0    0.0    0.0
    //  0.0    3.12   3.12   0.0    0.0    0.0
    //  0.0    7.57   7.57   0.0    0.0    0.0
    //  0.0    0.01   0.01   0.0    0.0    0.0
    //  2.78   49.98  2.30   0.0    0.0    0.0
    //  0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 2.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 5.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 0.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 0.79);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 99.99);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 5), 59238.39);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 0), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 1), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 3), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 0), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 1), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 2), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 3), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.360);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 1), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 2), 2.52);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 1), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 1), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 2), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 6), -999);


    eraseDynamicArr(arr0, 0);
    bool res_first = insertDynamicMatrixRow(matrixCopy, 12, arr0);
    ck_assert_int_eq(res_first, true);

    // Resulting matrix should look as follows:
    //  2.14   5.1    0.02   0.79   99.99  59238.39
    //  4.76   1.01   1.01   2.51   0.0    0.0
    //  1.25   2.02   2.02   0.009  0.0    0.0
    //  9.01   3.03   3.03   1093.1 0.0    0.0
    //  0.0    4.04   4.04   4.0    0.0    0.0
    //  0.0    5.05   5.05   0.63   0.360  0.0
    //  2.78   49.98  2.30   0.0    0.0    0.0
    //  0.0    2.52   2.52   0.0    0.0    0.0
    //  0.0    3.12   3.12   0.0    0.0    0.0
    //  0.0    7.57   7.57   0.0    0.0    0.0
    //  0.0    0.01   0.01   0.0    0.0    0.0
    //  2.78   49.98  2.30   0.0    0.0    0.0
    //  1.2    66.359 7.0    0.0    1.445  0.0
    //  0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), 7.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 1), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 6), -999);


    ck_assert_int_eq(matrixCopy->rows, 14);

    bool res_second = insertDynamicMatrixRow(matrixCopy, 14, arr0);
    ck_assert_int_eq(res_second, false);

    //// Resulting matrix should look as follows:
    ////  2.14   5.1    0.02   0.79   99.99  59238.39
    ////  4.76   1.01   1.01   2.51   0.0    0.0
    ////  1.25   2.02   2.02   0.009  0.0    0.0
    ////  9.01   3.03   3.03   1093.1 0.0    0.0
    ////  0.0    4.04   4.04   4.0    0.0    0.0
    ////  0.0    5.05   5.05   0.63   0.360  0.0
    ////  2.78   49.98  2.30   0.0    0.0    0.0
    ////  0.0    2.52   2.52   0.0    0.0    0.0
    ////  0.0    3.12   3.12   0.0    0.0    0.0
    ////  0.0    7.57   7.57   0.0    0.0    0.0
    ////  0.0    0.01   0.01   0.0    0.0    0.0
    ////  2.78   49.98  2.30   0.0    0.0    0.0
    ////  1.2    66.359 7.0    0.0    1.445  0.0
    ////  0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), 7.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 1), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 14, 6), -999);


    eraseDynamicMatrixRow(matrixCopy, 0);

    //// Resulting matrix should look as follows:
    ////  4.76   1.01   1.01   2.51   0.0    0.0
    ////  1.25   2.02   2.02   0.009  0.0    0.0
    ////  9.01   3.03   3.03   1093.1 0.0    0.0
    ////  0.0    4.04   4.04   4.0    0.0    0.0
    ////  0.0    5.05   5.05   0.63   0.360  0.0
    ////  2.78   49.98  2.30   0.0    0.0    0.0
    ////  0.0    2.52   2.52   0.0    0.0    0.0
    ////  0.0    3.12   3.12   0.0    0.0    0.0
    ////  0.0    7.57   7.57   0.0    0.0    0.0
    ////  0.0    0.01   0.01   0.0    0.0    0.0
    ////  2.78   49.98  2.30   0.0    0.0    0.0
    ////  1.2    66.359 7.0    0.0    1.445  0.0
    ////  0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 7.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 13, 6), -999);


    bool res_third = eraseDynamicMatrixRow(matrixCopy, 6);
    ck_assert_int_eq(res_third, true);

    // Resulting matrix should look as follows:
    //  4.76   1.01   1.01   2.51   0.0    0.0
    //  1.25   2.02   2.02   0.009  0.0    0.0
    //  9.01   3.03   3.03   1093.1 0.0    0.0
    //  0.0    4.04   4.04   4.0    0.0    0.0
    //  0.0    5.05   5.05   0.63   0.360  0.0
    //  2.78   49.98  2.30   0.0    0.0    0.0
    //  0.0    3.12   3.12   0.0    0.0    0.0
    //  0.0    7.57   7.57   0.0    0.0    0.0
    //  0.0    0.01   0.01   0.0    0.0    0.0
    //  2.78   49.98  2.30   0.0    0.0    0.0
    //  1.2    66.359 7.0    0.0    1.445  0.0
    //  0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.360);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);

    bool res_fourth = eraseDynamicMatrixRow(matrixCopy, 12);
    ck_assert_int_eq(res_fourth, false);

    //// Resulting matrix should look as follows:
    ////  4.76   1.01   1.01   2.51   0.0    0.0
    ////  1.25   2.02   2.02   0.009  0.0    0.0
    ////  9.01   3.03   3.03   1093.1 0.0    0.0
    ////  0.0    4.04   4.04   4.0    0.0    0.0
    ////  0.0    5.05   5.05   0.63   0.360  0.0
    ////  2.78   49.98  2.30   0.0    0.0    0.0
    ////  0.0    3.12   3.12   0.0    0.0    0.0
    ////  0.0    7.57   7.57   0.0    0.0    0.0
    ////  0.0    0.01   0.01   0.0    0.0    0.0
    ////  2.78   49.98  2.30   0.0    0.0    0.0
    ////  1.2    66.359 7.0    0.0    1.445  0.0
    ////  0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);

    insertDynamicMatrixColumn(matrixCopy, 0, arr2);
    //0.01, 31.14, 0.09, 99.12

    ck_assert_int_eq(matrixCopy->columns, 7);
    ck_assert_int_eq(matrixCopy->rows, 12);

    // Resulting matrix should look as follows:
    // 0.01    4.76   1.01   1.01   2.51   0.0    0.0
    // 31.14   1.25   2.02   2.02   0.009  0.0    0.0
    // 0.09    9.01   3.03   3.03   1093.1 0.0    0.0
    // 99.12   0.0    4.04   4.04   4.0    0.0    0.0
    // 0.0     0.0    5.05   5.05   0.63   0.360  0.0
    // 0.0     2.78   49.98  2.30   0.0    0.0    0.0
    // 0.0     0.0    3.12   3.12   0.0    0.0    0.0
    // 0.0     0.0    7.57   7.57   0.0    0.0    0.0
    // 0.0     0.0    0.01   0.01   0.0    0.0    0.0
    // 0.0     2.78   49.98  2.30   0.0    0.0    0.0
    // 0.0     1.2    66.359 7.0    0.0    1.445  0.0
    // 0.0     0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 0), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 1), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 2), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 3), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 0), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 2), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 3), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 5), 0.360);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 3), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 1), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 2), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 3), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 1), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 2), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 3), 7.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 7), -999);

    insertDynamicMatrixColumn(matrixCopy, 6, arr2);
    //0.01, 31.14, 0.09, 99.12

    //// Resulting matrix should look as follows:
    //// 0.01    4.76   1.01   1.01   2.51   0.0    0.01   0.0
    //// 31.14   1.25   2.02   2.02   0.009  0.0    31.14  0.0
    //// 0.09    9.01   3.03   3.03   1093.1 0.0    0.09   0.0
    //// 99.12   0.0    4.04   4.04   4.0    0.0    99.12  0.0
    //// 0.0     0.0    5.05   5.05   0.63   0.360  0.0    0.0
    //// 0.0     2.78   49.98  2.30   0.0    0.0    0.0    0.0
    //// 0.0     0.0    3.12   3.12   0.0    0.0    0.0    0.0
    //// 0.0     0.0    7.57   7.57   0.0    0.0    0.0    0.0
    //// 0.0     0.0    0.01   0.01   0.0    0.0    0.0    0.0
    //// 0.0     2.78   49.98  2.30   0.0    0.0    0.0    0.0
    //// 0.0     1.2    66.359 7.0    0.0    1.445  0.0    0.0
    //// 0.0     0.0    0.894  0.0    0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 6), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 6), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 0), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 1), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 2), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 3), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 6), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 0), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 2), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 3), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 6), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 5), 0.360);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 3), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 1), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 2), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 3), 2.30);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 1), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 2), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 3), 7.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 7), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 8), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 7), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 8), -999);

    ck_assert_int_eq(matrixCopy->columns, 8);
    eraseDynamicMatrixColumn(matrixCopy, 3);
    ck_assert_int_eq(matrixCopy->columns, 7);

    //// Resulting matrix should look as follows:
    //// 0.01    4.76   1.01   2.51   0.0    0.01   0.0
    //// 31.14   1.25   2.02   0.009  0.0    31.14  0.0
    //// 0.09    9.01   3.03   1093.1 0.0    0.09   0.0
    //// 99.12   0.0    4.04   4.0    0.0    99.12  0.0
    //// 0.0     0.0    5.05   0.63   0.360  0.0    0.0
    //// 0.0     2.78   49.98  0.0    0.0    0.0    0.0
    //// 0.0     0.0    3.12   0.0    0.0    0.0    0.0
    //// 0.0     0.0    7.57   0.0    0.0    0.0    0.0
    //// 0.0     0.0    0.01   0.0    0.0    0.0    0.0
    //// 0.0     2.78   49.98  0.0    0.0    0.0    0.0
    //// 0.0     1.2    66.359 0.0    1.445  0.0    0.0
    //// 0.0     0.0    0.894  0.0    0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 5), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 5), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 0), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 1), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 2), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 3), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 5), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 0), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 2), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 3), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 5), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.360);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 2), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 1), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 2), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 1), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 2), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 6), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 7), -999);

    bool res_2 = eraseDynamicMatrixColumn(matrixCopy, -1);
    ck_assert_int_eq(res_2, false);
    ck_assert_int_eq(matrixCopy->columns, 7);

    bool res_3 = eraseDynamicMatrixColumn(matrixCopy, 7);
    ck_assert_int_eq(res_3, false);
    ck_assert_int_eq(matrixCopy->columns, 7);

    bool res_4 = eraseDynamicMatrixColumn(matrixCopy, 6);
    ck_assert_int_eq(res_4, true);
    ck_assert_int_eq(matrixCopy->columns, 6);

    bool res_5 = eraseDynamicMatrixColumn(matrixCopy, 0);
    ck_assert_int_eq(res_5, true);
    ck_assert_int_eq(matrixCopy->columns, 5);

    //// Resulting matrix should look as follows:
    //// 4.76   1.01   2.51   0.0    0.01
    //// 1.25   2.02   0.009  0.0    31.14
    //// 9.01   3.03   1093.1 0.0    0.09
    //// 0.0    4.04   4.0    0.0    99.12
    //// 0.0    5.05   0.63   0.360  0.0
    //// 2.78   49.98  0.0    0.0    0.0
    //// 0.0    3.12   0.0    0.0    0.0
    //// 0.0    7.57   0.0    0.0    0.0
    //// 0.0    0.01   0.0    0.0    0.0
    //// 2.78   49.98  0.0    0.0    0.0
    //// 1.2    66.359 0.0    1.445  0.0
    //// 0.0    0.894  0.0    0.0    0.0

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 0), 4.76);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 1), 1.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 2), 2.51);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 4), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 0, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 0), 1.25);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 1), 2.02);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 2), 0.009);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 4), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 1, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 0), 9.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 1), 3.03);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 2), 1093.1);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 4), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 2, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 1), 4.04);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 2), 4.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 4), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 3, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 1), 5.05);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 2), 0.63);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 3), 0.360);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 4, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 5, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 1), 3.12);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 6, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 1), 7.57);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 7, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 1), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 8, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 0), 2.78);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 1), 49.98);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 9, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 0), 1.2);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 1), 66.359);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 3), 1.445);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 10, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 1), 0.894);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 11, 5), -999);

    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(matrixCopy, 12, 5), -999);

    freeDynamicArr(arr0);
    freeDynamicArr(arr1);
    freeDynamicArr(arr2);
    freeDynamicArr(arr3);

    freeDynamicMatrix(matrixCopy);

    // New matrix

    DynamicMatrix *newMatrix = createDynamicMatrix();
    ck_assert_ptr_nonnull(newMatrix);

    ck_assert_int_eq(newMatrix->rows, 0);
    ck_assert_int_eq(newMatrix->columns, 0);

    bool res_6 = eraseDynamicMatrixRow(newMatrix, 0);
    bool res_7 = eraseDynamicMatrixColumn(newMatrix, 0);
    ck_assert_int_eq(res_6, false);
    ck_assert_int_eq(res_7, false);

    ck_assert_int_eq(newMatrix->rows, 0);
    ck_assert_int_eq(newMatrix->columns, 0);

    bool res_8 = insertDynamicMatrixRow(newMatrix, 0, arr5);
    bool res_9 = insertDynamicMatrixColumn(newMatrix, 0, arr4);

    ck_assert_int_eq(res_8, true);
    ck_assert_int_eq(res_9, true);

    // The resulting matrix should be:
    // 2.14     0.01  31.14  0.09   99.12  0.0  0.0
    // 5.1      0.0   0.0    0.0    0.0    0.0  0.0
    // 0.02     0.0   0.0    0.0    0.0    0.0  0.0
    // 0.79     0.0   0.0    0.0    0.0    0.0  0.0
    // 99.99    0.0   0.0    0.0    0.0    0.0  0.0
    // 59238.39 0.0   0.0    0.0    0.0    0.0  0.0

    ck_assert_int_eq(newMatrix->rows, 6);
    ck_assert_int_eq(newMatrix->columns, 7);

    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 0), 2.14);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 1), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 2), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 3), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 4), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 0, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 0), 5.1);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 1, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 0), 0.02);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 2, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 0), 0.79);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 3, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 0), 99.99);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 4, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 0), 59238.39);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 6), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 5, 7), -999);

    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 6), -999);
    ck_assert_double_eq(getDynamicMatrixElement(newMatrix, 6, 7), -999);

    DynamicMatrix *newMatrixCopy = createDynamicMatrix();
    bool res_10 = copyDynamicMatrix(newMatrixCopy, newMatrix);
    ck_assert_int_eq(res_10, true);

    bool res_11 = eraseDynamicMatrixColumn(newMatrix, 7);
    ck_assert_int_eq(res_11, false);

    bool res_12 = eraseDynamicMatrixColumn(newMatrix, 6);
    ck_assert_int_eq(res_12, true);

    ck_assert_int_eq(newMatrix->rows, 6);
    ck_assert_int_eq(newMatrix->columns, 6);

    for (int i = 0; i < 6; i++)
    {
        bool res_13 = eraseDynamicMatrixColumn(newMatrix, 0);
        ck_assert_int_eq(res_13, true);
    }
    ck_assert_int_eq(newMatrix->columns, 0);
    ck_assert_int_eq(newMatrix->rows, 0);

    bool res_14 = eraseDynamicMatrixColumn(newMatrix, 0);
    ck_assert_int_eq(res_14, false);

    // newMatrixCopy
    ck_assert_int_eq(newMatrixCopy->rows, 6);
    ck_assert_int_eq(newMatrixCopy->columns, 7);

    bool res_15 = eraseDynamicMatrixRow(newMatrixCopy, 0);
    ck_assert_int_eq(res_15, true);

    ck_assert_int_eq(newMatrixCopy->rows, 5);
    ck_assert_int_eq(newMatrixCopy->columns, 7);

    for (int i = 0; i < 5; i++)
    {
        bool res_16 = eraseDynamicMatrixRow(newMatrixCopy, 0);
        ck_assert_int_eq(res_16, true);
    }

    ck_assert_int_eq(newMatrixCopy->columns, 0);
    ck_assert_int_eq(newMatrixCopy->rows, 0);

    bool res_17 = eraseDynamicMatrixRow(newMatrix, 0);
    ck_assert_int_eq(res_17, false);

    freeDynamicMatrix(newMatrix);
    freeDynamicMatrix(newMatrixCopy);

    // Last matrix

    DynamicMatrix *lastMatrix = createDynamicMatrix();

    bool res_18 = insertDynamicMatrixColumn(lastMatrix, 0, arr5);
    bool res_19 = insertDynamicMatrixRow(lastMatrix, 0, arr4);

    freeDynamicArr(arr4);
    freeDynamicArr(arr6);

    ck_assert_int_eq(res_18, true);
    ck_assert_int_eq(res_19, true);

    // The resulting matrix should be:
    // 2.14     5.1   0.02   0.79   99.99  59238.39
    // 0.01     0.0   0.0    0.0    0.0    0.0
    // 31.14    0.0   0.0    0.0    0.0    0.0
    // 0.09     0.0   0.0    0.0    0.0    0.0
    // 99.12    0.0   0.0    0.0    0.0    0.0
    // 0.0      0.0   0.0    0.0    0.0    0.0
    // 0.0      0.0   0.0    0.0    0.0    0.0

    ck_assert_int_eq(lastMatrix->rows, 7);
    ck_assert_int_eq(lastMatrix->columns, 6);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 0, 0), 2.14);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 0, 1), 5.1);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 0, 2), 0.02);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 0, 3), 0.79);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 0, 4), 99.99);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 0, 5), 59238.39);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 0, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 1, 0), 0.01);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 1, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 1, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 1, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 1, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 1, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 1, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 2, 0), 31.14);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 2, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 2, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 2, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 2, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 2, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 2, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 3, 0), 0.09);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 3, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 3, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 3, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 3, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 3, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 3, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 4, 0), 99.12);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 4, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 4, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 4, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 4, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 4, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 4, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 5, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 5, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 5, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 5, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 5, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 5, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 5, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 6, 0), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 6, 1), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 6, 2), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 6, 3), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 6, 4), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 6, 5), 0.0);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 6, 6), -999);

    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 7, 0), -999);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 7, 1), -999);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 7, 2), -999);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 7, 3), -999);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 7, 4), -999);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 7, 5), -999);
    ck_assert_double_eq(getDynamicMatrixElement(lastMatrix, 7, 6), -999);

    freeDynamicMatrix(lastMatrix);
}
END_TEST

#endif //DYNAMIC_MATRIX_TEST_H
