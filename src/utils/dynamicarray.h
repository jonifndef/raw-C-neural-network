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
bool reAllocDynamicArr(DynamicArray *arr, int newCapacity);
void freeDynamicArr(DynamicArray *array);
bool pushBackDynamicArr(DynamicArray *array, double element);
bool setDynamicArrElement(DynamicArray *array, int index, double value);
bool setDynamicArrRow(DynamicArray *array, const double *row, int size);
int getDynamicArrSize(const DynamicArray *array);
double getDynamicArrElement(const DynamicArray *array, int index);
bool copyDynamicArr(DynamicArray *destination, const DynamicArray *source);
void clearDynamicArr(DynamicArray *array);

// For debug purposes:
void printDynamicArr(const DynamicArray *array);

#endif // DYNAMICARRAY_H_
