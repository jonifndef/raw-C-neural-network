#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include "utils.h"

typedef struct DynamicArray
{
    int size;
    int capacity;
    double *data;
} DynamicArray;

DynamicArray* createDynamicArr();
void freeDynamicArr(DynamicArray *array);
void pushBackDynamicArr(DynamicArray *array, double element);
double getDynamicArrElement(DynamicArray *array, int index);
bool copyDynamicArr(DynamicArray *destination, DynamicArray *source);
void clearDynamicArr(DynamicArray *array);

#endif // DYNAMICARRAY_H_
