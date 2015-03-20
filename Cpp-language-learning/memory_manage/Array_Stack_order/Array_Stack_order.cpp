#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    const int N(200000); // 定义常数
    int idata[N] = {0}; // 栈空间
    int *pdata = new int[N]; // 堆空间

    clock_t startTime, endTime;
    startTime = clock();

    for (int k = 0; k < 1000; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            idata[i] = i;
        }
    }


    endTime = clock();
    cout << "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    startTime = clock();
    for (int k = 0; k < 1000; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            pdata[i] = i;
        }
    }


    endTime = clock();

    cout << "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    return 0;
}

