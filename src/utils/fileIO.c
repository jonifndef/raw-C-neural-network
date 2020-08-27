#include <stdlib.h>
#include <stdio.h>

#include "fileIO.h"

static bool getFileFormat(const char *filePath, int *rows, int *columns)
{
    FILE *fp;
    int numFieldsInRow = 0;
    int numFieldsFirstRow = 0;
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
                if (*rows == 0)
                    numFieldsFirstRow = numFieldsInRow;
                else if (numFieldsFirstRow != numFieldsInRow)
                    return false; // unmatching rows

                if (numTokensInField > 0)
                    numFieldsInRow++;
                else
                    return false; // invalid format
                *columns = numFieldsInRow;
                numFieldsInRow = 0;
                (*rows)++;
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

    printf("numfields: %d, numRows: %d\n", *columns, *rows);
    fclose(fp);

    return true;
}

//static MatrixDoubles* populateMatrix(const char *filePath,
//                                    int rows,
//                                    int columns)
//{
//    // TODO: implement
//    return NULL;
//}

bool readSampleData(const char* filePath, MatrixDoubles *data)
{
    int *rows = calloc(1, sizeof(int));
    int *columns = calloc(1, sizeof(int));
    if (!getFileFormat(filePath, rows, columns))
        return false;
    else
        return true;
}
