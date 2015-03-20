#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>


using namespace std;

// 产生随机数组
template<size_t SIZE>
void gen_rand_n(int (&A)[SIZE])
{
    srand((unsigned)time(0));
    for (int i = 0; i < SIZE; ++i)
    {
        A[i] = rand();
    }
}

// 产生随机字符串
template<size_t Len>
void gen_rand_s(char (&str)[Len])
{
    const int sizeChar = 62;
    char allChar[sizeChar + 1] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand((unsigned)time(0));

    for (int i = 0; i < Len-1; ++i)
    {
        str[i] = allChar[rand() % sizeChar];
    }
    str[Len] = '\0';
}

int main()
{
    const int N(40); // 定义常数
    int A[N] = {0};
    char str[N];
    string strs;

    gen_rand_n(A);

    for (int i = 0; i < N; ++i)
    {
        cout << i+1 << " : " << A[i] << endl;
    }

    gen_rand_s(str);
    strs = str;

    cout << str << endl;
    cout << strs << endl;

    return 0;
}

