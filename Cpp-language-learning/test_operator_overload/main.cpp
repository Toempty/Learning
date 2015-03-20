//main.cpp
//2014. 7. 29
//by lichao

#include <iostream>
#include "space_vector_class.h"

using namespace std;

int main()
{
	space_vector v1(1.0,1.0,1.0);
	v1.show_vector();

	space_vector v2(2.0,2.0,2.0);
	v2.show_vector();

	space_vector v3;
	v3 = v2.add_vector(v1);
	v3.show_vector();

	space_vector v4;
	v4 = v2 + v1;
	v4.show_vector();

	system("pause");
	return 0;
}