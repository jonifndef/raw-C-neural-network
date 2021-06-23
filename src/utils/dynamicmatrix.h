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

typedef enum TakeOwnerShip
{
    DO_NOT_TAKE_OWNERSHIP = 0,
    DO_TAKE_OWNERSHIP = 1
} TakeOwnerShip;

DynamicMatrix* createDynamicMatrix();
DynamicMatrix* createDynamicMatrixWithCapacity(const uint rowCapacity,
                                               const uint columnCapacity);
void freeDynamicMatrix(DynamicMatrix *matrix);

bool pushRow(DynamicMatrix *matrix, DynamicArray *row, const TakeOwnerShip option);
bool pushColumn(DynamicMatrix *matrix, DynamicArray *row);
bool pushRowElement(DynamicMatrix *matrix, int row, double element);
bool pushColumnElement(DynamicMatrix *matrix, int column, double element);

bool insertDynamicMatrixRow(DynamicMatrix *matrix, int rowPosition, DynamicArray *row);
bool insertDynamicMatrixColumn(DynamicMatrix *matrix, int columnPosition, DynamicArray *column);
bool eraseDynamicMatrixRow(DynamicMatrix *matrix, int rowPosition);
bool eraseDynamicMatrixColumn(DynamicMatrix *matrix, int columnPosition);

bool setDynamicMatrixRow(DynamicMatrix *matrix, int rowPosition, const DynamicArray *row);
bool setDynamicMatrixColumn(DynamicMatrix *matrix, int columnPosition, const DynamicArray *column);
bool setDynamicMatrixElement(DynamicMatrix *matrix, int row, int column, double element);

DynamicArray* getDynamicMatrixRowRef(const DynamicMatrix *matrix, int row);
DynamicArray* getDynamicMatrixRowCopy(const DynamicMatrix *matrix, int row);
DynamicArray* createDynamicMatrixColumnCopy(const DynamicMatrix *matrix, int column);
double getDynamicMatrixElement(const DynamicMatrix *matrix, int row, int column);

DynamicMatrix* createDynamicMatrixTranspose(const DynamicMatrix *matrix);
bool copyDynamicMatrix(DynamicMatrix *destination, const DynamicMatrix *source);
bool copyDynamicMatrixElements(DynamicMatrix *destination, const DynamicMatrix *source);
bool clearDynamicMatrix(DynamicMatrix *matrix);

// Debug
void printDynamicMatrix(DynamicMatrix *matrix);
DynamicMatrix* dotProductDynamicMatrix(const DynamicMatrix *lhs,
                                       const DynamicMatrix *rhs);

#endif // DYNAMICMATRIX_H_
