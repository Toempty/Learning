#include <iostream>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cufft.h>

#define NX 3335 // 有效数据个数
#define Nfft 128
#define BLOCK_SIZE 32
using std::cout;
using std::endl;


/**
* 功能：判断两个 cufftComplex 数组的是否相等
* 输入：idataA 输入数组A的头指针
* 输入：idataB 输出数组B的头指针
* 输入：size 数组的元素个数
* 返回：true | false
*/
bool IsEqual(cufftComplex *idataA, cufftComplex *idataB, const int size)
{
	for (int i = 0; i < size; i++)
	{
		if (abs(idataA[i].x - idataB[i].x) > 0.000001 || abs(idataA[i].y - idataB[i].y) > 0.000001)
			return false;
	}

	return true;
}



/**
* 功能：实现 cufftComplex 数组的尺度缩放，也就是乘以一个数
* 输入：idata 输入数组的头指针
* 输出：odata 输出数组的头指针
* 输入：size 数组的元素个数
* 输入：scale 缩放尺度
*/
__global__ void CufftComplexScale(cufftComplex *idata, cufftComplex *odata, float scale)
{
	// 坐标索引
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // 列坐标
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // 行坐标
	int index = y_id * NX + x_id;

	if (x_id < NX && y_id < Nfft)
	{
		odata[index].x = idata[index].x * scale;
		odata[index].y = idata[index].y * scale;
	}
}

int main()
{
	/* 开辟设备端的内存空间 */
	cufftComplex *data_dev;
	cudaMalloc((void**)&data_dev, Nfft * NX * sizeof(cufftComplex)); // 开辟设备内存
	cudaMemset(data_dev, 0, Nfft * NX * sizeof(cufftComplex)); // 初始为0

	/* 开辟主机端的内存空间 */
	cufftComplex *data_Host = (cufftComplex*)malloc(Nfft * NX * sizeof(cufftComplex)); // 主机端数据头指针
	cufftComplex *resultFFT = (cufftComplex*)malloc(Nfft * NX * sizeof(cufftComplex)); // 正变换的结果
	cufftComplex *resultIFFT = (cufftComplex*)malloc(Nfft * NX * sizeof(cufftComplex)); // 先正变换后逆变换的结果


	/* 初始数据 */
	for (int i = 0; i < Nfft * NX; i++)
	{
		data_Host[i].x = float((rand() * rand()) % NX) / NX;
		data_Host[i].y = float((rand() * rand()) % NX) / NX;
	}

	/* 线程块和线程格 */
	dim3 dimBlock2D(BLOCK_SIZE, BLOCK_SIZE);
	dim3 dimGrid2D_NX_Nfft((NX + BLOCK_SIZE - 1) / dimBlock2D.x, (Nfft + BLOCK_SIZE - 1) / dimBlock2D.y);

	/* 申请 cufft 句柄*/
	cufftHandle plan_NX_Many; // 创建cuFFT句柄
	int number_NX[1] = { NX };
	cufftPlanMany(&plan_NX_Many, 1, number_NX, NULL, 1, NX, NULL, 1, NX, CUFFT_C2C, Nfft);

	/* 核心部份 */

	cudaMemcpy(data_dev, data_Host, Nfft * NX * sizeof(cufftComplex), cudaMemcpyHostToDevice);
	cufftExecC2C(plan_NX_Many, data_dev, data_dev, CUFFT_FORWARD); // 执行 cuFFT，正变换
	cufftExecC2C(plan_NX_Many, data_dev, data_dev, CUFFT_INVERSE); // 执行 cuFFT，逆变换
	CufftComplexScale<<<dimGrid2D_NX_Nfft, dimBlock2D>>>(data_dev, data_dev, 1.0f / NX); // 乘以系数
	cudaMemcpy(resultIFFT, data_dev, Nfft * NX * sizeof(cufftComplex), cudaMemcpyDeviceToHost);


	/* 销毁句柄 */
	cufftDestroy(plan_NX_Many);

	/* 释放设备空间 */
	cudaFree(data_dev);


	/* 输出结果 */
	cout << IsEqual(data_Host, resultIFFT, NX * Nfft) << endl;

	return 0;
}