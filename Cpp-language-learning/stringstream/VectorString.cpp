#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    vector<string> stringVec;

    // 以下代码适合多文件读入的情况
    stringstream str;
    for (int i = 0; i < 12; ++i)
    {
        str << "data_" << setw(2) << setfill('0') << i << ".txt";
        stringVec.push_back(str.str());
        str.str("");
    }

    for (int i = 0; i < stringVec.size(); ++i)
    {
        cout << stringVec[i] << endl;
    }

    cout << "***********" << endl;
    stringVec.pop_back(); // 取出容器中最后一个

    for (int i = 0; i < stringVec.size(); ++i)
    {
        cout << stringVec[i] << endl;
    }
    return 0;
}
