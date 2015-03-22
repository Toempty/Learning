#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

#include "MyCuda.h"
#include "GenRandN.h"
#include "CountingSortCPU.h"
#include "IsOrder.h"
#include "CountingSortCUDA.h"

using namespace std;


/************************************************************************/
/*��������PrintfArray
/*��  �ܣ��������
/*����ֵ����
/************************************************************************/
void PrintfArray(int *A, const int SIZE)
{
	for (int i = 0; i < SIZE; ++i)
		cout << A[i] << " ";

	cout << endl;
}



const int N(80000000); // ���峣��
const int maxNum(10000000); // ���峣��

int main()
{
	vector<int> dataA(N, 0);
	vector<int> dataCPU(N, 0);
	vector<int> dataCUDA(N, 0);

	GenRandN(&dataA[0], N, maxNum); // �����������

	clock_t startTime, endTime;
	startTime = clock();

	CountingSort(&dataA[0], &dataCPU[0], N, maxNum); // ��������

	endTime = clock();
	cout<< "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;


	startTime = clock();

	CountingSortCUDA(&dataA[0], &dataCUDA[0], N, maxNum); // ��������

	endTime = clock();
	cout<< "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;


	// �ж������Ƿ�׼ȷ
	cout << IsOrder(&dataCPU[0], N) << endl;
	cout << IsOrder(&dataCUDA[0], N) << endl;
	cout << dataCPU[N-1] << " " << dataCUDA[N-1] << endl;

	return 0;
}

