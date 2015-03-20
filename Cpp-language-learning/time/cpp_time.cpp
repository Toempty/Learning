#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    clock_t start, end;
    start = clock();

    for (int i = 0; i < 12345678; ++i)
    {
        i = i + 1;
        i = i - 1;
    }

    end = clock();
    cout<<"Run time: "<< (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;

    return 0;
}
