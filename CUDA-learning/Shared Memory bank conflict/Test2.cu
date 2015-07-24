#include "Test2.h"
#include "IsEqualMatrix.h"

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <iostream>

#define BLOCKSIZE 32

/**
* ���ܣ�ÿ�� warp ���ʲ�ͬ�� bank����ͬ�� warp ����ͬһ�� bank
* ���룺matrix �������
* �����matrixTest �������
* ���룺row ����
* ���룺col ����
*/
__global__ void SharedMemoryBankConflictTest2(float *matrix, float *matrixTest, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // ������
	int index = y_id * col + x_id;

	__shared__ float sData[BLOCKSIZE][BLOCKSIZE];

	if (x_id < col && y_id < row)
	{
		sData[threadIdx.x][threadIdx.y] = matrix[index];
		__syncthreads();

		for (int i = 0; i < 1; i++)
		{
			matrixTest[index] = sData[threadIdx.x][threadIdx.y];
		}
	}
}

/**
* ���ܣ�ÿ�� warp ���ʲ�ͬ�� bank
* ˵����ʹ�õĶ���Ŀռ�
* ���룺matrix �������
* �����matrixTest �������
* ���룺row ����
* ���룺col ����
*/
__global__ void SharedMemoryBankConflictTest2_Pad(float *matrix, float *matrixTest, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // ������
	int index = y_id * col + x_id;

	__shared__ float sData[BLOCKSIZE][BLOCKSIZE+1];


	if (x_id < col && y_id < row)
	{
		sData[threadIdx.x][threadIdx.y] = matrix[index];
		__syncthreads();

		for (int i = 0; i < 1; i++)
		{
			matrixTest[index] = sData[threadIdx.x][threadIdx.y];
		}
	}
}

/**
* ���ܣ����棬ͬһ�� warp ����ͬһ�� bank �Ĳ�ֵͬ����ͬ warp ���ʲ�ͬ bank
* ���룺matrix �������
* �����matrixTest �������
* ���룺row ����
* ���룺col ����
*/
__global__ void SharedMemoryBankConflictTest2_Across(float *matrix, float *matrixTest, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // ������
	int index = y_id * col + x_id;

	__shared__ float sData[BLOCKSIZE][BLOCKSIZE];


	if (x_id < col && y_id < row)
	{
		sData[threadIdx.y][threadIdx.x] = matrix[index];
		__syncthreads();


		for (int i = 0; i < 1; i++)
		{
			matrixTest[index] = sData[threadIdx.y][threadIdx.x];
		}
	}
}

/**
* ���ܣ��ڶ�������ʾ�������棬ͬһ�� warp ����ͬһ�� bank �Ĳ�ֵͬ
* ���룺matrix_Dev �������
* ���룺row ����
* ���룺col ����
*/
void Test2(float *matrix_Dev, const int row, const int col)
{
	float *matrixTestA_Dev, *matrixTestB_Dev, *matrixTestC_Dev;
	cudaMalloc((void**)&matrixTestA_Dev, row * col * sizeof(float));
	cudaMemset(matrixTestA_Dev, 0, row * col * sizeof(float));
	cudaMalloc((void**)&matrixTestB_Dev, row * col * sizeof(float));
	cudaMemset(matrixTestB_Dev, 0, row * col * sizeof(float));
	cudaMalloc((void**)&matrixTestC_Dev, row * col * sizeof(float));
	cudaMemset(matrixTestC_Dev, 0, row * col * sizeof(float));

	float *matrixTestA_Host = (float *)malloc(row * col * sizeof(float));
	float *matrixTestB_Host = (float *)malloc(row * col * sizeof(float));
	float *matrixTestC_Host = (float *)malloc(row * col * sizeof(float));

	dim3 dimBlock2D(BLOCKSIZE, BLOCKSIZE);
	dim3 dimGrid2D((col+ BLOCKSIZE - 1) / dimBlock2D.x, (row + BLOCKSIZE - 1) / dimBlock2D.y);

	// ��¼ʱ��
	cudaEvent_t start_GPU, end_GPU;
	float elaspsedTime;
	cudaEventCreate(&start_GPU);
	cudaEventCreate(&end_GPU);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start_GPU, 0);

	SharedMemoryBankConflictTest2<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, matrixTestA_Dev, row, col);

	// ��ʱ����
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);

	std::cout << "\nTest2 ������ʱ��Ϊ��" << elaspsedTime << "ms." << std::endl;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start_GPU, 0);

	SharedMemoryBankConflictTest2_Pad<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, matrixTestB_Dev, row, col);

	// ��ʱ����
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);

	std::cout << "Test2 ������ʱ��Ϊ��" << elaspsedTime << "ms." << std::endl;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start_GPU, 0);

	SharedMemoryBankConflictTest2_Across<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, matrixTestC_Dev, row, col);

	// ��ʱ����
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);

	std::cout << "Test2 ������ʱ��Ϊ��" << elaspsedTime << "ms." << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cudaMemcpy(matrixTestA_Host, matrixTestA_Dev, row * col * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(matrixTestB_Host, matrixTestB_Dev, row * col * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(matrixTestC_Host, matrixTestC_Dev, row * col * sizeof(float), cudaMemcpyDeviceToHost);

	std::cout << "����Ƿ���ͬ�� A-B : " << IsEqualMatrix(matrixTestA_Host, matrixTestB_Host, row, col)
	                     << "    A-C : " << IsEqualMatrix(matrixTestA_Host, matrixTestC_Host, row, col) << std::endl;

	cudaEventDestroy(start_GPU);
	cudaEventDestroy(end_GPU);

	cudaFree(matrixTestA_Dev);
	cudaFree(matrixTestB_Dev);
	cudaFree(matrixTestC_Dev);
	free(matrixTestA_Host);
	free(matrixTestB_Host);
	free(matrixTestC_Host);
}