#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct MatrixDoubles
{
    int rows;
    int columns;
    double **data;
} MatrixDoubles;

// TODO: use dynamic array as data member?
typedef struct DynamicMatrix
{
    int rows;
    int columns;
    int rowCapacity;
    int columnCapacity;
    double **data;
} DynamicMatrix;

// Matrix functions
MatrixDoubles* createMatrixDoubles(int numRows, int numColumns);
void freeMatrixDoublesContents(MatrixDoubles *matrix);
void setMatrixDoublesRow(MatrixDoubles *matrix, int row, double *data);
void setMatrixDoubelsColumn(MatrixDoubles *matrix, int column, double *data);
double* getMatrixDoublesRow(const MatrixDoubles *matrix, int row);
//double* getMatrixDoublesColumn(MatrixDoubles *matrix, int column);
double getMatrixDoublesElement(const MatrixDoubles *matrix, int row, int column);

// Dynamic matrix functions - exclusively for doubles
DynamicMatrix* createDynamicMatrix();
void pushRow(DynamicMatrix *matrix, double *row);
void pushColumn(DynamicMatrix *matrix, double *row);
void pushRowElement(DynamicMatrix *matrix, int row, double element);
void pushColumnElement(DynamicMatrix *matrix, int column, double element);

double* getDynamicMatrixRow(DynamicMatrix *matrix, int row);
double* getDynamicMatrixColumn(DynamicMatrix *matrix, int column);
double getDynamicMatrixElement(DynamicMatrix *matrix, int row, int column);

void transposeDynamicMatrix(DynamicMatrix *matrix);

void clearDynamicMatrix(DynamicMatrix *matrix);
void freeDynamicMatrix(DynamicMatrix *matrix);

#endif //MATRIX
