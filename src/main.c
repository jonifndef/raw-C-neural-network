#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "layer.h"
#include "activationfunctions.h"
#include "loss.h"
#include "utils/dynamicarray.h"
#include "utils/dynamicmatrix.h"

int main(int argc, char *argv[])
{
    DynamicMatrix *X = createDynamicMatrix();
    DynamicMatrix *y = createDynamicMatrix();

    if (!readSampleData("/home/jonas/Development/raw-C-neural-network/nnfs_python/output_X.txt", " ", X))
    {
        printf("hej1ff\n");
    }

    if (!readSampleData("/home/jonas/Development/raw-C-neural-network/nnfs_python/output_y.txt", " ", y))
    {
        printf("dåff\n");
    }

    LayerDense *layer1 = createLayerDense(3, 1, 2, relu);
    LayerDense *layer2 = createLayerDense(3, 1, 3, softmax);

    DynamicMatrix *output1 = createDynamicMatrix();
    DynamicMatrix *output2 = createDynamicMatrix();

    // DynamicArray *newRow = createDynamicArrWithCapacity(row->capacity);
    // this newRow is NULL further down in copyDynArr
    // the newRow comes from "outputs" in forwardDense, which is the dot product of inputs and weights. Weights not initialized?


    if (!forwardDense(layer1, X))
        printf("whhops 1");

    if (!getOutputCopyFromLayerDense(layer1, output1))
        printf("whhops 2");

    if (!forwardDense(layer2, output1))
        printf("whhops 3");

    if (!getOutputCopyFromLayerDense(layer2, output2))
        printf("whhops 4");

    printDynamicMatrix(output2);
    DynamicMatrix *yTranspose = createDynamicMatrixTranspose(y);
    DynamicArray *loss = createDynamicArr();
    loss = categorialCrossEntropy(output2, yTranspose);
    //printDynamicMatrix(y);


    //printDynamicArr(loss);
    printf("mean loss: %f\n", getAvrageDynamicAarr(loss));
    return 0;
}
