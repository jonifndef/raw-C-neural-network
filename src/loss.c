#include "loss.h"

#include <stdlib.h>

DynamicArray* categorialCrossEntropy(const DynamicMatrix *outputs, const DynamicArray *classTargets)
{
    DynamicArray *loss = createDynamicArrWithCapacity(outputs->columns);
    if (!loss)
    {
        return NULL;
    }

    if (outputs->columns != classTargets->size)
    {
        return NULL;
    }

    int count = 0;
    int targetIndex = -1;
    for (int i = 0; i < classTargets->size; i++)
    {
        if (classTargets->data[i] < 0 || classTargets->data[i] > 1)
        {
            return NULL;
        }
        
        if (classTargets->data[i] == 1)
        {
            targetIndex = i;
            count++;
        }
    }

    if (count > 1 || targetIndex == -1)
    {
        return NULL;
    }

    for (int i = 0; i < outputs->rows; i++)
    {
        //DynamicArray *outputRow = createDynamicArrWithCapacity(outputs->columns);
        //if (!outputRow)
        //{
        //    return NULL;
        //}

        DynamicArray *outputRow = getDynamicMatrixRowRef(outputs, i);
    }

    return loss;
}
