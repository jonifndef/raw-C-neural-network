#include "dynamicmatrix.h"
#include "dynamicarray.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static bool reAllocDynamicMatrixRows(DynamicMatrix *matrix, int newRowCapacity)
{
    DynamicArray **newData = calloc(newRowCapacity, sizeof(DynamicArray));
    if (newData == NULL)
    {
        return false;
    }

    for (int i = 0; i < newRowCapacity; i++)
    {
        newData[i] = createDynamicArr();
        if (i < matrix->rowCapacity)
        {
            if (!copyDynamicArr(newData[i], matrix->data[i]))
            {
                return false;
            }
        }
    }

    freeDynamicMatrix(matrix);
    matrix->data = newData;
    matrix->rowCapacity = newRowCapacity;
    return true;
}

//static void reAllocDynamicMatrixColumns(DynamicMatrix *matrix, int newCapacity)
//{
//
//}

DynamicMatrix* createDynamicMatrix()
{
    DynamicMatrix *matrix = calloc(1, sizeof(DynamicMatrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    matrix->rows = 0;
    matrix->columns = 0;

    // a 3x4 matrix might be suitable as a default size
    // createDynamicArr() returns a dynamic array of lenght 4
    matrix->rowCapacity = 3;
    matrix->data = calloc(matrix->rowCapacity, sizeof(DynamicArray));
    if (matrix->data == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < matrix->rowCapacity; i++)
    {
        matrix->data[i] = createDynamicArr();
        if (matrix->data[i] == NULL)
        {
            return NULL;
        }
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

bool pushRow(DynamicMatrix *matrix, DynamicArray *row)
{
    // two cases:
    //  - the length of the new row is longer than the current column capacity
    //  - the current row capacity is already filled

    if (getDynamicArrSize(row) > matrix->columnCapacity)
    {
        for (int i = 0; i < matrix->rowCapacity; i++)
        {
            if (!reAllocDynamicArr(matrix->data[i], getDynamicArrSize(row)))
            {
                return false;
            }
        }
        matrix->columnCapacity = getDynamicArrSize(row);
    }

    if (matrix->rows >= matrix->rowCapacity)
    {
        if (!reAllocDynamicMatrixRows(matrix, matrix->rowCapacity + (matrix->rowCapacity / 2)))
        {
            return false;
        }
    }

    if (!copyDynamicArr(matrix->data[matrix->rows++], row))
    {
        return false;
    }

    if (getDynamicArrSize(row) > matrix->columns)
    {
        matrix->columns = getDynamicArrSize(row);
    }

    return true;
}

bool pushColumn(DynamicMatrix *matrix, DynamicArray *column)
{
    // two cases:
    //  - the length of the new column is longer than the current row capacity
    //  - the current column capacity is already filled

    if (getDynamicArrSize(column) > matrix->rowCapacity)
    {
        if (!reAllocDynamicMatrixRows(matrix, getDynamicArrSize(column)))
        {
            return false;
        }
        matrix->rowCapacity = getDynamicArrSize(column);
    }

    if (matrix->columns >= matrix->columnCapacity)
    {
        for (int i = 0; i < matrix->rows; i++)
        {
            if (!reAllocDynamicArr(matrix->data[i], getDynamicArrSize(column) + (matrix->columnCapacity / 2)))
            {
                return false;
            }
        }
        matrix->columnCapacity = getDynamicArrSize(column) + (matrix->columnCapacity / 2);
    }

    for (int i = 0; i < getDynamicArrSize(column); i++)
    {
        if (!pushBackDynamicArr(matrix->data[i], getDynamicArrElement(column, i)))
        {
            return false;
        }
    }
    matrix->columns++;

    if (getDynamicArrSize(column) > matrix->rows)
    {
        matrix->rows = getDynamicArrSize(column);
    }

    return true;
}

DynamicArray* getDynamicMatrixRow(const DynamicMatrix *matrix, int row)
{
    return (row < matrix->rows && row >= 0) ? matrix->data[row] : NULL;
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
