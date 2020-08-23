#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

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

bool readSampleData(const char* filePath, MatrixDoubles *data)
{
    FILE *fp;
    int numFieldsInRow = 0;
    int numFieldsFirstRow = 0;
    int numFields = 0;
    int numRows = 0;
    int numTokensInField = 0;
    char c = '_';

    fp = fopen(filePath, "r");
    if (fp == NULL)
        return false;

    while (c != EOF)
    {
        c = getc(fp);
        if (c == ' ')
        {
            if (numTokensInField > 0)
            {
                numFieldsInRow++;
                numTokensInField = 0;
            }
            else
            {
                // it's an invalid row
                return false;
            }
        }
        else if (c == '\n')
        {
            if (numFieldsInRow > 0)
            {
                if (numRows == 0)
                    numFieldsFirstRow = numFieldsInRow;
                else if (numFieldsFirstRow != numFieldsInRow)
                    return false; // unmatching rows

                if (numTokensInField > 0)
                    numFieldsInRow++;
                else
                    return false; // invalid format
                numFields = numFieldsInRow;
                numFieldsInRow = 0;
                numRows++;
            }
            else
            {
                // it's an invalid row
                return false;
            }
        }
        else //it's a valid token
        {
            numTokensInField++;
        }
    }

    printf("numfields: %d, numRows: %d\n", numFields, numRows);
    fclose(fp);

    return true;
}
