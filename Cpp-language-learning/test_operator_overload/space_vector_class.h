//space_vector_class.h
//2014. 7. 29
//by lichao

#ifndef SPACE_VECTOR_CLASS_H
#define SPACE_VECTOR_CLASS_H

#include <iostream>

class space_vector
{
private:
	double x;
	double y;
	double z;
	double length; // length of vector

	void length_vector()
	{
		this->length = sqrt(x*x + y*y + z*z);
	}

public:

	space_vector();
	space_vector(double x, double y, double z);
	~space_vector();

	space_vector add_vector(const space_vector & v) const;
	space_vector operator+(const space_vector & v) const;
	void show_vector();
	
};

#endif // SPACE_VECTOR_CLASS_H
