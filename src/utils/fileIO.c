#include <stdlib.h>
#include <stdio.h>

#include "fileIO.h"

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
