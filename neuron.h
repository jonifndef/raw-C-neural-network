typedef struct Neuron
{
    int numInputs;
    double *inputs;
    double *weights;
    double bias;
} Neuron;

Neuron* createNeuron(int numNeuronsPrevLayer, double bias);
void deleteNeuron(Neuron *neuron);
void updateNeuron(Neuron *neuron, double *inputs, double *weights);
double getNeuronOutput(const Neuron *neuron);
