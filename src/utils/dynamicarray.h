#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include "utils.h"

typedef struct DynamicArray
{
    int size;
    int capacity;
    double *data;
} DynamicArray;

bool reAllocDynamicArr(DynamicArray *arr, int newCapacity);

DynamicArray* createDynamicArr();
void freeDynamicArr(DynamicArray *array);

bool pushBackDynamicArr(DynamicArray *array, double element);
bool insert(DynamicArray *array, int position, double element);
void popDynamicArr(DynamicArray *array);

bool setDynamicArrElement(DynamicArray *array, int index, double value);
bool setDynamicArrRow(DynamicArray *array, const double *row, int size);

int getDynamicArrSize(const DynamicArray *array);
double getDynamicArrElement(const DynamicArray *array, int index);
double backDynamicArr(const DynamicArray *array);
double frontDynamicArr(const DynamicArray *array);

bool copyDynamicArr(DynamicArray *destination, const DynamicArray *source);
void clearDynamicArr(DynamicArray *array);

// For debug purposes:
void printDynamicArr(const DynamicArray *array);

#endif // DYNAMICARRAY_H_
