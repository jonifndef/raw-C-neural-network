typedef struct MatrixDoubles
{
    int rows;
    int columns;
    double **data;
} MatrixDoubles;

MatrixDoubles* createMatrixDoubles(int numRows, int numColumns);
void freeMatrixDoublesContents(MatrixDoubles *matrix);
void setMatrixDoublesRow(MatrixDoubles *matrix, int row, double *data);
void setMatrixDoubelsColumn(MatrixDoubles *matrix, int column, double *data);
double* getMatrixDoublesRow(MatrixDoubles *matrix, int row);
//double* getMatrixDoublesColumn(MatrixDoubles *matrix, int column);
double getMatrixDoublesElement(MatrixDoubles *matrix, int row, int column);
