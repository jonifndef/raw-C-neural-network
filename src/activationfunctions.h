#ifndef ACTIVATIONFUNCTIONS_H_
#define ACTIVATIONFUNCTIONS_H_

#include "utils/dynamicmatrix.h"

bool relu(DynamicMatrix *input);
bool linear(DynamicMatrix *input);
bool softmax(DynamicMatrix *input);

#endif //ACTIVATIONFUNCTIONS_H_
