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

static bool resizeExistingRows(DynamicMatrix *matrix, DynamicArray *newRow)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        // Add padding of 0.0 until all arrays are of same length
        for (int j = 0; j < (newRow->size - matrix->columns); j++)
        {
            if (!pushBackDynamicArr(matrix->data[i], 0.0))
            {
                return false;
            }
        }
    }
    return true;
}

static bool resizeNewRow(const DynamicMatrix *matrix, DynamicArray *newRow)
{
    int numElementsToPush = matrix->columns - getDynamicArrSize(newRow);
    for (int i = 0; i < numElementsToPush; i++)
    {
        if (!pushBackDynamicArr(newRow, 0.0))
        {
            return false;
        }
    }
    return true;
}

static bool resizeExistingColumns(DynamicMatrix *matrix, DynamicArray *newColumn)
{
    DynamicArray *paddingArr = createDynamicArr();
    for (int i = 0; i < matrix->columns; i++)
    {
        if (!pushBackDynamicArr(paddingArr, 0.0))
        {
            return false;
        }
    }

    int numRowsToAdd = getDynamicArrSize(newColumn) - matrix->rows;
    for (int i = 0; i < numRowsToAdd; i++)
    {
        if (!pushRow(matrix, paddingArr))
        {
            return false;
        }
    }
    free(paddingArr);
    return true;
}

static bool resizeNewColumn(DynamicMatrix *matrix, DynamicArray *newColumn)
{
    int numElementsToPush = matrix->rows - getDynamicArrSize(newColumn);
    for (int i = 0; i < numElementsToPush; i++)
    {
        if (!pushBackDynamicArr(newColumn, 0.0))
        {
            return false;
        }
    }
    return true;
}

static bool insertNewColumn(DynamicMatrix *matrix, DynamicArray *newColumn)
{
    // if empty matrix
    if (matrix->rows == 0)
    {
        DynamicArray *arr = createDynamicArr();
        for (int i = 0; i < getDynamicArrSize(newColumn); i++)
        {
            pushRow(matrix, arr);
        }
    }

    for (int i = 0; i < matrix->rows; i++)
    {
        if (!pushBackDynamicArr(getDynamicMatrixRowRef(matrix, i),
                                getDynamicArrElement(newColumn, i)))
        {
            return false;
        }
    }
    matrix->columns++;
    // U G L Y
    matrix->columnCapacity = getDynamicMatrixRowRef(matrix, 0)->capacity;
    return true;
}

DynamicMatrix* createDynamicMatrix()
{
    DynamicMatrix *matrix = calloc(1, sizeof(DynamicMatrix));
    if (matrix == NULL)
    {
        return NULL;
    }

    matrix->rows = 0;
    matrix->columns = 0;

    // a 4x4 matrix might be suitable as a default size
    // createDynamicArr() returns a dynamic array with a capacity of 4
    matrix->rowCapacity = 4;
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

    printf("=== new row size:%d, capacity: %d\n", newRow->size, newRow->capacity);
    printf("=== matrix rows: %d, rowCapacity: %d\n", matrix->rows, matrix->rowCapacity);
    printf("=== matrix columns: %d, columnCapacity: %d\n", matrix->columns, matrix->columnCapacity);

    free(newRow);
    return true;
}

bool pushColumn(DynamicMatrix *matrix, DynamicArray *column)
{
    // What if a column get pushed to an empty matrix?


    // Perform a deep copy of the new column, except its capacity
    DynamicArray *newColumn = createDynamicArr();
    for (int i = 0; i < getDynamicArrSize(column); i++)
    {
        if (!pushBackDynamicArr(newColumn, getDynamicArrElement(column, i)))
        {
            return false;
        }
    }

    if (getDynamicArrSize(newColumn) > matrix->rows)
    {
        if (!resizeExistingColumns(matrix, newColumn))
        {
            return false;
        }
    }
    else if (getDynamicArrSize(newColumn) < matrix->rows)
    {
        if (!resizeNewColumn(matrix, newColumn))
        {
            return false;
        }
    }

    if (!insertNewColumn(matrix, newColumn))
    {
        return false;
    }

    printf("=== new column size:%d, capacity: %d\n", newColumn->size, newColumn->capacity);
    printf("=== matrix rows: %d, rowCapacity: %d\n", matrix->rows, matrix->rowCapacity);
    printf("=== matrix columns: %d, columnCapacity: %d\n", matrix->columns, matrix->columnCapacity);


    return true;
}

DynamicArray* getDynamicMatrixRowRef(const DynamicMatrix *matrix, int row)
{
    return (row < matrix->rows && row >= 0) ? matrix->data[row] : NULL;
}

DynamicArray* createDynamicMatrixColumnCopy(const DynamicMatrix *matrix, int column)
{
    if (column < matrix->columns && column >= 0)
    {
        DynamicArray *array = calloc(1, sizeof(DynamicArray));
        array->data = calloc(matrix->rowCapacity, sizeof(double));
        for (int i = 0; i < matrix->rows; i++)
        {
            array->data[i] = matrix->data[i]->data[column];
        }
        array->size = matrix->rows;
        array->capacity = matrix->rowCapacity;
        return array;
    }
    return NULL;
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
    printf("\n");
}
