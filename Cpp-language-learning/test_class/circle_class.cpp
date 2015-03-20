//circle_class.cpp
//2014. 7. 23
//by lichao

#include <iostream>
#include "circle_class.h"

using namespace std;

circle::circle()
{
	x = 0;
	y = 0;
	r = 1;

	pi = 3.141593;

	calculate_perimeter();
	calculate_area();
}

circle::circle(double x, double y, double r)
{
	if(r <= 0)
	{
		cout << "error! r <= 0! Please input right r." << endl;
	}
	else
	{
		this->r = r;
	}


	this->x = x;
	this->y = y;

	pi = 3.141593;

	calculate_perimeter();
	calculate_area();
}

circle::~circle()
{

}

void circle::translation_xy(double offset_x, double offset_y)
{
	x += offset_x;
	y += offset_y;
}

void circle::zoom_r(double alpha)
{
	if(alpha <= 0)
	{
		cout << "error! r <= 0! Please input right alpha." << endl;
	}
	else
	{
			r *= alpha;
	}
	calculate_perimeter();
	calculate_area();
}


void circle::show_information()
{
	cout << "(x, y) = " << "(" << x << ", " << y << ")" << endl;
	cout << "r = " << r << endl;
	cout << "perimeter = " << perimeter << endl;
	cout << "area = " << area << endl;
}




