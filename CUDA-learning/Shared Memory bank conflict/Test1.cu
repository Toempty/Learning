#include "Test1.h"
#include "IsEqualMatrix.h"

#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>

#define BLOCKSIZE 32

/**
* 功能：每个块内的每个元素计算改块内一行的和
* 说明：块内每行的计算完全相同，并且会同时访问一个 bank
* 输入：matrix 输入矩阵
* 输出：matrixTest 输出矩阵
* 输入：row 行数
* 输入：col 列数
*/
__global__ void SharedMemoryBankConflictTest1(float *matrix, float *matrixTest, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // 列坐标
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // 行坐标
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
* 功能：每个块内的每个元素计算改块内一行的和
* 说明：块内每行的计算完全相同，由于多申请一个，所以每一行的会同时访问不同的 bank
* 输入：matrix 输入矩阵
* 输出：matrixTest 输出矩阵
* 输入：row 行数
* 输入：col 列数
*/
__global__ void SharedMemoryBankConflictTest1_Pad(float *matrix, float *matrixTest, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // 列坐标
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // 行坐标
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
* 功能：第一个测试示例，避免 bank conflict
* 输入：matrix_Dev 输入矩阵
* 输入：row 行数
* 输入：col 列数
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

	// 记录时间
	cudaEvent_t start_GPU, end_GPU;
	float elaspsedTime;
	cudaEventCreate(&start_GPU);
	cudaEventCreate(&end_GPU);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start_GPU, 0);

	SharedMemoryBankConflictTest1<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, matrixTestA_Dev, row, col);

	// 计时结束
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);

	std::cout << "Test1 的运行时间为：" << elaspsedTime << "ms." << std::endl;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start_GPU, 0);

	SharedMemoryBankConflictTest1_Pad<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, matrixTestB_Dev, row, col);

	// 计时结束
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);

	std::cout << "Test1 的运行时间为：" << elaspsedTime << "ms." << std::endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cudaMemcpy(matrixTestA_Host, matrixTestA_Dev, row * col * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(matrixTestB_Host, matrixTestB_Dev, row * col * sizeof(float), cudaMemcpyDeviceToHost);

	std::cout << "结果是否相同：" << IsEqualMatrix(matrixTestA_Host, matrixTestB_Host, row, col) << std::endl;

	cudaEventDestroy(start_GPU);
	cudaEventDestroy(end_GPU);

	cudaFree(matrixTestA_Dev);
	cudaFree(matrixTestB_Dev);
	free(matrixTestA_Host);
	free(matrixTestB_Host);
}