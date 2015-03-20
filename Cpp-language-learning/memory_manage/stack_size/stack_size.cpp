#include <iostream>

using namespace std;

// 1024*1024 = 1 048 576
// 2 M = 2 099 152 Byte = 524 788 * 4 Byte(int)

// 栈超出时，编译可以通过，但是执行的时候将发生错误。
// 当Max > 521152 时，将超出栈的范围(2M)
// 当Max = 521152 时，栈存满，如果此时主函数内还有
// 其他内容，栈也将超出。

// 如果将 int data[Max] = {0}; 放在main函数外将不会超出
// 因为此时data就是全局变量，占用的就是全局/静态区，一般很大

void show()
{
    cout << "Hello World!" << endl;
}

const int Max = 521152;
int main()
{
    int data[Max] = {0};
    //show();

    return 0;
}
