#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <curand_kernel.h>

#include <iostream>

#include "Test1.h"
#include "Test2.h"
#include "Test3.h"

#define BLOCKSIZE 32

using namespace std;

/**
* ���ܣ����� 0-1 ���������
* �����matrix �������������
* ���룺row ����
* ���룺col ����
*/
__global__ void GenerateMatrixCUDA(float *matrix, int row, int col)
{
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // ������
	int index = y_id * col + x_id;

	curandState s;
	curand_init(index, 0, 0, &s);

	if (x_id < col && y_id < row)
	{
		matrix[index] = curand_uniform(&s);
	}
	//if (x_id < 4 && y_id < 4)
	//	printf("x_id = %d, y_id = %d, value = %f.\n", x_id, y_id, matrix[index]);
}


int main()
{
	const int row = 1024;
	const int col = 1024;

	float *matrix_Dev;
	cudaMalloc((void**)&matrix_Dev, row * col * sizeof(float));

	dim3 dimBlock2D(BLOCKSIZE, BLOCKSIZE);
	dim3 dimGrid2D((col+ BLOCKSIZE - 1) / dimBlock2D.x, (row + BLOCKSIZE - 1) / dimBlock2D.y);
	GenerateMatrixCUDA<<<dimGrid2D, dimBlock2D>>>(matrix_Dev, row, col);

	/* ʵ�� 1 */
	Test1(matrix_Dev, row, col);

	/* ʵ�� 2 */
	Test2(matrix_Dev, row, col);

	/* ʵ�� 3 */
	Test3(matrix_Dev, row, col);

	cudaFree(matrix_Dev);

	cudaDeviceReset();
	return 0;
}