#include <iostream>

using namespace std;

int main()
{
	int A = 100;

	int &C = A;
	int &D = C;
	int &E = D;

	cout << A << " " << C << " " << D << " " << E << endl;
	cout << "==================================" << endl;

	C++;
	cout << A << " " << C << " " << D << " " << E << endl;
	cout << "==================================" << endl;

	D++;
	cout << A << " " << C << " " << D << " " << E << endl;
	cout << "==================================" << endl;

	E++;
	cout << A << " " << C << " " << D << " " << E << endl;
	cout << "==================================" << endl;


	system("pause");
}

