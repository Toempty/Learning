#include <iostream>
#include <Windows.h>

using namespace std;

//#define square(x) (x)*(x)

//inline int square(int x) { return x*x; }

int square(int x)
{
	return x*x;
}

int main()
{
	int x = 3;

	cout << "x=" << x << endl;
	cout << "x^2 = " << square(x) << endl;

	cout << "x=" << x << endl;
	cout << "(x++)^2 = " << square(x++) << endl;

	cout << "x=" << x << endl;
	cout << "(x+1)^2 = " << square(x+1) << endl;

	Sleep(200000);
	return 0;
}
