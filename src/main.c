#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "layer.h"
#include "activationfunctions.h"
#include "utils/dynamicarray.h"
#include "utils/dynamicmatrix.h"

int main(int argc, char *argv[])
{
    DynamicMatrix *matrix = createDynamicMatrix();

    double row0[] = { 3.24, 1.2, 66.359, 7.0, 0.0, 1.445 };
    DynamicArray *arr0 = createDynamicArr();
    setDynamicArrRow(arr0, row0, 6);
    pushRow(matrix, arr0);
    freeDynamicArr(arr0);

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

    DynamicArray *arr4 = calloc(1, sizeof(DynamicArray));

    // Make sure the content of the second row of the matrix
    // is the same as its 'source array'
    copyDynamicArr(arr4, getDynamicMatrixRowRef(matrix, 1));


    freeDynamicArr(arr1);

    DynamicArray *arr5 = calloc(1, sizeof(DynamicArray));

    // Make sure that the length of the third row of the matrix
    // is longer than its 'source array', since the row should be padded with zeroes
    copyDynamicArr(arr5, getDynamicMatrixRowRef(matrix, 2));
    freeDynamicArr(arr2);

    freeDynamicArr(arr4);
    freeDynamicArr(arr5);


    // Test if you can edit elements in-place with the "getDynMatRowRef"-function
    setDynamicArrElement(getDynamicMatrixRowRef(matrix, 1), 1, 4.33);

    printDynamicMatrix(matrix);


    // Insert some columns
    double column6[] = { 2.51, 0.009, 1093.1, 4.0, 0.63 };
    DynamicArray *arr6 = createDynamicArr();
    setDynamicArrRow(arr6, column6, 5);
    pushColumn(matrix, arr6);
    pushColumn(matrix, arr6);
    pushColumn(matrix, arr6);


    double column7[] = { 4.76, 1.25, 9.01 };
    DynamicArray *arr7 = createDynamicArr();
    setDynamicArrRow(arr7, column7, 3);
    pushColumn(matrix, arr7);


    double column8[] = { 1.01, 2.02, 3.03, 4.04, 5.05, 2.52, 3.12, 7.57, 0.01 };
    DynamicArray *arr8 = createDynamicArr();
    setDynamicArrRow(arr8, column8, 9);
    pushColumn(matrix, arr8);


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

    freeDynamicArr(arr9);

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
    pushColumn(matrix, arr7); //3
    pushColumn(matrix, arr8); //9
    pushColumn(matrix, arr8); //9
    pushColumn(matrix, arr6); //5
    pushRow(matrix, arr3); //3
    printDynamicMatrix(matrix);

    // 10x4
    //
    // arr7: 4.76, 1.25, 9.01
    // arr8: 1.01, 2.02, 3.03, 4.04, 5.05, 2.52, 3.12, 7.57, 0.01
    // arr6: 2.51, 0.009, 1093.1, 4.0, 0.63
    // arr3: 2.78, 49.98, 2.30

    freeDynamicArr(arr3);
    freeDynamicArr(arr6);
    freeDynamicArr(arr7);
    freeDynamicArr(arr8);

    DynamicMatrix *matrixCopy = createDynamicMatrix();
    copyDynamicMatrix(matrixCopy, matrix);

    pushRowElement(matrix, 4, 0.360);
    pushColumnElement(matrix, 1, 0.894);

    printDynamicMatrix(matrix);

    return 0;

    srand(time(0));

    int numNeuronsPrevLayer = 4;
    int numNeuronsLayer = 3;
    int batchSize = 3;

    double biases[3] = { 2, 3, 0.5 };
    double biases2[3] = { -1, 2, -0.5 };

    // weights matrix
    double weightsRow1[] = { 0.2, 0.8, -0.5, 1.0 };
    double weightsRow2[] = { 0.5, -0.91, 0.26, -0.5 };
    double weightsRow3[] = { -0.26, -0.27, 0.17, 0.87 };

    MatrixDoubles *weights = createMatrixDoubles(numNeuronsLayer, numNeuronsPrevLayer);
    setMatrixDoublesRow(weights, 0, weightsRow1);
    setMatrixDoublesRow(weights, 1, weightsRow2);
    setMatrixDoublesRow(weights, 2, weightsRow3);

    double weights2Row1[] = { 0.1, -0.14, 0.5 };
    double weights2Row2[] = { -0.5, 0.12, -0.33 };
    double weights2Row3[] = { -0.44, 0.73, -0.13 };

    MatrixDoubles *weights2 = createMatrixDoubles(numNeuronsLayer, numNeuronsLayer);
    setMatrixDoublesRow(weights2, 0, weights2Row1);
    setMatrixDoublesRow(weights2, 1, weights2Row2);
    setMatrixDoublesRow(weights2, 2, weights2Row3);

    // inputs matrix
    double inputs1[] = { 1, 2, 3, 2.5 };
    double inputs2[] = { 2.0, 5.0, -1.0, 2.0 };
    double inputs3[] = { -1.5, 2.7, 3.3, -0.8 };

    MatrixDoubles *inputs = createMatrixDoubles(batchSize, numNeuronsPrevLayer);
    setMatrixDoublesRow(inputs, 0, inputs1);
    setMatrixDoublesRow(inputs, 1, inputs2);
    setMatrixDoublesRow(inputs, 2, inputs3);

    // output matrix
    MatrixDoubles *outputs1 = createMatrixDoubles(batchSize, numNeuronsLayer);
    MatrixDoubles *outputs2 = createMatrixDoubles(batchSize, numNeuronsLayer);

    LayerDense *layer1 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsPrevLayer, relu);
    updateWeightsAndBiasesInLayerDense(layer1, weights, biases);

    LayerDense *layer2 = createLayerDense(numNeuronsLayer, batchSize, numNeuronsLayer, relu);
    updateWeightsAndBiasesInLayerDense(layer2, weights2, biases2);

    forwardDense(layer1, inputs);
    outputs1 = getOutputsFromLayerDense(layer1);

    printf("=== Output form layer 1: ===\n");
    for (int i = 0; i < batchSize; i++)
    {
        for (int j = 0; j < numNeuronsLayer; j++)
        {
            double element = getMatrixDoublesElement(outputs1, i, j);
            printf("%.4f ", element);
        }
        printf("\n");
    }

    printf("\n");

    forwardDense(layer2, outputs1);
    outputs2 = getOutputsFromLayerDense(layer2);

    printf("=== Output form layer 2: ===\n");
    for (int i = 0; i < batchSize; i++)
    {
        for (int j = 0; j < numNeuronsLayer; j++)
        {
            double element = getMatrixDoublesElement(outputs2, i, j);
            printf("%.4f ", element);
        }
        printf("\n");
    }
    freeMatrixDoublesContents(outputs1);
    freeMatrixDoublesContents(outputs2);

    freeLayerDenseContents(layer1);
    freeLayerDenseContents(layer2);

    return 0;
}

// Correct answers for layer 1:
//      4.8,     1.21,     2.385
//      8.9,    -1.81,     0.2
//      1.41,    1.051,    0.026

// Correct answers for layer 2:
//      0.5031, -1.04185, -2.03875
//      0.2434, -2.7332,  -5.7633
//     -0.99314, 1.41254, -0.35655
