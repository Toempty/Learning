#include <iostream>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cufft.h>

#define NX 3335 // ��Ч���ݸ���
#define N 5335 // ��0֮������ݳ���
#define BATCH 1
#define BLOCK_SIZE 1024
using std::cout;
using std::endl;


/**
* ���ܣ��ж����� cufftComplex ������Ƿ����
* ���룺idataA ��������A��ͷָ��
* ���룺idataB �������B��ͷָ��
* ���룺size �����Ԫ�ظ���
* ���أ�true | false
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
* ���ܣ�ʵ�� cufftComplex ����ĳ߶����ţ�Ҳ���ǳ���һ����
* ���룺idata ���������ͷָ��
* �����odata ��������ͷָ��
* ���룺size �����Ԫ�ظ���
* ���룺scale ���ų߶�
*/
static __global__ void cufftComplexScale(cufftComplex *idata, cufftComplex *odata, const int size, float scale)
{
	const int threadID = blockIdx.x * blockDim.x + threadIdx.x;

	if (threadID < size)
	{
		odata[threadID].x = idata[threadID].x * scale;
		odata[threadID].y = idata[threadID].y * scale;
	}
}

int main()
{
	cufftComplex *data_dev; // �豸������ͷָ��
	cufftComplex *data_Host = (cufftComplex*)malloc(NX*BATCH*sizeof(cufftComplex)); // ����������ͷָ��
	cufftComplex *resultFFT = (cufftComplex*)malloc(N*BATCH*sizeof(cufftComplex)); // ���任�Ľ��
	cufftComplex *resultIFFT = (cufftComplex*)malloc(NX*BATCH*sizeof(cufftComplex)); // �����任����任�Ľ��

	// ��ʼ����
	for (int i = 0; i < NX; i++)
	{
		data_Host[i].x = float((rand() * rand()) % NX) / NX;
		data_Host[i].y = float((rand() * rand()) % NX) / NX;
	}

	
	dim3 dimBlock(BLOCK_SIZE); // �߳̿�
	dim3 dimGrid((NX + BLOCK_SIZE - 1) / dimBlock.x); // �̸߳�

	cufftHandle plan; // ����cuFFT���
	cufftPlan1d(&plan, N, CUFFT_C2C, BATCH);

	// ��ʱ
	clock_t start, stop;
	double duration;
	start = clock();

	cudaMalloc((void**)&data_dev, sizeof(cufftComplex)*N*BATCH); // �����豸�ڴ�
	cudaMemset(data_dev, 0, sizeof(cufftComplex)*N*BATCH); // ��ʼΪ0
	cudaMemcpy(data_dev, data_Host, NX *sizeof(cufftComplex), cudaMemcpyHostToDevice); // �������ڴ濽�����豸�ڴ�

	cufftExecC2C(plan, data_dev, data_dev, CUFFT_FORWARD); // ִ�� cuFFT�����任
	cudaMemcpy(resultFFT, data_dev, N * sizeof(cufftComplex), cudaMemcpyDeviceToHost); // ���豸�ڴ濽���������ڴ�

	cufftExecC2C(plan, data_dev, data_dev, CUFFT_INVERSE); // ִ�� cuFFT����任
	cufftComplexScale<<<dimGrid, dimBlock>>>(data_dev, data_dev, N, 1.0f / N); // ����ϵ��
	cudaMemcpy(resultIFFT, data_dev, NX * sizeof(cufftComplex), cudaMemcpyDeviceToHost); // ���豸�ڴ濽���������ڴ�

	stop = clock();
	duration = (double)(stop-start)*1000/CLOCKS_PER_SEC;
	cout << "ʱ��Ϊ " << duration << " ms" << endl;

	cufftDestroy(plan); // ���پ��
	cudaFree(data_dev); // �ͷſռ�

	cout << IsEqual(data_Host, resultIFFT, NX) << endl;

	return 0;
}