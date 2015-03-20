#include <iostream>

using namespace std;

void swap_v(int a, int b);
void swap_r(int &a, int &b);
void swap_p(int *a, int *b);

int main()
{
	int A = 100;
	int B = 200;

	cout << "Before : A="  << A << " B="  << B << endl;
	cout << "Using value to swap contents:" << endl;
	swap_v(A, B);
	cout << "After  : A="  << A << " B="  << B << endl;
	cout << "==================================" << endl;

	cout << "Before : A="  << A << " B="  << B << endl;
	cout << "Using point to swap contents:" << endl;
	swap_p(&A, &B);
	cout << "After  : A="  << A << " B="  << B << endl;
	cout << "==================================" << endl;

	cout << "Before : A="  << A << " B="  << B << endl;
	cout << "Using reference to swap contents:" << endl;
	swap_r(A, B);
	cout << "After  : A="  << A << " B="  << B << endl;

	system("pause");
}

void swap_v(int a, int b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}


void swap_p(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void swap_r(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

