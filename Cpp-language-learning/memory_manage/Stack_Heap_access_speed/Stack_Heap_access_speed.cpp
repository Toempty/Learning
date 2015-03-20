#include <iostream>
#include <time.h>

using namespace std;

// Stack accessing time: 0.381S
// Heap accessing time: 0.408S

// 局部变量在栈空间
// new，malloc动态分配在堆空间

int main()
{
    const int N(200000); // 定义常数
    int idata[N] = {0}; // 栈空间
    int *pdata = new int[N]; // 堆空间

    // 栈空间访问
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
    cout << "Stack accessing time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    // 堆空间访问
    startTime = clock();
    for (int k = 0; k < 1000; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            pdata[i] = i;
        }
    }

    endTime = clock();

    cout << "Heap accessing time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    return 0;
}

