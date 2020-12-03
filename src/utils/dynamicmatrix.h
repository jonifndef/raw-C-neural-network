#ifndef DYNAMICMATRIX_H_
#define DYNAMICMATRIX_H_

#include "dynamicarray.h"

// exclusively for doubles
typedef struct DynamicMatrix
{
    int rows;
    int columns;
    int rowCapacity;
    int columnCapacity;
    DynamicArray **data;
} DynamicMatrix;

DynamicMatrix* createDynamicMatrix();
void freeDynamicMatrix(DynamicMatrix *matrix);

bool pushRow(DynamicMatrix *matrix, DynamicArray *row);
bool pushColumn(DynamicMatrix *matrix, DynamicArray *row);
void pushRowElement(DynamicMatrix *matrix, int row, double element);
void pushColumnElement(DynamicMatrix *matrix, int column, double element);

bool setDynamicMatrixRow(DynamicMatrix *matrix, int rowNum, const DynamicArray *row);
void setDynamicMatrixColumn(DynamicMatrix *matrix, int columnNum, const DynamicArray *column);
void setDynamicMatrixElement(DynamicMatrix *matrix, int row, int column, double element);

DynamicArray* getDynamicMatrixRow(const DynamicMatrix *matrix, int row);
DynamicArray* getDynamicMatrixColumn(const DynamicMatrix *matrix, int column);
double getDynamicMatrixElement(const DynamicMatrix *matrix, int row, int column);

void transposeDynamicMatrix(DynamicMatrix *matrix);
void copyDynamicMatrix(DynamicMatrix *destination, const DynamicMatrix *source);
void clearDynamicMatrix(DynamicMatrix *matrix);

// Debug
void printDynamicMatrix(DynamicMatrix *matrix);

#endif // DYNAMICMATRIX_H_
