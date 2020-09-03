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
bool setDynamicArrElement(DynamicArray *array, int index, double value);
int getDynamicArrSize(const DynamicArray *array);
double getDynamicArrElement(const DynamicArray *array, int index);
void copyDynamicArr(DynamicArray *destination, const DynamicArray *source);
void clearDynamicArr(DynamicArray *array);

#endif // DYNAMICARRAY_H_
