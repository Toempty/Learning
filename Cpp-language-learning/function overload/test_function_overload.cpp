#include <iostream>

using namespace std;

//矩形面积，只有一个参数表示正方形
//double型
double rect_area(double a)
{
	cout << "square-double" << endl;
	return a*a;
}

//矩形面积，只有一个参数表示正方形
//int型
int rect_area(int a)
{
	cout << "square-int" << endl;
	return a*a;
}


//矩形面积，两个参数表示长方形
double rect_area(double a, double b)
{
	cout << "rectangle-double" << endl;
	return a*b;
}

int main()
{
	double a = 1.5;
	double b = 2;
	int c = 1.5;

	cout << "square: " << rect_area(a) << endl << endl;
	cout << "rectangle: " << rect_area(a,b) << endl << endl;
	cout << "square: " << rect_area(c) << endl << endl;

	system("pause");
	return 0;
}
