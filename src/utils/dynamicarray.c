#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dynamicarray.h"

static void reAllocDynamicArr(DynamicArray *array, int newCapacity)
{
    double *newData = calloc(newCapacity, sizeof(double));
    memcpy(newData, array->data, array->size * sizeof(double));

    array->capacity = newCapacity;
    free(array->data);

    array->data = newData;
}

DynamicArray* createDynamicArr()
{
    DynamicArray *array = calloc(1, sizeof(DynamicArray));

    // default capacity 4, seems reasonable, right?
    array->capacity = 4;
    array->size = 0;
    array->data = calloc(array->capacity, sizeof(double));

    return array;
}

void freeDynamicArr(DynamicArray *array)
{
    free(array->data);
    free(array);
}

void pushBackDynamicArr(DynamicArray *array, double element)
{
    if (array->size >= array->capacity)
    {
        // Note, newCapacity might need some tweaking
        reAllocDynamicArr(array, array->capacity + (array->capacity / 2));
    }

    array->data[array->size++] = element;
}

bool setDynamicArrElement(DynamicArray *array, int index, double value)
{
    if (index <= array->capacity)
    {
        array->data[index] = value;
        return true;
    }
    else
        return false;
}

void setDynamicArrRow(DynamicArray *array, const double *row, int size)
{
    if (size > array->capacity)
    {
        reAllocDynamicArr(array, size);
    }
    memcpy(array->data, row, size * sizeof(double));
    array->size = size;
}


int getDynamicArrSize(const DynamicArray *array)
{
    return array->size;
}

double getDynamicArrElement(const DynamicArray *array, int index)
{
    return (index <= array->capacity) ? array->data[index] : 0.0;
}

void copyDynamicArr(DynamicArray *destination, const DynamicArray *source)
{
    double *newData = calloc(source->capacity, sizeof(double));
    memcpy(newData, source->data, source->size * sizeof(double));

    destination->capacity = source->capacity;
    free(destination->data);

    destination->data = newData;
}

void clearDynamicArr(DynamicArray *array)
{
    for (int i = 0; i < array->size; i++)
    {
        array->data[i] = 0.0;
    }
    array->size = 0;
}

// For debug purposes:
void printDynamicArr(const DynamicArray *array)
{
    for (int i = 0; i < array->size; i++)
    {
        printf("%.3f ", array->data[i]);
    }
    printf("\n");
}
