#ifndef MYCUDA_H
#define MYCUDA_H

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>

// cuda函数错误判断语句
// 确保cuda程序正确执行
static void HandleError(cudaError_t err, const char *file, int line)
{
	if (err != cudaSuccess)
	{
		std::cout << "The file : " << file << " error in line " << line << "!" << std::endl;
		std::cout << "The error code is : " << cudaGetErrorString(err) << std::endl;
	}
}

// 宏定义
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define BLOCK_SIZE 256 // 线程块的大小

float RuntimeOfReduceThrust(float *fMatrix_Host, const int iRow, const int iCol); // ReduceThrust 的求和时间
float RuntimeOfReduce0(float *fMatrix_Host, const int iRow, const int iCol); // Reduce0 的求和时间
float RuntimeOfReduce1(float *fMatrix_Host, const int iRow, const int iCol); // Reduce1 的求和时间
float RuntimeOfReduce2(float *fMatrix_Host, const int iRow, const int iCol); // Reduce2 的求和时间
float RuntimeOfReduce3(float *fMatrix_Host, const int iRow, const int iCol); // Reduce3 的求和时间
float RuntimeOfReduce4(float *fMatrix_Host, const int iRow, const int iCol); // Reduce4 的求和时间

#endif // !MYCUDA_H
