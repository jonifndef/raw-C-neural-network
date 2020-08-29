#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

MatrixDoubles* createMatrixDoubles(int numRows, int numColumns)
{
    MatrixDoubles *matrix = calloc(1, sizeof(MatrixDoubles));
    matrix->rows = numRows;
    matrix->columns = numColumns;
    matrix->data = calloc(numRows, sizeof(double*));
    for (int i = 0; i < numRows; i++)
    {
        matrix->data[i] = calloc(numColumns, sizeof(double));
    }
    return matrix;
}

void freeMatrixDoublesContents(MatrixDoubles *matrix)
{
    for(int i = 0; i < matrix->rows; i++)
    {
        free(matrix->data[i]);
    }
    free(matrix->data);
}

// Warning, length of data must be the same as num columns in matrix
void setMatrixDoublesRow(MatrixDoubles *matrix, int row, double *data)
{
    for (int i = 0; i < matrix->columns; i++)
    {
        matrix->data[row][i] = data[i];
    }
}

void setMatrixDoubelsColumn(MatrixDoubles *matrix, int column, double *data)
{

}

double* getMatrixDoublesRow(const MatrixDoubles *matrix, int row)
{
    return matrix->data[row];
}

double getMatrixDoublesElement(const MatrixDoubles *matrix, int row, int column)
{
    return matrix->data[row][column];
}

//-----------------------------------------------------------------------------

static void reAllocDynamicMatrixRows(DynamicMatrix *matrix, int newRowCapacity)
{
    double **newData = calloc(newRowCapacity, sizeof(double));
    for (int i = 0; i < newRowCapacity; i++)
    {
        newData[i] = calloc(matrix->columnCapacity, sizeof(double));
    }

    for (int i = 0; i < matrix->rows; i++)
    {
        newData[i] = matrix->data[i];
    }

    freeDynamicMatrix(matrix);
    matrix->rowCapacity = newRowCapacity;
    matrix->data = newData;
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
