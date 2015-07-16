#include "MyCuda.h"

#include <thrust\device_vector.h>
#include <thrust\host_vector.h>
#include <thrust\device_ptr.h>

/**
* 计算reduce1函数的时间
* fMatrix_Host  矩阵头指针
* iRow          矩阵行数
* iCol          矩阵列数
* @return       和
*/
float RuntimeOfReduceThrust(float *fMatrix_Host, const int iRow, const int iCol)
{
	// 检查矩阵维度是否正确
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return 0.0;
	}

	float *fMatrix_Device; // 指向设备显存
	int iMatrixSize = iRow * iCol; // 矩阵元素个数

	cudaMalloc((void**)&fMatrix_Device, iMatrixSize * sizeof(float)); // 在显存中为矩阵开辟空间
	cudaMemcpy(fMatrix_Device, fMatrix_Host, iMatrixSize * sizeof(float), cudaMemcpyHostToDevice); // 将数据拷贝到显存

	cudaEvent_t start_GPU, end_GPU;
	float elaspsedTime;

	cudaEventCreate(&start_GPU);
	cudaEventCreate(&end_GPU);
	cudaEventRecord(start_GPU, 0);

	thrust::device_ptr<float> dev_ptr(fMatrix_Device);
	float thrustResult = thrust::reduce(dev_ptr, dev_ptr + size_t(iMatrixSize), (float)0, thrust::plus<float>());

	// 计时结束
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);
	cudaEventDestroy(start_GPU);
	cudaEventDestroy(end_GPU);

	std::cout << "GPU的运行时间为：" << elaspsedTime << "ms." << std::endl;

	cudaFree(fMatrix_Device);

	return thrustResult;
}
