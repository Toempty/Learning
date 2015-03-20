#include <iostream>
#include <string>

using namespace std;

// cout 输出char或者string类型，会自动寻找'\0'作为结束标准
int main()
{
    const int N(13); // 定义常数

    //////////////char数组//////////////////////////////////////
    char a[N] = "Hello World!"; // 如果N=12则出错
    cout << "a = " << a << endl;

    char b3[5] = {'1', '2', '3', '4', '\0'}; // 字符串
    char b2[5] = {'a', 'b', 'c', 'd', 'e'}; // 非字符串
    char b[N - 1] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '?'};
    cout << "b = " << b << endl;

    //////////////char数组//////////////////////////////////////

    cout << "------------------------------" << endl;

    //////////////char转string/////////////////////////////////
    cout << "char数组转string : Method 1" << endl;
    string str1(a); // 向构造函数传入c字符串创建string对象
    cout << "str1 = " << str1 << endl;

    cout << "char数组转string : Method 2" << endl;
    string str2 = a; // 使用拷贝构造函数创建string对象
    cout << "str2 = " << str2 << endl;

    cout << "char数组转string : Method 3" << endl;
    string str3;
    str3 = a; // c++标准库编写的string类的内部重载了赋值运算符
    cout << "str3 = " << str3 << endl;
    //////////////char转string/////////////////////////////////

    cout << "------------------------------" << endl;

    //////////////cout << char////////////////////////////////
    char c1[N] = "Hello Chars!";
    char c[N] = "Hello Chars!";
    cout << "c = " << c << endl;

    c[N - 1] = '?';

    cout << "new c = " << c << endl;

    string str4 = c;
    cout << "str4 = " << str4 << endl;
    //////////////cout << char////////////////////////////////

    return 0;
}
