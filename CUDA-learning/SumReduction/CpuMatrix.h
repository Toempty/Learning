#ifndef CPUMATRIX_H
#define CPUMATRIX_H

#include <stdlib.h>
#include <iostream>
#include <time.h>

void GenerateMatrix(float *fMatrix, const int iRow, const int iCol);
float RunTimeOfCpu(float *fMatrix, const int iRow, const int iCol);

#endif // !CPUMATRIX_H
