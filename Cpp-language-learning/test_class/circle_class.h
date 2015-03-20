//circle_class.h
//2014. 7. 23
//by lichao

#ifndef CIRCLE_CLASS_H_
#define CIRCLE_CLASS_H_

#include <iostream>

class circle
{
private:
	double x;
	double y;
	double r;
	double perimeter;
	double area;
	double pi;

	void calculate_perimeter()
	{
		perimeter = 2 * pi * r;
	}
	void calculate_area()
	{
		area = pi * r * r;
	}
public:
	circle();
	circle(double x, double y, double r);
	~circle();
	void translation_xy(double offset_x, double offset_y);
	void zoom_r(double alpha);
	void show_information();
};

#endif