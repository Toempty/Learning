#include <iostream>

using namespace std;

int main()
{
    int a = 3;
    int *b = &a; // int *b; b = &a;
    int **c = &b; // int **c; c = &b;

    cout << hex << "a   = " << a << endl;
    cout << hex << "&a  = " << &a << endl;

    cout << hex << "b   = " << b << endl;
    cout << hex << "*b  = " << *b << endl;
    cout << hex << "&b  = " << &b << endl;

    cout << hex << "c   = " << c << endl;
    cout << hex << "*c  = " << *c << endl;
    cout << hex << "**c = " << **c << endl;
    cout << hex << "&c  = " << &c << endl;

    return 0;
}
