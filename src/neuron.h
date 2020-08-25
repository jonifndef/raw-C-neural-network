#ifndef NEURON_H_
#define NEURON_H_

typedef struct Neuron
{
    int numInputs;
    double *inputs;
    double *weights;
    double bias;
    double(*activationFunction)(double);
} Neuron;

Neuron* createNeuron(int numNeuronsPrevLayer, double(*activationFunction)(double));
void freeNeuronContents(Neuron *neuron);
void updateWeightsAndBiasNeuron(Neuron *neuron, double *weights, double bias);
double getNeuronOutput(const Neuron *neuron, double *inputs);

#endif //NEURON_H_
