#include "GenRandN.h"
#include <iostream>

// MSVC��RAND_MAXͨ��Ϊ0x7fff����32767����Linuxƽ̨��GCC��RAND_MAXͨ����ԶԶ�������ֵ
/************************************************************************/
/*��������GenRandN
/*��  �ܣ�����������飬���ֵ������maxNum
/*����ֵ����
/************************************************************************/
void GenRandN(int *A, const int SIZE, const int maxNum)
{
	srand(5);
	for (int i = 0; i < SIZE; ++i)
		A[i] = (rand() * rand()) % maxNum;
}