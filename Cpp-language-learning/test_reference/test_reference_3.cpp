#include <iostream>

using namespace std;

int square_v(int a);
int square_r(int &a);

int main()
{
	int A = 100;

	cout << "A = " << A << endl;
	cout << "square_v of A = " << square_v(A) << endl;
	cout << "A = " << A << endl;
	cout << "square_r of A = "  << square_r(A) << endl;
	cout << "A = " << A << endl;

	system("pause");
}

int square_v(int a)
{
	a = a * a;
	return a; 
}

int square_r(int &a)
{
	a = a * a;
	return a; 
}
