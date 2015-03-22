#include "IsOrder.h"

/************************************************************************/
/*��������IsOrder()
/*��  �ܣ��жϺ����Ƿ�����
/*����ֵ������0��1
/************************************************************************/
bool IsOrder(int *A, const int SIZE)
{
	if (1 == SIZE)
		return true;

	int i = 1;
	while (A[i - 1] <= A[i] && i < SIZE)
		i++;

	return SIZE == i ? true : false;
}