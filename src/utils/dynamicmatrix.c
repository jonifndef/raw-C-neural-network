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

static bool resizeExistingRows(DynamicMatrix *matrix, DynamicArray *row)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        // Add padding of 0.0 until all arrays are of same length
        for (int j = 0; j < (row->size - matrix->columns); j++)
        {
            if (!pushBackDynamicArr(matrix->data[i], 0.0))
            {
                return false;
            }
        }
    }
    return true;
}

static bool resizeNewRow(const DynamicMatrix *matrix, DynamicArray *row)
{
    int numElementsToPush = matrix->columns - getDynamicArrSize(row);
    for (int i = 0; i < numElementsToPush; i++)
    {
        if (!pushBackDynamicArr(row, 0.0))
        {
            return false;
        }
    }
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
    // Perform a deep copy of the new row, except its capacity
    DynamicArray *newRow = createDynamicArr();
    for (int i = 0; i < getDynamicArrSize(row); i++)
    {
        if (!pushBackDynamicArr(newRow, getDynamicArrElement(row, i)))
        {
            return false;
        }
    }

    if (getDynamicArrSize(newRow) > matrix->columns)
    {
        if (!resizeExistingRows(matrix, newRow))
        {
            return false;
        }
    }
    else if (getDynamicArrSize(newRow) < matrix->columns)
    {
        if (!resizeNewRow(matrix, newRow))
        {
            return false;
        }
    }

    if (matrix->rows >= matrix->rowCapacity)
    {
        if (!reAllocDynamicMatrixRows(
            matrix, matrix->rowCapacity + (matrix->rowCapacity / 2)))
        {
            return false;
        }
    }

    if (!copyDynamicArr(matrix->data[matrix->rows++], newRow))
    {
        return false;
    }

    // this should always be valid since we update the size and capacity of the new row everytime
    matrix->columns = newRow->size;
    matrix->columnCapacity = newRow->capacity;

    free(newRow);
    return true;
}

bool pushColumn(DynamicMatrix *matrix, DynamicArray *column)
{
    if (getDynamicArrSize(column) > matrix->rows)
    {
        DynamicArray *row = createDynamicArr();
        if (row == NULL)
        {
            return false;
        }

        for (int j = 0; j < matrix->columns; j++)
        {
            if (!pushBackDynamicArr(row, 0.0))
            {
                return false;
            }
        }

        for (int i = 0; i < (getDynamicArrSize(column) - matrix->rows); i++)
        {
            pushRow(matrix, row);
        }
        freeDynamicArr(row);

        reAllocDynamicArr(column, matrix->rowCapacity); // this is a weird solution to the problem below, but it needs to be implemented for the pushRow-function
        // FIXME: rowCapacity will get updated dynamically here, so it won't match the capacity of the 'column' dynamic arr!
    }
    else if (getDynamicArrSize(column) < matrix->rows)
    {
        for (int i = 0; i < (matrix->rows - getDynamicArrSize(column)); i++)
        {
            pushBackDynamicArr(column, 0.0);
        }
    }

    if (getDynamicArrSize(column) > matrix->rows)
    {
        matrix->rows = getDynamicArrSize(column);
    }

    if (getDynamicArrSize(column) > matrix->columnCapacity)
    {

    }

    //insert the column here

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
        //return 0.0;
        return -999;
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
