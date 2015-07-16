#include "CpuMatrix.h"

/**
* 在 CPU 上产生随机矩阵
* fMatrix  矩阵头指针
* iRow     矩阵行数
* iCol     矩阵列数
*/
void GenerateMatrix(float *fMatrix, const int iRow, const int iCol)
{
	// 检查矩阵维度是否正确
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return;
	}

	srand(1); // 随机数产生种子
	for (int i = 0; i < iRow; i++)
	{
		for (int j = 0; j < iCol; j++)
		{
			fMatrix[i * iCol + j] = float((rand() % 100) / 100.0);
		}
	}
}

/**
* 在CPU上计算矩阵的和
* fMatrix  矩阵头指针
* @return  和
*/
float SumOfMatrix(float *fMatrix, const int iRow, const int iCol)
{
	double fResult = 0.0; // 输出结果

	// 检查矩阵维度是否正确
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return fResult;
	}

	for (int i = 0; i < iRow; i++)
	{
		for (int j = 0; j < iCol; j++)
		{
			fResult += double(fMatrix[i * iCol + j]);
		}
	}

	return float(fResult);
}

/**
* 在CPU上计算矩阵的和所用的时间
* fMatrix       矩阵头指针
* iRow          矩阵行数
* iCol          矩阵列数
* @return       和
*/

float RunTimeOfCpu(float *fMatrix, const int iRow, const int iCol)
{
	// 检查矩阵维度是否正确
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return 0;
	}

	float fResult = 0;

	clock_t startCpu, endCpu;
	startCpu = clock();
	fResult = SumOfMatrix(fMatrix, iRow, iCol);
	endCpu = clock();
	double duration = (double)(endCpu - startCpu) / CLOCKS_PER_SEC;
	std::cout << "CPU的运行时间为：" << duration * 1000 << " ms." << std::endl;

	return fResult;
}


