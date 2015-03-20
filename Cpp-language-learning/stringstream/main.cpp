#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
    int iData = 123;
    stringstream ss;
    ss << "iData = " << iData << endl; // 将int类型读入ss,变为string类型
    cout << ss.str() << endl;

    ss.str(""); //在进行多次转换前，必须清除stream

    int iInputData = 0;
    ss << "1234"; // 将字符串“1234”输入流ss
    ss >> iInputData; // 从流ss中提取字符串并转换为int值放入iInputData
    cout << "iInputData = " << iInputData << endl;

    // 以下代码适合多文件读入的情况
    stringstream str;
    for (int i = 1; i < 12; ++i)
    {
        str << "data_" << setw(2) << setfill('0') << i << ".txt";
        cout << str.str() << endl;
        str.str("");
    }
    return 0;
}
