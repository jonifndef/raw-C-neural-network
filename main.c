#include <stdio.h>
#include <stdlib.h>

#include "neuron.h"

int main(int argc, char *argv[])
{
    int numNeuronsPrevLayer = 3;
    double inputs[] = { 1, 2, 3 };
    double weights[] = { 0.2, 0.8, -0.5 };
    double bias = 2.0;

    double output;

    Neuron *neuron = createNeuron(numNeuronsPrevLayer, bias);
    updateNeuron(neuron, inputs, weights);
    output = getNeuronOutput(neuron);
    deleteNeuron(neuron);
    free(neuron);

    printf("Output of the neruon is: %f\n", output);

    return 0;
}
