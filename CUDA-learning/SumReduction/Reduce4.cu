#include "MyCuda.h"

/**
* 每个 warp 自动同步，不用 __syncthreads();
* volatile : 加上关键字volatile的变量将被定义为敏感变量，意思是加了volatile
*            的变量在内存中的值可能会随时发生变化，当程序要去读取这个变量时，
             必须要从内存中读取，而不是从缓存中读取
* sdata  数组头指针，数组位于共享内存
* tid    线程索引
*/
__device__ void warpReduce(volatile float *sdata, int tid)
{
	sdata[tid] += sdata[tid + 32];
	sdata[tid] += sdata[tid + 16];
	sdata[tid] += sdata[tid + 8];
	sdata[tid] += sdata[tid + 4];
	sdata[tid] += sdata[tid + 2];
	sdata[tid] += sdata[tid + 1];
}

/**
* 优化：解决了 reduce3 中存在的多余同步操作（每个warp默认自动同步）。
* globalInputData  输入数据，位于全局内存
* globalOutputData 输出数据，位于全局内存
*/
__global__ void reduce4(float *globalInputData, float *globalOutputData, unsigned int n)
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
	for (unsigned int s = blockDim.x / 2; s>32; s >>= 1)
	{
		if (tid < s)
		{
			sdata[tid] += sdata[tid + s];
		}

		__syncthreads();
	}
	if (tid < 32)
	{
		warpReduce(sdata, tid);
	}

	// 把计算结果从共享内存写回全局内存
	if (tid == 0)
	{
		globalOutputData[blockIdx.x] = sdata[0];
	}
}

/**
* 计算 reduce4 函数的时间
* fMatrix_Host  矩阵头指针
* iRow          矩阵行数
* iCol          矩阵列数
* @return       和
*/
float RuntimeOfReduce4(float *fMatrix_Host, const int iRow, const int iCol)
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

	for (int i = 1, int iNum = iMatrixSize; i < iMatrixSize; i = 2 * i * BLOCK_SIZE)
	{
		int iBlockNum = (iNum + (2 * BLOCK_SIZE) - 1) / (2 * BLOCK_SIZE);
		reduce4<<<iBlockNum, BLOCK_SIZE>>>(fMatrix_Device, fMatrix_Device, iNum);
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