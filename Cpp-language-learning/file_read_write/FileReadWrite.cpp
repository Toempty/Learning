#include <iostream>
#include <fstream>

using namespace std;

int FileRead(ifstream &input)
{
    size_t size = 0; // 数据长度
    char *memblocks;

    // ios::end  = 2　相对于文件尾
    // 返回文件尾，用于计算数据长度
    input.seekg(0, ios::end);

    // tellg() 返回当前指针
    // 这两个成员函数不用传入参数，返回pos_type 类型的值
    // 就是一个整数，代表当前get 流指针的位置(用tellg)
    // 或put 流指针的位置(用tellp)
    // 111整数占三个size，
    // 一个字母占一个size
    // 1.11占四个size
    // 换行占两个size
    // 此程序的问题，在windows下，没一行的结束都会有换行符（占两个size）
    // 所以最终的size是加上换行符的size（n行文本，可能size会多2n或2n-2（最后一行无换行））
    size = input.tellg();

    cout << "size = " << size << endl;

    memblocks = new char[size + 1];

    //seekp(相对位置,参照位置);
    //ios::beg = 0相对于文件头
    input.seekg(0, ios::beg);
    // read配合使用的函数是gcount()，用来获得实际读取的字节数。
    input.read(memblocks, size);

    memblocks[size] = '\0';

    cout << "size is: " <<  size << endl;
    cout << "memblocks is: " <<  string(memblocks) << endl;

    delete [] memblocks;
}


int main()
{
    ifstream file;
    string inputFilename = "data.txt";
    if (!inputFilename.empty())
    {
        file.open(inputFilename.c_str(), ios::in | ios::out | ios::binary);
        if (file.is_open())
        {
            cout << FileRead(file) << endl;
            file.close();
        }
        else
        {
            cout << "File open error" << endl;
        }
    }
    else
    {
        cout << "File empty!" << endl;
    }

    return 0;
}
