#include "dynamicmatrix.h"

#include <stdlib.h>

static void reAllocDynamicMatrixRows(DynamicMatrix *matrix, int newRowCapacity)
{

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
    matrix->columnCapacity = 4;

    matrix->data = calloc(matrix->rowCapacity, sizeof(double));
    for (int i = 0; i < matrix->rowCapacity; i++)
    {
        matrix->data[i] = calloc(matrix->columnCapacity, sizeof(double));
    }

    return matrix;
}

void freeDynamicMatrix(DynamicMatrix *matrix)
{
    for (int i = 0; i < matrix->rowCapacity; i++)
    {
        free(matrix->data[i]);
    }
    free(matrix->data);
}
