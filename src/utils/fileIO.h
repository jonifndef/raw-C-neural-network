#ifndef FILEIO_H_
#define FILEIO_H_

#include "utils.h"
#include "dynamicmatrix.h"

//static MatrixDoubles* populateMatrix(const char *filePath,
//                                    int rows,
//                                    int columns);

// Reading data sample
bool readSampleData(const char *filePath,
                    const char *delimiter,
                    DynamicMatrix *data);

#endif //FILEIO_H_
