#include "dynamicmatrix.h"
#include "dynamicarray.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void reAllocDynamicMatrixRows(DynamicMatrix *matrix, int newRowCapacity)
{
    DynamicArray **newData = calloc(newRowCapacity, sizeof(DynamicArray));
    for (int i = 0; i < newRowCapacity; i++)
    {
        newData[i] = createDynamicArr();
        if (i < matrix->rowCapacity)
        {
            copyDynamicArr(newData[i], matrix->data[i]);
        }
    }
    freeDynamicMatrix(matrix);
    matrix->data = newData;
    matrix->rowCapacity = newRowCapacity;
}

//static void reAllocDynamicMatrixColumns(DynamicMatrix *matrix, int newCapacity)
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
    // two cases:
    //  - the length of the new row is longer than the current column capacity
    //  - the current row capacity is already filled

    if (getDynamicArrSize(row) > matrix->columnCapacity)
    {
        for (int i = 0; i < matrix->rowCapacity; i++)
        {
            reAllocDynamicArr(matrix->data[i], getDynamicArrSize(row));
        }
        matrix->columnCapacity = getDynamicArrSize(row);
    }

    if (matrix->rows >= matrix->rowCapacity)
    {
        reAllocDynamicMatrixRows(matrix, matrix->rowCapacity + (matrix->rowCapacity / 2));
    }

    copyDynamicArr(matrix->data[matrix->rows++], row);
    if (getDynamicArrSize(row) > matrix->columns)
    {
        matrix->columns = getDynamicArrSize(row);
    }
}

double getDynamicMatrixElement(const DynamicMatrix *matrix, int row, int column)
{
    if ((row >= 0 && row <= matrix->rows) &&
        (column >= 0 && column <= matrix->columns))
    {
        return getDynamicArrElement(matrix->data[row], column);
    }
    else
    {
        // Hmm...? How to do this in a nicer way? O_o
        return 0.0;
    }
}

void printDynamicMatrix(DynamicMatrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            printf("%.3f ", matrix->data[i]->data[j]);
        }
        printf("\n");
    }
}
