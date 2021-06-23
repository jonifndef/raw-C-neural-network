#include <stdlib.h>
#include "activationfunctions.h"

DynamicMatrix* relu(DynamicMatrix *input)
{
    for (int i = 0; i < input->rows; i++)
    {
        for (int j = 0; j < input->columns; j++)
        {
            double element = getDynamicMatrixElement(input, i, j);         
            if (!setDynamicMatrixElement(input, i, j, 
                                         (element > 0) ? element : 0.0))
            {
                return NULL;
            }
        }
    }
    
    return input;
}

DynamicMatrix* linear(DynamicMatrix *input)
{
    return input;
}
