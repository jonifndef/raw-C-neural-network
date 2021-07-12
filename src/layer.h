#ifndef LAYER_H_
#define LAYER_H_

#include "neuron.h"
#include "utils/fileIO.h"
#include "utils/dynamicmatrix.h"

typedef struct LayerDense
{
    int numNeurons; // Needed as an explicit field?
    double* biases;
    DynamicMatrix *weights;
    DynamicMatrix *outputs;
    bool (*activationFunction)(DynamicMatrix*);
} LayerDense;

LayerDense* createLayerDense(uint numNeurons,
                             uint batchSize,
                             uint numInputs,
                             bool (*activationFunction)(DynamicMatrix*));
void freeLayerDenseContents(LayerDense *layer);
bool updateWeightsAndBiasesInLayerDense(LayerDense *layer,
                                        const DynamicMatrix *weights,
                                        const double *biases);
bool forwardDense(LayerDense *layer,
                  const DynamicMatrix *inputs);
DynamicMatrix* getOutputsFromLayerDense(const LayerDense *layer);

#endif // LAYER_H_
