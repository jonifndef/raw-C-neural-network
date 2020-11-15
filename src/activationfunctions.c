#include "activationfunctions.h"

double relu(double input)
{
    return (input > 0) ? input : 0;
}

double linear(double input)
{
    return input;
}
