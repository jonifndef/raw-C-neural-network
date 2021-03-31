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
bool pushRowElement(DynamicMatrix *matrix, int row, double element);
bool pushColumnElement(DynamicMatrix *matrix, int column, double element);

bool insertDynamicMatrixRow(DynamicMatrix *matrix, int rowPosition, DynamicArray *row);
bool insertDynamicMatrixColumn(DynamicMatrix *matrix, int columnPosition, DynamicArray *column);
bool eraseDynamicMatrixRow(DynamicMatrix *matrix, int rowPosition);
bool eraseDynamicMatrixColumn();

bool setDynamicMatrixRow(DynamicMatrix *matrix, int rowPosition, const DynamicArray *row);
bool setDynamicMatrixColumn(DynamicMatrix *matrix, int columnPosition, const DynamicArray *column);
bool setDynamicMatrixElement(DynamicMatrix *matrix, int row, int column, double element);

DynamicArray* getDynamicMatrixRowRef(const DynamicMatrix *matrix, int row);
DynamicArray* createDynamicMatrixColumnCopy(const DynamicMatrix *matrix, int column);
double getDynamicMatrixElement(const DynamicMatrix *matrix, int row, int column);

void transposeDynamicMatrix(DynamicMatrix *matrix);
bool copyDynamicMatrix(DynamicMatrix *destination, const DynamicMatrix *source);
void clearDynamicMatrix(DynamicMatrix *matrix);

// Debug
void printDynamicMatrix(DynamicMatrix *matrix);

#endif // DYNAMICMATRIX_H_
