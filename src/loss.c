#include "loss.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h> // debug

static int findHotIndex(const DynamicArray *classTargetsRow)
{
    for (int i = 0; i < classTargetsRow->size; i++)
    {
        if (classTargetsRow->data[i] == 1)
        {
            return i;
        }
    }

    return -1;
}

static bool verifySparseTargets(const DynamicMatrix *outputs, const DynamicArray *classTargets)
{
    printDynamicArr(classTargets);
    if (classTargets->size != outputs->rows)
    {
        return false;
    }

    for (int i = 0; i < classTargets->size; i++)
    {
        if (classTargets->data[i] >= outputs->columns)
        {
            return false;
        }
    }

    return true;
}

static bool verifyOneHotTargets(const DynamicMatrix *outputs, const DynamicMatrix *classTargets)
{
    // how do we verify the two-dimensional matrix?
    // It should only have one element set to one per row
    // same amount of rows and cols as outputRow
    if (classTargets->rows != outputs->rows || classTargets->columns != outputs->columns)
    {
        return false;
    }

    for (int i = 0; i < classTargets->rows; i++)
    {
        DynamicArray *classTargetsRow = getDynamicMatrixRowRef(classTargets, i);
        unsigned int numHot = 0; 

        for (int j = 0; j < classTargetsRow->size; j++)
        {
            if (classTargetsRow->data[j] == 1)
            {
                numHot++;
            }
        }

        if (numHot > 1)
        {
            return false;
        }
    }

    return true;
}

DynamicArray* categorialCrossEntropy(const DynamicMatrix *outputs, const DynamicMatrix *classTargets)
{
    DynamicArray *loss = createDynamicArrWithCapacity(outputs->rows);
    if (!loss)
    {
        return NULL;
    }

    // If classTargets is one-dimensional, then it's sparse (a list of the acutal correct classes, rather than it's indicies), e.g. { 5, 2, 1 }
    // On the other hand, if it's one-hot-coded, i.e. a matrix of indicies
    if (classTargets->rows == 1)
    {
        const DynamicArray *classTargetsArr = getDynamicMatrixRowRef(classTargets, 0);

        if (!verifySparseTargets(outputs, classTargetsArr))
        {
            return NULL;
        }

        for (int i = 0; i < outputs->rows; i++)
        {
            const DynamicArray *outputRow = getDynamicMatrixRowRef(outputs, i);

            double lossEntry = -(log(outputRow->data[(int)classTargetsArr->data[i]]));
            pushBackDynamicArr(loss, lossEntry);
        }
    }
    else
    {
        if (!verifyOneHotTargets(outputs, classTargets))
        {
            return NULL;
        }

        for (int i = 0; i < outputs->rows; i++)
        {
            const DynamicArray *outputRow = getDynamicMatrixRowRef(outputs, i);
            const DynamicArray *classTargetsRow = getDynamicMatrixRowRef(classTargets, i);

            // we need to know which index is set to "1"
            int hotIndex = findHotIndex(classTargetsRow);

            double lossEntry = -(log(outputRow->data[hotIndex]));
            pushBackDynamicArr(loss, lossEntry);
        }
    }

    return loss;
}
