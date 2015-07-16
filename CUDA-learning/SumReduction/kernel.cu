#include "MyCuda.h"
#include "CpuMatrix.h"

using namespace std;

int main(void)
{
	const int iRow = 1000;
	const int iCol = 1000;

	float *fMatrix_Host = (float*)malloc(iRow * iCol * sizeof(float)); // ���ٿռ�; // ָ�������ڴ�
	GenerateMatrix(fMatrix_Host, iRow, iCol); // �����������

	float thrustResult = RuntimeOfReduceThrust(fMatrix_Host, iRow, iCol);;
	cout << thrustResult << endl;

	float fReduce0Result = RuntimeOfReduce0(fMatrix_Host, iRow, iCol);
	cout << fReduce0Result << endl;

	float fReduce1Result = RuntimeOfReduce1(fMatrix_Host, iRow, iCol);
	cout << fReduce1Result << endl;

	float fReduce2Result = RuntimeOfReduce2(fMatrix_Host, iRow, iCol);
	cout << fReduce2Result << endl;

	float fReduce4Result = RuntimeOfReduce3(fMatrix_Host, iRow, iCol);
	cout << fReduce4Result << endl;

	float fReduce5Result = RuntimeOfReduce4(fMatrix_Host, iRow, iCol);
	cout << fReduce5Result << endl;

	float fCpuResult = RunTimeOfCpu(fMatrix_Host, iRow, iCol);
	cout << fCpuResult << endl;

	free(fMatrix_Host);

	system("pause");
	return 0;
}