#include "loss.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h> // debug

DynamicArray* categorialCrossEntropy(const DynamicMatrix *outputs, const DynamicArray *classTargets)
{
    DynamicArray *loss = createDynamicArrWithCapacity(outputs->rows);
    if (!loss)
    {
        return NULL;
    }

    if (classTargets->size != outputs->rows)
    {
        return NULL;
    }

    for (int i = 0; i < outputs->rows; i++)
    {
        const DynamicArray *outputRow = getDynamicMatrixRowRef(outputs, i);

        double lossEntry = -(log(outputRow->data[(int)classTargets->data[i]]));
        pushBackDynamicArr(loss, lossEntry); 
    }

    return loss;
}
