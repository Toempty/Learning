#include <iostream>

using namespace std;

int main()
{
    char str1[] = "Hello world!"; //在栈上分配
    char *str2 = "const"; // 编译器在常量区分配6个字节存储'c','o','n','s','t','\0'， 然后将'c'的指针返回给str2
    char *str3 = str1; // str3与str1指向同一个区域，将共同改变

    cout << "change str1:" << endl << "str1 = ";
    str1[0] = 'X';
    for (int i = 0; i < 12; ++i)
        cout << str1[i];
    cout << endl;

    cout << "str3 = ";
    for (int i = 0; i < 12; ++i)
        cout << str3[i];
    cout << endl;

    cout << "change str3:" << endl << "str3 = ";
    str3[1] = 'Y';
    for (int i = 0; i < 12; ++i)
        cout << str3[i];
    cout << endl;

    cout << "str1 = ";
    for (int i = 0; i < 12; ++i)
        cout << str3[i];
    cout << endl;

    //str2[0] = 'X'; // 如果不注释掉此操作将出错
    cout << "str2 = ";
    for (int i = 0; i < 5; ++i)
        cout << str2[i];
    cout << endl;

    return 0;
}
