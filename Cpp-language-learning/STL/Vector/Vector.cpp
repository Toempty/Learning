#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //-- 1. 声明
    vector<char> cVectorData(2);
    cVectorData[0] = 'a'; // 容器的赋值
    cVectorData[1] = 'b';

    cout << "cVectorData : "
         << cVectorData[0]
         << " "
         << cVectorData[1]
         << endl;

    vector<int> iVectorData(3, 1); // 第一个：容器大小；第二个：初始值
    cout << "iVectorData : "
         << iVectorData[0]
         << " "
         << iVectorData[1]
         << endl;

    //-- 2. 容器大小
    // size()-返回容器中元素数目
    cout << "size of iVectorData : "
         << iVectorData.size()
         << endl;

    //-- 3. 容器头位置
    // begin()-返回指向容器第一个元素的迭代器
    cout << "cVectorData : "
         << *cVectorData.begin()
         << " "
         << *(cVectorData.begin() + 1)
         << endl;

    //-- 4. 容器结束位置
    // end()-返回表示超过容器尾的迭代器
    // 也就是说，end()指向最后一个元素的下一个位置
    cout << "cVectorData : "
         << *(cVectorData.end() - 1)
         << " "
         << *(cVectorData.end() - 2)
         << endl;

    //-- 5. 添加元素
    // 使用push_back()将元素添加到容器末尾
    vector<double> dVectorData;

    cout << "size of dVectorData : "
         << dVectorData.size()
         << endl;

    dVectorData.push_back(1.2);
    dVectorData.push_back(2.3);

    cout << "dVectorData : "
         << dVectorData[0]
         << " "
         << dVectorData[1]
         << endl;

    cout << "size of dVectorData : "
         << dVectorData.size()
         << endl;

    //-- 6. 删除元素
    // 使用erase()方法删除容器中给定区间的元素
    vector<float> fVectorData(5, 1.1);
    cout << "size of fVectorData : "
         << fVectorData.size()
         << endl;

    // 删除前两个元素
    fVectorData.erase(fVectorData.begin(), fVectorData.begin() + 2);

    cout << "size of fVectorData : "
         << fVectorData.size()
         << endl;

    //-- 7. 插入元素
    // 使用insert()方法插入元素，与erase()类似
    // 从第一个参数的位置开始插入
    vector<float> fVectorDataInsert(5, 2.2);

    fVectorData.insert(fVectorData.begin() + 2, fVectorDataInsert.begin(), fVectorDataInsert.begin() + 2);

    cout << "size of fVectorData : "
         << fVectorData.size()
         << endl;

    cout << "fVectorData : "
         << fVectorData[1]
         << " "
         << fVectorData[2]
         << " "
         << fVectorData[3]
         << " "
         << fVectorData[4]
         << endl;

    //-- 8. 交换元素
    // 使用swap()方法交换元素

    return 0;
}
