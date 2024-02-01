#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "fileIO.h"

static bool firstRow = true;

static bool validateConversion(double *element, char *eptr, char *token)
{
    if (*element == 0 && (errno != 0 || eptr == token))
    {
        return false;
    }

    // special case where the first char is valid, but subsequent ones are not
    if (*eptr != '\n')
    {
        if (strcmp(eptr, ""))
        {
            return false;
        }
    }
    return true;
}

static bool validateRowLength(const DynamicArray *row)
{
    static int firstRowLength = 0;

    if (firstRow)
    {
        firstRowLength = row->size;
        firstRow = false;
    }
    else
    {
        if (row->size != firstRowLength)
        {
            return false;
        }
    }

    return true;
}

static bool readLines(FILE *fp, char *line, const char *delimiter, DynamicMatrix *data)
{
    int numCharsRead = 0;
    size_t numBytesAllocated = 0;

    numCharsRead = getline(&line, &numBytesAllocated, fp);

    double element = 0.0;
    char *eptr;

    while (numCharsRead != -1)
    {
        char *token = strtok(line, delimiter);

        DynamicArray *row = createDynamicArr();
        if (!row)
        {
            return false;
        }

        while (token != NULL)
        {
            element = strtod(token, &eptr);

            if (!validateConversion(&element, eptr, token))
            {
                return false;
            }

            if (!pushBackDynamicArr(row, element))
            {
                return false;
            }

            token = strtok(NULL, delimiter);
        }

        if (!validateRowLength(row))
        {
            return false;
        }

        if (!pushRow(data, row, DO_TAKE_OWNERSHIP))
        {
            return false;
        }

        numCharsRead = getline(&line, &numBytesAllocated, fp);
    }
    return true;
}

bool readSampleData(const char *filePath,
                    const char *delimiter,
                    DynamicMatrix *data)
{
    FILE *fp;
    fp = fopen(filePath, "r");

    if (!fp)
    {
        return false;
    }

    char *line = NULL;
    bool success = readLines(fp, line, delimiter, data);

    free(line);
    fclose(fp);

    firstRow = true;

    return success;
}
