#ifndef LAYER_H_
#define LAYER_H_

#include "neuron.h"
#include "utils/fileIO.h"
#include "utils/dynamicmatrix.h"

typedef struct LayerDense
{
    int numNeurons;
    Neuron *neurons;
    DynamicMatrix *outputs;
    void *activationFunction; //will be a function pointer once we implement them
} LayerDense;

LayerDense* createLayerDense(int numNeurons,
                             int batchSize,
                             int numNeuronsPrevLayer,
                             double (*activationFunction)(double));
void freeLayerDenseContents(LayerDense *layer);
void updateWeightsAndBiasesInLayerDense(LayerDense *layer,
                                        const DynamicMatrix *weights,
                                        const double *biases);
bool forwardDense(LayerDense *layer,
                  const DynamicMatrix *inputs);
DynamicMatrix* getOutputsFromLayerDense(const LayerDense *layer);

#endif // LAYER_H_
