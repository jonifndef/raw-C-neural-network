#include <stdio.h>
#include <stdlib.h>

#include "layer.h"

int main(int argc, char *argv[])
{
    int numNeuronsPrevLayer = 4;
    double inputs[] = { 1, 2, 3, 2.5 };
    double weights[3][4] = {
                                { 0.2, 0.8, -0.5, 1.0 },
                                { 0.5, -0.91, 0.26, -0.5 },
                                { -0.26, -0.27, 0.17, 0.87 }
                           };
    double biases[3] = { 2, 3, 0.5 };
    double *outputs = calloc(3, sizeof(double));

    //Neuron *neuron = createNeuron(numNeuronsPrevLayer);
    //updateNeuron(neuron, inputs, weights, bias);
    //output = getNeuronOutput(neuron);
    //freeNeuronContents(neuron);
    //free(neuron);

    //printf("Output of the neruon is: %.2f\n", output);
    
    Layer *layer = createLayer(3, numNeuronsPrevLayer);
    updateNeuronsInLayer(layer, inputs, weights, biases);
    outputs = getLayerOutput(layer);

    for (int i = 0; i < 3; i++)
    {
        printf("Output of neuron %d: %.3f\n", i, outputs[i]);
    }
    free(outputs);

    return 0;
}
