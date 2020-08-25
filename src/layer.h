#ifndef LAYER_H_
#define LAYER_H_

#include "neuron.h"
#include "utils/fileIO.h"
#include "utils/matrix.h"

typedef struct LayerDense
{
    int numNeurons;
    Neuron *neurons;
    MatrixDoubles *outputs;
    void *activationFunction; //will be a function pointer once we implement them
} LayerDense;

LayerDense* createLayerDense(int numNeurons, int batchSize, int numNeuronsPrevLayer, double (*activationFunction)(double));
void freeLayerDenseContents(LayerDense *layer);
void updateWeightsAndBiasesInLayerDense(LayerDense *layer, MatrixDoubles *weights, double *biases);
void forwardDense(LayerDense *layer, MatrixDoubles *inputs);
MatrixDoubles* getOutputsFromLayerDense(LayerDense* layer);

#endif // LAYER_H_
