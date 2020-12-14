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

    return true;
}

bool reAllocDynamicArr(DynamicArray *array, int newCapacity)
{
    //printf("reallocating dynamic array, newcapacity: %d\n", newCapacity);
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

bool insert(DynamicArray *array, int position, double element)
{
    if (position < array->size && position >= 0)
    {
        if (position == array->size - 1)
        {
            if (!pushBackDynamicArr(array, element))
            {
                return false;
            }
        }
        else
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
    }
    return false;
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
    return (index <= array->capacity) ? array->data[index] : -999;
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

    memcpy(newData, source->data, source->size * sizeof(double));

    destination->capacity = source->capacity;
    destination->size = source->size;

    // This memory might not be pointing to anything if it's a brand new array
    // but is has definitively been allocated with a call to createDynamicArray()
    // if capacity is set to the default value,
    // so free it to not have it dangeling
    if (destination->capacity == 4)
    {
        free(destination->data);
    }

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
