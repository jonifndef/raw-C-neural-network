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

double* getMatrixDoublesRow(MatrixDoubles *matrix, int row)
{
    return matrix->data[row];
}

double getMatrixDoublesElement(MatrixDoubles *matrix, int row, int column)
{
    return matrix->data[row][column];
}
