#include "CountingSortCPU.h"
#include <iostream>
#include <vector>

using namespace std;

/************************************************************************/
/*��������CountingSort
/*��  �ܣ���������
/*����ֵ����
/************************************************************************/
void CountingSort(int *A, int *B, const int SIZE, const int k)
{
	vector<int> C(k + 1, 0); // ����C���鲢��ʼ��

	// C�������ӦA��Ԫ�ص�ֵ��ͳ��A��Ԫ�صĸ���
	for (int i = 0; i < SIZE; i++)
		C[A[i]]++;

	// C�м����ۼӣ���ʱA[i]��ӦC�е�A[i]��
	// C[i]��������i��Ԫ�ظ���
	for (int i = 1; i <= k; ++i)
		C[i] += C[i - 1];

	// ��C[A[i]]���Ԫ�ؼ�ΪA[i]��B�е���ȷλ��
	// �����±�Ӧ��0��ʼ�������C[A[j]]��ȥ1
	// C[i]����С�ڵ���i��Ԫ�ظ���
	for (int i = SIZE - 1; i >= 0; i--)
	{
		B[C[A[i]] - 1] = A[i];
		C[A[i]]--; // ����ͬԪ�صĻ�����ͬԪ������ǰ��
	}
}