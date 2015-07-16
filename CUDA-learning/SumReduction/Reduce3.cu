#include "MyCuda.h"

/**
* 优化：避免了 reduce0 和 reduce1 中存在的 warp 分支现象，进一步提高效率
* 优化：解决 reduce2 中线程利用率低的问题，在数据拷贝到共享内存之前，首先
*       执行一次合并，进一步提高线程利用率
* 问题：1.当每个块中的剩余元素小于等于32个时，依然会执行同步操作。但，实际上每个warp都是默
*       认同步的，不用额外的同步操作。
* globalInputData  输入数据，位于全局内存
* globalOutputData 输出数据，位于全局内存
*/
__global__ void reduce3(float *globalInputData, float *globalOutputData, unsigned int n)
{
	__shared__ float sdata[BLOCK_SIZE];

	// 坐标索引
	unsigned int tid = threadIdx.x;
	unsigned int index = blockIdx.x*(blockDim.x * 2) + threadIdx.x;
	unsigned int indexWithOffset = index + blockDim.x;

	if (index >= n)
	{
		sdata[tid] = 0;
	}
	else if (indexWithOffset >= n)
	{
		sdata[tid] = globalInputData[index];
	}
	else
	{
		sdata[tid] = globalInputData[index] + globalInputData[indexWithOffset];
	}
	__syncthreads();

	// 在共享内存中对每一个块进行规约计算
	for (unsigned int s = blockDim.x / 2; s>0; s >>= 1)
	{
		if (tid < s)
		{
			sdata[tid] += sdata[tid + s];
		}

		__syncthreads();
	}

	// 把计算结果从共享内存写回全局内存
	if (tid == 0)
	{
		globalOutputData[blockIdx.x] = sdata[0];
	}
}

/**
* 计算reduce3函数的时间
* fMatrix_Host  矩阵头指针
* iRow          矩阵行数
* iCol          矩阵列数
* @return       和
*/
float RuntimeOfReduce3(float *fMatrix_Host, const int iRow, const int iCol)
{
	// 检查矩阵维度是否正确
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return 0.0;
	}

	float *fReuslt = (float*)malloc(sizeof(float));;
	float *fMatrix_Device; // 指向设备显存
	int iMatrixSize = iRow * iCol; // 矩阵元素个数

	HANDLE_ERROR(cudaMalloc((void**)&fMatrix_Device, iMatrixSize * sizeof(float))); // 在显存中为矩阵开辟空间
	HANDLE_ERROR(cudaMemcpy(fMatrix_Device, fMatrix_Host, iMatrixSize * sizeof(float), cudaMemcpyHostToDevice)); // 将数据拷贝到显存

	// 记录起始时间
	cudaEvent_t start_GPU, end_GPU;
	float elaspsedTime;

	cudaEventCreate(&start_GPU);
	cudaEventCreate(&end_GPU);
	cudaEventRecord(start_GPU, 0);

	for (int i = 1, int iNum = iMatrixSize; i < iMatrixSize; i = 2 * i*BLOCK_SIZE)
	{
		int iBlockNum = (iNum + (2 * BLOCK_SIZE) - 1) / (2 * BLOCK_SIZE);
		reduce3<<<iBlockNum, BLOCK_SIZE>>>(fMatrix_Device, fMatrix_Device, iNum);
		iNum = iBlockNum;
	}

	HANDLE_ERROR(cudaMemcpy(fReuslt, fMatrix_Device, sizeof(float), cudaMemcpyDeviceToHost)); // 将数据拷贝到内存

	// 计时结束
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);
	cudaEventDestroy(start_GPU);
	cudaEventDestroy(end_GPU);

	std::cout << "GPU的运行时间为：" << elaspsedTime << "ms." << std::endl;

	HANDLE_ERROR(cudaFree(fMatrix_Device));// 释放显存空间

	return fReuslt[0];
}