#include "loss.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h> // debug

DynamicArray* categorialCrossEntropy(const DynamicMatrix *outputs, const uint *classTargets)
{
    DynamicArray *loss = createDynamicArrWithCapacity(outputs->rows);
    if (!loss)
    {
        return NULL;
    }

    int count = 0;
    int targetIndex = -1;
    for (int i = 0; i < outputs->rows; i++)
    {
        if (classTargets[i] < 0 || classTargets[i] > 1)
        {
            return NULL;
        }
        
        if (classTargets[i] == 1)
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

        const DynamicArray *outputRow = getDynamicMatrixRowRef(outputs, i);

        printf("hejhejehj\n");
        double lossEntry = -(log(outputRow->data[targetIndex]));
        pushBackDynamicArr(loss, lossEntry); 
    }

    return loss;
}
