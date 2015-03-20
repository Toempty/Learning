#include <iostream>

using namespace std;

void SetA(int **iA)
{
    cout << hex << "iA   = " << iA << endl;
    cout << hex << "&iA  = " << &iA << endl;
    cout << hex << "*iA  = " << *iA << endl;
    cout << hex << "**iA = " << **iA << endl;
    **iA = 4;
    cout << hex << "iA   = " << iA << endl;
    cout << hex << "&iA  = " << &iA << endl;
    cout << hex << "*iA  = " << *iA << endl;
    cout << hex << "**iA = " << **iA << endl;
}

int main()
{
    int a = 3;
    int *b = &a; // int *b; b = &a;

    cout << hex << "a    = " << a << endl;
    cout << hex << "&a   = " << &a << endl;

    cout << hex << "b    = " << b << endl;
    cout << hex << "*b   = " << *b << endl;
    cout << hex << "&b   = " << &b << endl;

    SetA(&b);

    cout << hex << "a    = " << a << endl;
    cout << hex << "&a   = " << &a << endl;

    cout << hex << "b    = " << b << endl;
    cout << hex << "*b   = " << *b << endl;
    cout << hex << "&b   = " << &b << endl;

    return 0;
}
