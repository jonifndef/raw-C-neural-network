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

    ck_assert_int_eq(matrix->columns, 6);

    // Insert some columns
    double column6[] = { 2.51, 0.009, 1093.1, 4.0, 0.63 };
    DynamicArray *arr6 = createDynamicArr();
    setDynamicArrRow(arr6, column6, 5);
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
    setDynamicArrRow(arr7, column7, 3);
    pushColumn(matrix, arr7);

    double column8[] = { 1.01, 2.02, 3.03, 4.04, 5.05, 2.52, 3.12, 7.57, 0.01 };
    DynamicArray *arr8 = createDynamicArr();
    setDynamicArrRow(arr8, column8, 9);
    pushColumn(matrix, arr8);

    ck_assert_int_eq(matrix->columnCapacity, getDynamicMatrixRowRef(matrix, 0)->capacity);

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

    // check the new rows after column 8!

    DynamicArray *column9 = createDynamicMatrixColumnCopy(matrix, 2);
    printDynamicArr(column9);
    setDynamicArrElement(column9, 0, 66.66);

    freeDynamicArr(column9);

    //printDynamicMatrix(matrix);
    freeDynamicMatrix(matrix);

    // ============================================== //
    //                   new matrix                   //
    // ============================================== //

    matrix = createDynamicMatrix();
    pushColumn(matrix, arr7);
    pushColumn(matrix, arr8);
    pushColumn(matrix, arr8);
    pushColumn(matrix, arr6);
    pushRow(matrix, arr3);
    printDynamicMatrix(matrix);

    freeDynamicArr(arr3);
    freeDynamicArr(arr6);
    freeDynamicArr(arr7);
    freeDynamicArr(arr8);

    pushRowElement(matrix, 4, 0.360);
    pushColumnElement(matrix, 1, 0.894);

    printDynamicMatrix(matrix);
}
END_TEST

#endif //DYNAMIC_MATRIX_TEST_H

