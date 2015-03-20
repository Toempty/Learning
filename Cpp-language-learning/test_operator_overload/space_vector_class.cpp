//space_vector_class.cpp
//2014. 7. 29
//by lichao

#include <iostream>
#include "space_vector_class.h"

using namespace std; 

space_vector::space_vector()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;

	this->length_vector();
}

space_vector::space_vector(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->length_vector();
}

space_vector::~space_vector()
{

}

space_vector space_vector::add_vector(const space_vector & v) const
{
	space_vector added_vector;
	added_vector.x = x + v.x;
	added_vector.y = y + v.y;
	added_vector.z = z + v.z;

	added_vector.length_vector();
	return added_vector;
}

space_vector space_vector::operator+(const space_vector & v) const
{
	space_vector added_vector;
	added_vector.x = x + v.x;
	added_vector.y = y + v.y;
	added_vector.z = z + v.z;

	added_vector.length_vector();
	return added_vector;
}

void space_vector::show_vector()
{
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "z = " << z << endl;
	cout << "length = " << length << endl;
}