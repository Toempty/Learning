#ifndef MYCUDA_H
#define MYCUDA_H

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <iostream>

// cuda���������ж����
// ȷ��cuda������ȷִ��
static void HandleError(cudaError_t err, const char *file, int line)
{
	if (err != cudaSuccess)
	{
		std::cout << "The file : " << file << " error in line " << line << "!" << std::endl;
		std::cout << "The error code is : " << cudaGetErrorString(err) << std::endl;
	}
}

// �궨��
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define BLOCK_SIZE 256 // �߳̿�Ĵ�С

float RuntimeOfReduceThrust(float *fMatrix_Host, const int iRow, const int iCol); // ReduceThrust �����ʱ��
float RuntimeOfReduce0(float *fMatrix_Host, const int iRow, const int iCol); // Reduce0 �����ʱ��
float RuntimeOfReduce1(float *fMatrix_Host, const int iRow, const int iCol); // Reduce1 �����ʱ��
float RuntimeOfReduce2(float *fMatrix_Host, const int iRow, const int iCol); // Reduce2 �����ʱ��
float RuntimeOfReduce3(float *fMatrix_Host, const int iRow, const int iCol); // Reduce3 �����ʱ��
float RuntimeOfReduce4(float *fMatrix_Host, const int iRow, const int iCol); // Reduce4 �����ʱ��

#endif // !MYCUDA_H
