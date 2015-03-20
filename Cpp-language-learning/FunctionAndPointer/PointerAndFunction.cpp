#include <iostream>

using namespace std;

void SetA(int iA)
{
    cout << hex << "iA   = " << iA << endl;
    cout << hex << "&iA  = " << &iA << endl;
    iA = 4;
    cout << hex << "iA   = " << iA << endl;
    cout << hex << "&iA  = " << &iA << endl;
}

int main()
{
    int a = 3;

    cout << hex << "a   = " << a << endl;
    cout << hex << "&a  = " << &a << endl;

    SetA(a);

    cout << hex << "a   = " << a << endl;
    cout << hex << "&a  = " << &a << endl;
    return 0;
}
