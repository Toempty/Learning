#include <iostream>
#include <time.h>

using namespace std;


int main()
{
    clock_t start, end;
    int N = 32;
    int var[32] = {0};
    int var1[32] = {1};
    int var_test = 0;

    for(int i = 0; i < N; i++)
        var1[i] = var[i] = i;

    start = clock();

    for (int i = 0; i < N*100000; i++)
    {
        int j = i % N;
        var_test = var[j];
        if(j == 0)
            var[j] = var[j] + 1;
        else
            var[j] = var [j] + 2;
        var[j] = var[j] * 3;
        var[j] = var_test;
    }

    end = clock();
    cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;



    start = clock();

    for (int i = 0; i < N*100000; i++)
    {
        int j = i % N;
        var_test = var1[j];
        var1[j] = (var1[j] + 1 + (var1[j] > 0)) * 3;
        var1[j] = var_test;
    }

    end = clock();
    cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;

    for(int i = 0; i < N; i++)
        cout << var[i] - var1[i] << endl;

  return 0;
}
