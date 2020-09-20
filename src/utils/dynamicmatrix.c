#include "dynamicmatrix.h"
#include "dynamicarray.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void reAllocDynamicMatrixRows(DynamicMatrix *matrix, int newRowCapacity)
{
    matrix->data = realloc(matrix->data, newRowCapacity);
    matrix->rowCapacity = newRowCapacity;
}

// Todo: call the dynamicArr instance, right?
static void reAllocDynamicArr(DynamicArray *array, int newCapacity)
{
    double *newData = calloc(newCapacity, sizeof(double));
    memcpy(newData, array->data, array->size * sizeof(double));

    array->capacity = newCapacity;
    free(array->data);

    array->data = newData;
}

//static void reAllocDynamicMatrixColumn(int newCapacity)
//{
//
//}

DynamicMatrix* createDynamicMatrix()
{
    DynamicMatrix *matrix = calloc(1, sizeof(DynamicMatrix));
    matrix->rows = 0;
    matrix->columns = 0;

    // a 3x4 matrix might be suitable as a default size
    // createDynamicArr() returns a dynamic array of lenght 4
    matrix->rowCapacity = 3;
    matrix->data = calloc(matrix->rowCapacity, sizeof(DynamicArray));
    for (int i = 0; i < matrix->rowCapacity; i++)
    {
        matrix->data[i] = createDynamicArr();
    }
    // ugly?
    matrix->columnCapacity = matrix->data[0]->capacity;

    return matrix;
}

void freeDynamicMatrix(DynamicMatrix *matrix)
{
    for (int i = 0; i < matrix->rowCapacity; i++)
    {
        freeDynamicArr(matrix->data[i]);
    }
    free(matrix->data);
}

void pushRow(DynamicMatrix *matrix, DynamicArray *row)
{
    // Todo: make a function out of this!
    if (getDynamicArrSize(row) > matrix->columnCapacity)
    {
        for (int i = 0; i < matrix->rowCapacity; i++)
        {
            reAllocDynamicArr(matrix->data[i], getDynamicArrSize(row));
        }
        matrix->columnCapacity = getDynamicArrSize(row);
    }

    printDynamicArr(matrix->data[0]);
    if (matrix->rows >= matrix->rowCapacity)
    {
        reAllocDynamicMatrixRows(matrix, matrix->rowCapacity + (matrix->rowCapacity / 2));
    }

    copyDynamicArr(matrix->data[matrix->rows++], row);
}

void printDynamicMatrix(DynamicMatrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < getDynamicArrSize(matrix->data[i]); j++)
        {
            printf("%.3f ", getDynamicArrElement(matrix->data[i], j));
        }
        printf("\n");
    }
}
