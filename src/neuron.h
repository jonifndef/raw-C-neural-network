typedef struct Neuron
{
    int numInputs;
    double *inputs;
    double *weights;
    double bias;
    void *activationFunction;
} Neuron;

Neuron* createNeuron(int numNeuronsPrevLayer, double(*activationFunction)(double));
void freeNeuronContents(Neuron *neuron);
void updateWeightsAndBiasNeuron(Neuron *neuron, double *weights, double bias);
double getNeuronOutput(const Neuron *neuron, double *inputs);
