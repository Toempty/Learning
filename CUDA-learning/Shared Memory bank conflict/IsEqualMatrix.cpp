#include "IsEqualMatrix.h"

#include <iostream>

using std::cout;
using std::endl;

/**
* ���ܣ��ж����������Ƿ����
* ���룺matrixA �������
* ���룺matrixB �������
* ���룺row ����
* ���룺col ����
* return��true or false
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