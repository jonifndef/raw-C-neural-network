typedef struct Neuron
{
    int numInputs;
    double *inputs;
    double *weights;
    double bias;
} Neuron;

Neuron* createNeuron(int numNeuronsPrevLayer);
void freeNeuronContents(Neuron *neuron);
void updateWeightsAndBiasNeuron(Neuron *neuron, double *weights, double bias);
double getNeuronOutput(const Neuron *neuron, double *inputs);
