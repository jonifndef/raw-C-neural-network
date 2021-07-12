#include <stdlib.h>
#include <math.h>

#include "activationfunctions.h"

static const double E = 2.71828182846;

bool relu(DynamicMatrix *input)
{
    for (int i = 0; i < input->rows; i++)
    {
        for (int j = 0; j < input->columns; j++)
        {
            double element = getDynamicMatrixElement(input, i, j);
            if (!setDynamicMatrixElement(input, i, j,
                                         (element > 0) ? element : 0.0))
            {
                return false;
            }
        }
    }

    return true;
}

bool linear(DynamicMatrix *input)
{
    return true;
}

bool softmax(DynamicMatrix *input)
{
    // One row is one batch
    // The length of a row represents the number of neurons in the layer

    //DynamicMatrix *calcMatrix = createDynamicMatrixWithCapacity(input->rowCapacity,
    //                                                            input->columnCapacity);
    //if (!calcMatrix)
    //{
    //    return false;
    //}

    double batchSum = 0;
    for (int i = 0; i < input->rows; i++)
    {
        DynamicArray *row = getDynamicMatrixRowRef(input, i);
        double maxValue = getMaxElementDynamicArr(row);
        subtractFromAllElementsDynamicArr(row, maxValue);

        for (int j = 0; j < input->columns; j++)
        {
            double element = pow(E, getDynamicMatrixElement(input, i, j));
            if (!setDynamicMatrixElement(input, i, j, element))
            {
                return false;
            }

            batchSum += element;
        }

        for (int j = 0; j < input->columns; j++)
        {
            double element = getDynamicMatrixElement(input, i, j);
            if (!setDynamicMatrixElement(input, i, j, element / batchSum))
            {
                return false;
            }

            batchSum += element;
        }

        batchSum = 0;
    }

    return true;
}
