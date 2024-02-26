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

    ck_assert_ptr_nonnull(X);
    ck_assert_ptr_nonnull(y);

    bool ret = false;

    ret = readSampleData("../nnfs_python/output_X.txt", " ", X);
    ck_assert_int_eq(ret, 1);

    ret = readSampleData("../nnfs_python/output_y.txt", " ", y);
    ck_assert_int_eq(ret, 1);

    LayerDense *layer1 = createLayerDense(3, 1, 2, relu);
    LayerDense *layer2 = createLayerDense(3, 1, 3, softmax);

    ck_assert_ptr_nonnull(layer1);
    ck_assert_ptr_nonnull(layer2);

    DynamicMatrix *output1 = createDynamicMatrix();
    DynamicMatrix *output2 = createDynamicMatrix();

    ck_assert_ptr_nonnull(output1);
    ck_assert_ptr_nonnull(output2);

    ret = forwardDense(layer1, X);
    ck_assert_int_eq(ret, 1);

    ret = getOutputCopyFromLayerDense(layer1, output1);
    ck_assert_int_eq(ret, 1);

    ret = forwardDense(layer2, output1);
    ck_assert_int_eq(ret, 1);

    ret = getOutputCopyFromLayerDense(layer2, output2);
    ck_assert_int_eq(ret, 1);

    DynamicArray *loss = createDynamicArr();
    ck_assert_ptr_nonnull(loss);

    DynamicMatrix *yTranspose = createDynamicMatrixTranspose(y);
    ck_assert_ptr_nonnull(yTranspose);
    ck_assert_int_eq(yTranspose->rows, 1);
    ck_assert_int_eq(yTranspose->columns, 300);

    loss = categorialCrossEntropy(output2, yTranspose);
    ck_assert_int_eq(loss->size, 300);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 0, 0), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 0, 0), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 0, 1), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 0, 1), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 0, 2), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 0, 2), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 1, 0), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 1, 0), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 1, 1), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 1, 1), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 1, 2), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 1, 2), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 2, 0), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 2, 0), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 2, 1), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 2, 1), 0.35);

    ck_assert_float_gt(getDynamicMatrixElement(output2, 2, 2), 0.32);
    ck_assert_float_lt(getDynamicMatrixElement(output2, 2, 2), 0.35);

    ck_assert_float_gt(getAvrageDynamicAarr(loss), 1.07);
    ck_assert_float_lt(getAvrageDynamicAarr(loss), 1.17);
}
END_TEST

#endif // LOSS_WITH_SPIRAL_DATA_TEST_H
