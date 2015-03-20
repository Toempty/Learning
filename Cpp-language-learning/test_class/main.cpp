//main.cpp
//2014. 7. 23
//by lichao

#include <iostream>
#include "circle_class.h"

using namespace std;

int main()
{
	circle circle1(1,1,2);
	circle1.show_information();

	circle1.zoom_r(2);
	circle1.show_information();

	circle1.translation_xy(3,3);
	circle1.show_information();

	system("pause");
	return 0;
}
