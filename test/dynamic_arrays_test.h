#ifndef DYNAMIC_ARRAYS_TEST_H
#define DYNAMIC_ARRAYS_TEST_H

#include <stdlib.h>
#include <check.h>

#include "../src/utils/dynamicarray.h"

START_TEST(dynamicArrTest)
{
    DynamicArray *arr1 = createDynamicArr();

    pushBackDynamicArr(arr1, 3.0);
    pushBackDynamicArr(arr1, 1.74);
    pushBackDynamicArr(arr1, 5.234);
    pushBackDynamicArr(arr1, 7.33873);
    pushBackDynamicArr(arr1, 2.1);
    pushBackDynamicArr(arr1, 0.0);
    pushBackDynamicArr(arr1, 113334.0);
    pushBackDynamicArr(arr1, 0.0018);

    ck_assert_int_eq(getDynamicArrSize(arr1), 8);

    ck_assert_double_eq(getDynamicArrElement(arr1, 0), 3.0);
    ck_assert_double_eq(getDynamicArrElement(arr1, 1), 1.74);
    ck_assert_double_eq(getDynamicArrElement(arr1, 2), 5.234);
    ck_assert_double_eq(getDynamicArrElement(arr1, 3), 7.33873);
    ck_assert_double_eq(getDynamicArrElement(arr1, 4), 2.1);
    ck_assert_double_eq(getDynamicArrElement(arr1, 5), 0.0);
    ck_assert_double_eq(getDynamicArrElement(arr1, 6), 113334.0);
    ck_assert_double_eq(getDynamicArrElement(arr1, 7), 0.0018);

    setDynamicArrElement(arr1, 4, 0.14);

    ck_assert_double_eq(getDynamicArrElement(arr1, 0), 3.0);
    ck_assert_double_eq(getDynamicArrElement(arr1, 1), 1.74);
    ck_assert_double_eq(getDynamicArrElement(arr1, 2), 5.234);
    ck_assert_double_eq(getDynamicArrElement(arr1, 3), 7.33873);
    ck_assert_double_eq(getDynamicArrElement(arr1, 4), 0.14);
    ck_assert_double_eq(getDynamicArrElement(arr1, 5), 0.0);
    ck_assert_double_eq(getDynamicArrElement(arr1, 6), 113334.0);
    ck_assert_double_eq(getDynamicArrElement(arr1, 7), 0.0018);

    DynamicArray *arr2 = createDynamicArr();

    {
        // stack-allocated array, verify after scope ends
        double row[6] = { 3.21, 5.0, 0.019, 7.79, 0.0, 744.1 };
        setDynamicArrRow(arr2, row, 6);
    }

    ck_assert_double_eq(getDynamicArrElement(arr2, 0), 3.21);
    ck_assert_double_eq(getDynamicArrElement(arr2, 1), 5.0);
    ck_assert_double_eq(getDynamicArrElement(arr2, 2), 0.019);
    ck_assert_double_eq(getDynamicArrElement(arr2, 3), 7.79);
    ck_assert_double_eq(getDynamicArrElement(arr2, 4), 0.0);
    ck_assert_double_eq(getDynamicArrElement(arr2, 5), 744.1);

    copyDynamicArr(arr2, arr1);
    freeDynamicArr(arr1);

    ck_assert_int_eq(getDynamicArrSize(arr2), 8);

    ck_assert_double_eq(getDynamicArrElement(arr2, 0), 3.0);
    ck_assert_double_eq(getDynamicArrElement(arr2, 1), 1.74);
    ck_assert_double_eq(getDynamicArrElement(arr2, 2), 5.234);
    ck_assert_double_eq(getDynamicArrElement(arr2, 3), 7.33873);
    ck_assert_double_eq(getDynamicArrElement(arr2, 4), 0.14);
    ck_assert_double_eq(getDynamicArrElement(arr2, 5), 0.0);
    ck_assert_double_eq(getDynamicArrElement(arr2, 6), 113334.0);
    ck_assert_double_eq(getDynamicArrElement(arr2, 7), 0.0018);

    {
        double element = 0.0;
        double *row = (double*)calloc(5, sizeof(double));
        for (int i = 0; i < 5; i++)
        {
            row[i] = element;
            element += 0.89;
        }

        // potential memory leak? Double check! Hehe, get it? Double...? Check...?
        setDynamicArrRow(arr2, row, 5);
        free(row);
    }

    ck_assert_int_eq(getDynamicArrSize(arr2), 5);

    freeDynamicArr(arr2);
}
END_TEST

#endif // DYNAMIC_ARRAYS_TEST_H
