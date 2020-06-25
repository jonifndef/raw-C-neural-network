typedef struct Neuron
{
    int numInputs;
    double *inputs;
    double *weights;
    double bias;
} Neuron;

Neuron* createNeuron(int numNeuronsPrevLayer);
void freeNeuronContents(Neuron *neuron);
void updateNeuron(Neuron *neuron, double *inputs, double *weights, double bias);
double getNeuronOutput(const Neuron *neuron);
