#include "dynamicmatrix.h"

#include <stdlib.h>

static void reAllocDynamicMatrixRows(DynamicMatrix *matrix, int newRowCapacity)
{
    matrix->data = realloc(matrix->data, newRowCapacity);

}

static void reAllocDynamicMatrixColumn(int newCapacity)
{

}

DynamicMatrix* createDynamicMatrix()
{
    DynamicMatrix *matrix = calloc(1, sizeof(DynamicMatrix));
    matrix->rows = 0;
    matrix->columns = 0;

    // a 3x4 matrix might be suitable as a default size
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
    if (matrix->rows >= matrix->rowCapacity)
    {
        reAllocDynamicMatrixRows(matrix, matrix->rowCapacity + (matrix->rowCapacity / 2));
    }
}
