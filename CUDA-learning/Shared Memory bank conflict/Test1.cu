#include "Test1.h"
#include "IsEqualMatrix.h"

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>

#define BLOCKSIZE 32

/**
* ���ܣ�ÿ�����ڵ�ÿ��Ԫ�ؼ���Ŀ���һ�еĺ�
* ˵��������ÿ�еļ�����ȫ��ͬ�����һ�ͬʱ����һ�� bank
* ���룺matrix �������
* �����matrixTest �������
* ���룺row ����
* ���룺col ����
*/
__global__ void SharedMemoryBankConflictTest1(float *matrix, float *matrixTest, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // ������
	int index = y_id * col + x_id;

	__shared__ float sData[BLOCKSIZE][BLOCKSIZE];


	if (x_id < col && y_id < row)
	{
		sData[threadIdx.y][threadIdx.x] = matrix[index];
		__syncthreads();

		float data = 0.0f;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < BLOCKSIZE; j++)
			{
				data += sData[threadIdx.x][j];
			}
		}
		matrixTest[index] = data;

	}
}


/**
* ���ܣ�ÿ�����ڵ�ÿ��Ԫ�ؼ���Ŀ���һ�еĺ�
* ˵��������ÿ�еļ�����ȫ��ͬ�����ڶ�����һ��������ÿһ�еĻ�ͬʱ���ʲ�ͬ�� bank
* ���룺matrix �������
* �����matrixTest �������
* ���룺row ����
* ���룺col ����
*/
__global__ void SharedMemoryBankConflictTest1_Pad(float *matrix, float *matrixTest, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // ������
	int index = y_id * col + x_id;

	__shared__ float sData[BLOCKSIZE][BLOCKSIZE+1];


	if (x_id < col && y_id < row)
	{
		sData[threadIdx.y][threadIdx.x] = matrix[index];
		__syncthreads();

		float data = 0.0f;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < BLOCKSIZE; j++)
			{
				data += sData[threadIdx.x][j];
			}
		}
		matrixTest[index] = data;

	}
}

/**
* ���ܣ���һ������ʾ�������� bank conflict
* ���룺matrix_Dev �������
* ���룺row ����
* ���룺col ����
*/
void Test1(float *matrix_Dev, const int row, const int col)
{
	float *matrixTestA_Dev, *matrixTestB_Dev;
	cudaMalloc((void**)&matrixTestA_Dev, row * col * sizeof(float));
	cudaMemset(matrixTestA_Dev, 0, row * col * sizeof(float));
	cudaMalloc((void**)&matrixTestB_Dev, row * col * sizeof(float));
	cudaMemset(matrixTestB_Dev, 0, row * col * sizeof(float));

	float *matrixTestA_Host = (float *)malloc(row * col * sizeof(float));
	float *matrixTestB_Host = (float *)malloc(row * col * sizeof(float));

	dim3 dimBlock2D(BLOCKSIZE, BLOCKSIZE);
	dim3 dimGrid2D((col+ BLOCKSIZE - 1) / dimBlock2D.x, (row + BLOCKSIZE - 1) / dimBlock2D.y);

	// ��¼ʱ��
	cudaEvent_t start_GPU, end_GPU;
	float elaspsedTime;
	cudaEventCreate(&start_GPU);
	cudaEventCreate(&end_GPU);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start_GPU, 0);

	SharedMemoryBankConflictTest1<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, matrixTestA_Dev, row, col);

	// ��ʱ����
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);

	std::cout << "Test1 ������ʱ��Ϊ��" << elaspsedTime << "ms." << std::endl;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start_GPU, 0);

	SharedMemoryBankConflictTest1_Pad<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, matrixTestB_Dev, row, col);

	// ��ʱ����
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);

	std::cout << "Test1 ������ʱ��Ϊ��" << elaspsedTime << "ms." << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cudaMemcpy(matrixTestA_Host, matrixTestA_Dev, row * col * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(matrixTestB_Host, matrixTestB_Dev, row * col * sizeof(float), cudaMemcpyDeviceToHost);

	std::cout << "����Ƿ���ͬ��" << IsEqualMatrix(matrixTestA_Host, matrixTestB_Host, row, col) << std::endl;

	cudaEventDestroy(start_GPU);
	cudaEventDestroy(end_GPU);

	cudaFree(matrixTestA_Dev);
	cudaFree(matrixTestB_Dev);
	free(matrixTestA_Host);
	free(matrixTestB_Host);
}