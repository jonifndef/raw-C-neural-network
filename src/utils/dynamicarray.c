#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dynamicarray.h"

static bool insertAndMoveDynamicArr(DynamicArray *array,
                                    int position,
                                    double element)
{
    DynamicArray *arrCopy = createDynamicArr();
    if (!copyDynamicArr(arrCopy, array))
    {
        return false;
    }

    for (int i = position; i < array->size; i++)
    {
        array->data[i + 1] = arrCopy->data[i];
    }
    array->data[position] = element;
    array->size++;

    free(arrCopy);
    return true;
}

static bool eraseAndMoveDynamicArr(DynamicArray *array, int position)
{
    DynamicArray *arrCopy = createDynamicArr();
    if (!copyDynamicArr(arrCopy, array))
    {
        return false;
    }

    for (int i = position; i < array->size; i++)
    {
        array->data[i] = arrCopy->data[i + 1];
    }
    array->size--;

    free(arrCopy);
    return true;
}

bool reAllocDynamicArr(DynamicArray *array, int newCapacity)
{
    double *newData = calloc(newCapacity, sizeof(double));
    if (newData == NULL)
    {
        return false;
    }

    memcpy(newData, array->data, array->size * sizeof(double));

    array->capacity = newCapacity;
    free(array->data);

    array->data = newData;
    return true;
}

DynamicArray* createDynamicArr()
{
    DynamicArray *array = calloc(1, sizeof(DynamicArray));
    if (array == NULL)
    {
        return NULL;
    }

    // default capacity 4, seems reasonable, right?
    array->capacity = 4;
    array->size = 0;
    array->data = calloc(array->capacity, sizeof(double));
    if (array->data == NULL)
    {
        return NULL;
    }

    return array;
}

void freeDynamicArr(DynamicArray *array)
{
    free(array->data);
    free(array);
}

bool pushBackDynamicArr(DynamicArray *array, double element)
{
    if (array->size >= array->capacity)
    {
        // Note, newCapacity might need some tweaking
        if (!reAllocDynamicArr(array, array->capacity + (array->capacity / 2)))
        {
            return false;
        }
    }

    array->data[array->size++] = element;
    return true;
}

bool insertDynamicArr(DynamicArray *array, int position, double element)
{
    if (position < array->size && position >= 0)
    {
        if (array->size >= array->capacity)
        {
            if (!reAllocDynamicArr(array, array->capacity + (array->capacity / 2)))
            {
                return false;
            }
        }
        if (!insertAndMoveDynamicArr(array, position, element))
        {
            return false;
        }
        return true;
    }
    return false;
}

bool eraseDynamicArr(DynamicArray *array, int position)
{
    if (position < 0 || position >= array->size)
    {
        return false;
    }

    if (!eraseAndMoveDynamicArr(array, position))
    {
        return false;
    }
    return true;
}

void popDynamicArr(DynamicArray *array)
{
    if (array->size > 0)
    {
        array->size--;
    }
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

bool setDynamicArrRow(DynamicArray *array, const double *row, int size)
{
    if (size > array->capacity)
    {
        if (!reAllocDynamicArr(array, size))
        {
            return false;
        }
    }
    memcpy(array->data, row, size * sizeof(double));
    array->size = size;
    return true;
}

int getDynamicArrSize(const DynamicArray *array)
{
    return array->size;
}

double getDynamicArrElement(const DynamicArray *array, int index)
{
    //return (index <= array->capacity) ? array->data[index] : 0.0;
    return (index < array->capacity) ? array->data[index] : -999;
}

double backDynamicArr(const DynamicArray *array)
{
    return array->data[array->size - 1];
}

double frontDynamicArr(const DynamicArray *array)
{
    return array->data[0];
}

bool copyDynamicArr(DynamicArray *destination, const DynamicArray *source)
{
    double *newData = calloc(source->capacity, sizeof(double));
    if (newData == NULL)
    {
        return false;
    }

    // bug here when copying empty matrix! when inserting row into empty matrix
    memcpy(newData, source->data, source->size * sizeof(double));

    destination->capacity = source->capacity;
    destination->size = source->size;

    free(destination->data);
    destination->data = newData;
    return true;
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
    printf("\n\n");
}
