#include "MyCuda.h"

#include <thrust\device_vector.h>
#include <thrust\host_vector.h>
#include <thrust\device_ptr.h>

/**
* ����reduce1������ʱ��
* fMatrix_Host  ����ͷָ��
* iRow          ��������
* iCol          ��������
* @return       ��
*/
float RuntimeOfReduceThrust(float *fMatrix_Host, const int iRow, const int iCol)
{
	// ������ά���Ƿ���ȷ
	if (iRow <= 0 || iCol <= 0)
	{
		std::cout << "The size of the matrix is error!" << std::endl;
		return 0.0;
	}

	float *fMatrix_Device; // ָ���豸�Դ�
	int iMatrixSize = iRow * iCol; // ����Ԫ�ظ���

	cudaMalloc((void**)&fMatrix_Device, iMatrixSize * sizeof(float)); // ���Դ���Ϊ���󿪱ٿռ�
	cudaMemcpy(fMatrix_Device, fMatrix_Host, iMatrixSize * sizeof(float), cudaMemcpyHostToDevice); // �����ݿ������Դ�

	cudaEvent_t start_GPU, end_GPU;
	float elaspsedTime;

	cudaEventCreate(&start_GPU);
	cudaEventCreate(&end_GPU);
	cudaEventRecord(start_GPU, 0);

	thrust::device_ptr<float> dev_ptr(fMatrix_Device);
	float thrustResult = thrust::reduce(dev_ptr, dev_ptr + size_t(iMatrixSize), (float)0, thrust::plus<float>());

	// ��ʱ����
	cudaEventRecord(end_GPU, 0);
	cudaEventSynchronize(end_GPU);
	cudaEventElapsedTime(&elaspsedTime, start_GPU, end_GPU);
	cudaEventDestroy(start_GPU);
	cudaEventDestroy(end_GPU);

	std::cout << "GPU������ʱ��Ϊ��" << elaspsedTime << "ms." << std::endl;

	cudaFree(fMatrix_Device);

	return thrustResult;
}
