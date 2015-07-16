#include "MyCuda.h"

/**
* ��GPU���� Interleaved Addressing ���ϼ�������ĺ�
* Interleaved Addressing �ĺ���˼�����ڽ���Ѱַ�������͵���״ģ��
* �Ż����Ľ� Reduce0 ��ȡ�����Ч�ʽϵ͵�����
* ���⣺ÿ��warp�ж�����ַ�֧��Ч�ʵ�
* globalInputData  �������ݣ�λ��ȫ���ڴ�
* globalOutputData ������ݣ�λ��ȫ���ڴ�
*/
__global__ void reduce1(float *globalInputData, float *globalOutputData, unsigned int n)
{
	__shared__ float sdata[BLOCK_SIZE];

	// ��������
	unsigned int tid = threadIdx.x;
	unsigned int index = blockIdx.x*blockDim.x + threadIdx.x;

	// ���ݶ��빲���ڴ�
	sdata[tid] = (index < n) ? globalInputData[index] : 0; // ������Χ����0

	__syncthreads(); // ͬ�����ȴ�ͬһ��block�ڵ����ݶ������������ڴ�

	// �ڹ����ڴ��ж�ÿһ������й�Լ����
	for (unsigned int s = 1; s < blockDim.x; s *= 2)
	{
		index = 2 * s * tid;

		if (index < blockDim.x)
		{
			sdata[index] += sdata[index + s];
		}

		__syncthreads();
	}

	// �Ѽ������ӹ����ڴ�д��ȫ���ڴ�
	if (tid == 0)
	{
		globalOutputData[blockIdx.x] = sdata[0];
	}
}

/**
* ����reduce1������ʱ��
* fMatrix_Host  ����ͷָ��
* iRow          ��������
* iCol          ��������
* @return       ��
*/
float RuntimeOfReduce1(float *fMatrix_Host, const int iRow, const int iCol)
{
	// ������ά���Ƿ���ȷ
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return 0.0;
	}

	float *fReuslt = (float*)malloc(sizeof(float));;
	float *fMatrix_Device; // ָ���豸�Դ�
	int iMatrixSize = iRow * iCol; // ����Ԫ�ظ���

	HANDLE_ERROR(cudaMalloc((void**)&fMatrix_Device, iMatrixSize * sizeof(float))); // ���Դ���Ϊ���󿪱ٿռ�
	HANDLE_ERROR(cudaMemcpy(fMatrix_Device, fMatrix_Host, iMatrixSize * sizeof(float), cudaMemcpyHostToDevice)); // �����ݿ������Դ�

	// ��¼��ʼʱ��
	cudaEvent_t start_GPU, end_GPU;
	float elaspsedTime;

	cudaEventCreate(&start_GPU);
	cudaEventCreate(&end_GPU);
	cudaEventRecord(start_GPU, 0);

	for (int i = 1, int iNum = iMatrixSize; i < iMatrixSize; i = i*BLOCK_SIZE)
	{
		int iBlockNum = (iNum + BLOCK_SIZE - 1) / BLOCK_SIZE;
		reduce1<<<iBlockNum, BLOCK_SIZE>>>(fMatrix_Device, fMatrix_Device, iNum);
		iNum = iBlockNum;
	}

	HANDLE_ERROR(cudaMemcpy(fReuslt, fMatrix_Device, sizeof(float), cudaMemcpyDeviceToHost)); // �����ݿ������ڴ�

	// ��ʱ����
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);
	cudaEventDestroy(start_GPU);
	cudaEventDestroy(end_GPU);

	std::cout << "Reduce1 ������ʱ��Ϊ��" << elaspsedTime << "ms." << std::endl;

	HANDLE_ERROR(cudaFree(fMatrix_Device));// �ͷ��Դ�ռ�

	return fReuslt[0];
}
