#include "MyCuda.h"
#include "CpuMatrix.h"

using namespace std;

int main(void)
{
	const int iRow = 11000;
	const int iCol = 11000;

	float *fMatrix_Host = (float*)malloc(iRow * iCol * sizeof(float)); // 开辟空间; // 指向主机内存
	GenerateMatrix(fMatrix_Host, iRow, iCol); // 产生随机矩阵

	float thrustResult = RuntimeOfReduceThrust(fMatrix_Host, iRow, iCol);;
	cout << thrustResult << endl;

	float fReduce0Result = RuntimeOfReduce0(fMatrix_Host, iRow, iCol);
	cout << fReduce0Result << endl;

	float fReduce1Result = RuntimeOfReduce1(fMatrix_Host, iRow, iCol);
	cout << fReduce1Result << endl;

	float fReduce2Result = RuntimeOfReduce2(fMatrix_Host, iRow, iCol);
	cout << fReduce2Result << endl;

	float fReduce3Result = RuntimeOfReduce3(fMatrix_Host, iRow, iCol);
	cout << fReduce3Result << endl;

	float fReduce4Result = RuntimeOfReduce4(fMatrix_Host, iRow, iCol);
	cout << fReduce4Result << endl;

	float fCpuResult = RunTimeOfCpu(fMatrix_Host, iRow, iCol);
	cout << fCpuResult << endl;

	free(fMatrix_Host);

	system("pause");
	return 0;
}