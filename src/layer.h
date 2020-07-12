#include "neuron.h"
#include "utils.h"

typedef struct Layer
{
    int numNeurons;
    Neuron *neurons;
    void *activationFunction; //will be a function pointer once we implement them
} Layer;

Layer* createLayer(int numNeurons, int numNeuronsPrevLayer);
void freeLayerContents(Layer *layer);
void updateWeightsAndBiasesInLayer(Layer *layer, MatrixDoubles *weights, double *biases);
MatrixDoubles* getOutputsFromLayer(Layer* layer, MatrixDoubles *inputs);
