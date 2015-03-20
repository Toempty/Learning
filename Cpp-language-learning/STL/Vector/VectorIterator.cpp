#include <iostream>
#include <vector>

using namespace std;

/**
 * 迭代器可以看成一个广义指针。
 * 每个容器类都定义了一个合适的迭代器，该迭代器是一个
 * 名为iterator的typedef，其作用域为整个类
 * 例如，要为vector的double类型声明一个迭代器
 * vector<double>::iterator itVector;
 */
int main()
{
    int iNum = 5;
    vector<int> iVectorData(iNum, 0);

    for (vector<int>::iterator it = iVectorData.begin(); it != iVectorData.end(); ++it)
    {
        cin >> *it;
    }

    for (vector<int>::iterator it = iVectorData.begin(); it != iVectorData.end(); ++it)
    {
        cout << *it << " ";
    }

    cout << endl;

    // 也可以使用auto来声明自动变量(要使用 -std=c++0x 选项)，如下：
    for (auto it = iVectorData.begin(); it != iVectorData.end(); ++it)
    {
        cout << *it << " ";
    }

    return 0;
}
