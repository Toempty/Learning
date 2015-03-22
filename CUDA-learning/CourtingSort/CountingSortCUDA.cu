#include "CountingSortCUDA.h"
#include "MyCuda.h"
#include <iostream>
#include <vector>

using namespace std;

/************************************************************************/
/*��������CountingSortKernelOne
/*��  �ܣ����������һ����C[i]ΪA��Ԫ��i�ĸ���
/*����ֵ����
/************************************************************************/
__global__ void CountingSortKernelOne(int *A, int *C, int iSize)
{
	// ��������
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������

	if (x_id < iSize)
	{
		int iIdx = A[x_id];
		atomicAdd(&C[iIdx], 1);
	}
}

/************************************************************************/
/*��������CountingSortKernelTwo
/*��  �ܣ���������ڶ����˺���������һ�ι�Լ
/*����ֵ����
/************************************************************************/
__global__ void CountingSortKernelTwo(int *C, int k, int iSize)
{
	// ��������
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������

	x_id++;

	if (x_id <= k)
	{
		int iRe = x_id & (iSize - 1);
		if (0 == iRe)
			iRe = iSize;

		if (iRe > (iSize >> 1))
		{
			x_id--;
			C[x_id] = C[x_id] + C[x_id + (iSize >> 1) - iRe];
		}
	}
}

/************************************************************************/
/*��������CountingSortTwo
/*��  �ܣ���������ڶ�������C��������ۻ��͹�Լ
/*����ֵ����
/************************************************************************/
void CountingSortTwo(dim3 dimGridK, dim3 dimBlockK, int *devC, int k)
{
	int iSize = 1;
	while (iSize <= k)
	{
		iSize = iSize << 1;
		CountingSortKernelTwo<<<dimGridK, dimBlockK>>>(devC, k, iSize);
	}
}

/************************************************************************/
/*��������CountingSortKernelThree
/*��  �ܣ��������������������C������±������������
/*����ֵ����
/************************************************************************/
__global__ void CountingSortKernelThree(int *B, int *C, int k)
{
	// ��������
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������

	if (x_id <= k)
	{
		int iStart = 0;
		if (0 != x_id)
			iStart = C[x_id - 1];

		for (int i = iStart; i < C[x_id]; i++)
		{
			B[i] = x_id;
		}
	}
}

/************************************************************************/
/*��������CountingSort
/*��  �ܣ�CUDA������������A�����B
/*����ֵ����
/************************************************************************/
void CountingSortCUDA(int *A, int *B, const int SIZE, const int k)
{
	vector<int> C(k + 1, 0); // ����C���鲢��ʼ��

	int *devA;
	int *devB;
	int *devC;

	cudaMalloc((void**)&devA, sizeof(int) * SIZE);
	cudaMalloc((void**)&devB, sizeof(int) * SIZE);
	cudaMalloc((void**)&devC, sizeof(int) * (k + 1));

	cudaMemcpy(devA, A, sizeof(int) * SIZE, cudaMemcpyHostToDevice);
	cudaMemset(devB, 0, sizeof(int) * SIZE);
	cudaMemset(devC, 0, sizeof(int) * (k + 1));

	dim3 dimBlock(BLOCK_SIZE);
	dim3 dimGrid((SIZE + BLOCK_SIZE - 1) / BLOCK_SIZE);
	dim3 dimGridK((k + BLOCK_SIZE - 1) / BLOCK_SIZE);

	// C�������ӦA��Ԫ�ص�ֵ��ͳ��A��Ԫ�صĸ���
	CountingSortKernelOne<<<dimGrid, dimBlock>>>(devA, devC, SIZE);

	// C�м����ۼӣ���ʱA[i]��ӦC�е�A[i]��
	// C[i]��������i��Ԫ�ظ���
	CountingSortTwo(dimGridK, dimBlock, devC, k + 1);


	// ��C[A[i]]���Ԫ�ؼ�ΪA[i]��B�е���ȷλ��
	// �����±�Ӧ��0��ʼ�������C[A[j]]��ȥ1
	// C[i]����С�ڵ���i��Ԫ�ظ���
	CountingSortKernelThree<<<dimGridK, dimBlock>>>(devB, devC, k);

	cudaMemcpy(B, devB, sizeof(int) * SIZE, cudaMemcpyDeviceToHost);

	cudaFree(devA);
	cudaFree(devB);
	cudaFree(devC);
}