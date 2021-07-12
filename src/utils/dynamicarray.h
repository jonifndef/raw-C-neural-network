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
DynamicArray* createPopulatedDynamicArr(double *arr, const uint size);
DynamicArray* createDynamicArrWithCapacity(const uint capacity);
void freeDynamicArr(DynamicArray *array);

bool pushBackDynamicArr(DynamicArray *array, double element);
bool insertDynamicArr(DynamicArray *array, int position, double element);
bool eraseDynamicArr(DynamicArray *array, int position);
void popDynamicArr(DynamicArray *array);

bool setDynamicArrElement(DynamicArray *array, int index, double value);
bool setDynamicArr(DynamicArray *array, const double *inputArr, int size);

int getDynamicArrSize(const DynamicArray *array);
double getDynamicArrElement(const DynamicArray *array, int index);
double backDynamicArr(const DynamicArray *array);
double frontDynamicArr(const DynamicArray *array);

bool copyDynamicArr(DynamicArray *destination, const DynamicArray *source);
void clearDynamicArr(DynamicArray *array);

double getMaxElementDynamicArr(const DynamicArray *array);
void addToAllElementsDynamicArr(DynamicArray *array, double value);
void subtractFromAllElementsDynamicArr(DynamicArray *array, double value);

// For debug purposes:
void printDynamicArr(const DynamicArray *array);

#endif // DYNAMICARRAY_H_
