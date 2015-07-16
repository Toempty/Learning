#include "CpuMatrix.h"

/**
* �� CPU �ϲ����������
* fMatrix  ����ͷָ��
* iRow     ��������
* iCol     ��������
*/
void GenerateMatrix(float *fMatrix, const int iRow, const int iCol)
{
	// ������ά���Ƿ���ȷ
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return;
	}

	srand(1); // �������������
	for (int i = 0; i < iRow; i++)
	{
		for (int j = 0; j < iCol; j++)
		{
			fMatrix[i * iCol + j] = float((rand() % 100) / 100.0);
		}
	}
}

/**
* ��CPU�ϼ������ĺ�
* fMatrix  ����ͷָ��
* @return  ��
*/
float SumOfMatrix(float *fMatrix, const int iRow, const int iCol)
{
	double fResult = 0.0; // ������

	// ������ά���Ƿ���ȷ
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
* ��CPU�ϼ������ĺ����õ�ʱ��
* fMatrix       ����ͷָ��
* iRow          ��������
* iCol          ��������
* @return       ��
*/

float RunTimeOfCpu(float *fMatrix, const int iRow, const int iCol)
{
	// ������ά���Ƿ���ȷ
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
	std::cout << "CPU������ʱ��Ϊ��" << duration * 1000 << " ms." << std::endl;

	return fResult;
}


