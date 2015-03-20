/////////////////////////////////////////////////////////////////////////////////////////////
// ofstream: 写操作（输出）的文件类 (由ostream引申而来)
// ifstream: 读操作（输入）的文件类(由istream引申而来)
// fstream:  可同时读写操作的文件类 (由iostream引申而来)
/////////////////////////////////////////////////////////////////////////////////////////////
// 类          参数的默认方式
// ofstream    ios::out | ios::trunc
// ifstream    ios::in
// fstream     ios::in | ios::out
/////////////////////////////////////////////////////////////////////////////////////////////
// ifstream f("data.txt",ios::nocreate);
// 默认以 ios::in 的方式打开文件，文件不存在时操作失败

// ofstream f("data.txt");
// 默认以 ios::out的方式打开文件

// fstream　f("data.dat",ios::in|ios::out|ios::binary);　
//以读写方式打开二进制文件
/////////////////////////////////////////////////////////////////////////////////////////////
// 文件打开方式选项：
// ios::in　= 0x01, 供读，文件不存在则创建(ifstream默认的打开方式)
// ios::out = 0x02, 供写，文件不存在则创建，若文件已存在则清空原内容(ofstream默认的打开方式)
// ios::at  = 0x04, 文件打开时，指针在文件最后。可改变指针的位置，常和in、out联合使用
// ios::app = 0x08, 供写，文件不存在则创建，
// 若文件已存在则在原文件内容后写入新的内容，指针位置总在最后
// ios::trunc = 0x10, 在读写前先将文件长度截断为0（默认）
// ios::nocreate = 0x20, 文件不存在时产生错误，常和in或app联合使用
// ios::noreplace = 0x40, 文件存在时产生错误，常和out联合使用
// ios::binary　　= 0x80　二进制格式文件
/////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
// #include <iomanip>
#include <fstream>

using namespace std;

// 写文件测试
// 写入内容：
// abcdefg
// deage
// 123
// 345.67
void fileWtrieTest()
{
    fstream file;
    file.open("data.txt", ios::out);

    file << "abcdefg" << endl;
    file << "deage" << endl;
    file << 123 << endl;
    file << 345.67 << endl;

    file.close();
}

// 读文件测试
void fileReadTest()
{
    fstream file;
    char str[20];
    int intNum = 0;
    double doubleNum = 0;

    file.open("data.txt", ios::in);

    file >> str;
    cout << str << endl;

    file >> str;
    cout << str << endl;

    file >> intNum;
    cout << intNum << endl;

    file >> doubleNum;
    cout << doubleNum << endl;

    file.close();
}

int main()
{

    fileWtrieTest();

    fileReadTest();

    return 0;
}
