#ifndef LEGACY_LAYER_H_
#define LEGACY_LAYER_H_

#include "legacy_neuron.h"
#include "utils/fileIO.h"
#include "utils/matrix.h"

typedef struct LayerDense
{
    int numNeurons;
    Neuron *neurons;
    MatrixDoubles *outputs;
    void *activationFunction; //will be a function pointer once we implement them
} LayerDense;

LayerDense* createLayerDense(int numNeurons,
                             int batchSize,
                             int numNeuronsPrevLayer,
                             double (*activationFunction)(double));
void freeLayerDenseContents(LayerDense *layer);
void updateWeightsAndBiasesInLayerDense(LayerDense *layer,
                                        const MatrixDoubles *weights,
                                        const double *biases);
void forwardDense(LayerDense *layer, const MatrixDoubles *inputs);
MatrixDoubles* getOutputsFromLayerDense(const LayerDense *layer);

#endif // LEGACY_LAYER_H_
