#include "neuron.h"

typedef struct Layer
{
    int numNeurons;
    Neuron *neurons;
    void *activationFunction; //will be a function pointer once we implement them
    double *outputs;
} Layer;

Layer* createLayer(int numNeurons, int numNeuronsPrevLayer);
void freeLayerContents(Layer *layer);
void updateNeuronsInLayer(Layer *layer, double *inputs, double weights[3][4], double *biases);
double* getLayerOutput(Layer* layer);
