#include "IsEqualMatrix.h"

#include <iostream>

using std::cout;
using std::endl;

/**
* 功能：判断两个矩阵是否相等
* 输入：matrixA 输入矩阵
* 输入：matrixB 输出矩阵
* 输入：row 行数
* 输入：col 列数
* return：true or false
*/
bool IsEqualMatrix(float *matrixA, float *matrixB, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int index = i * col + j;
			if (abs(matrixA[index] - matrixB[index]) > 1e-6)
			{
				//cout << i << " " << j << endl;
				//cout << matrixA[index] << " " << matrixB[index] << endl;
				return false;
			}
		}
	}

	return true;
}