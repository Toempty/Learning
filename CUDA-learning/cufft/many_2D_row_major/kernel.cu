#include <iostream>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cufft.h>

#define NX 3335 // ��Ч���ݸ���
#define Nfft 128
#define BLOCK_SIZE 32
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
__global__ void CufftComplexScale(cufftComplex *idata, cufftComplex *odata, float scale)
{
	// ��������
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // ������
	int y_id = blockDim.y * blockIdx.y + threadIdx.y; // ������
	int index = y_id * NX + x_id;

	if (x_id < NX && y_id < Nfft)
	{
		odata[index].x = idata[index].x * scale;
		odata[index].y = idata[index].y * scale;
	}
}

int main()
{
	/* �����豸�˵��ڴ�ռ� */
	cufftComplex *data_dev;
	cudaMalloc((void**)&data_dev, Nfft * NX * sizeof(cufftComplex)); // �����豸�ڴ�
	cudaMemset(data_dev, 0, Nfft * NX * sizeof(cufftComplex)); // ��ʼΪ0

	/* ���������˵��ڴ�ռ� */
	cufftComplex *data_Host = (cufftComplex*)malloc(Nfft * NX * sizeof(cufftComplex)); // ����������ͷָ��
	cufftComplex *resultFFT = (cufftComplex*)malloc(Nfft * NX * sizeof(cufftComplex)); // ���任�Ľ��
	cufftComplex *resultIFFT = (cufftComplex*)malloc(Nfft * NX * sizeof(cufftComplex)); // �����任����任�Ľ��


	/* ��ʼ���� */
	for (int i = 0; i < Nfft * NX; i++)
	{
		data_Host[i].x = float((rand() * rand()) % NX) / NX;
		data_Host[i].y = float((rand() * rand()) % NX) / NX;
	}

	/* �߳̿���̸߳� */
	dim3 dimBlock2D(BLOCK_SIZE, BLOCK_SIZE);
	dim3 dimGrid2D_NX_Nfft((NX + BLOCK_SIZE - 1) / dimBlock2D.x, (Nfft + BLOCK_SIZE - 1) / dimBlock2D.y);

	/* ���� cufft ���*/
	cufftHandle plan_NX_Many; // ����cuFFT���
	int number_NX[1] = { NX };
	cufftPlanMany(&plan_NX_Many, 1, number_NX, NULL, 1, NX, NULL, 1, NX, CUFFT_C2C, Nfft);

	/* ���Ĳ��� */

	cudaMemcpy(data_dev, data_Host, Nfft * NX * sizeof(cufftComplex), cudaMemcpyHostToDevice);
	cufftExecC2C(plan_NX_Many, data_dev, data_dev, CUFFT_FORWARD); // ִ�� cuFFT�����任
	cufftExecC2C(plan_NX_Many, data_dev, data_dev, CUFFT_INVERSE); // ִ�� cuFFT����任
	CufftComplexScale<<<dimGrid2D_NX_Nfft, dimBlock2D>>>(data_dev, data_dev, 1.0f / NX); // ����ϵ��
	cudaMemcpy(resultIFFT, data_dev, Nfft * NX * sizeof(cufftComplex), cudaMemcpyDeviceToHost);


	/* ���پ�� */
	cufftDestroy(plan_NX_Many);

	/* �ͷ��豸�ռ� */
	cudaFree(data_dev);


	/* ������ */
	cout << IsEqual(data_Host, resultIFFT, NX * Nfft) << endl;

	return 0;
}