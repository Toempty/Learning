#include <iostream>
#include <array>
#include <vector>

using namespace std;

int main()
{
    const int constN(5); // 定义常数

    // 常规数组
    int data[constN] = {1, 2, 3, 4, 5};

    // vector动态数组
    int variableN = 5;
    vector<int> dataVector(variableN, 1);

    // array固定数组
    array<int, constN> dataArray = {6, 7, 8, 9, 10};

    // 数组访问
    cout << "data[3] = " << data[3] << endl;
    cout << "dataVector[3] = " << dataVector[3] << endl;
    cout << "dataArray[3] = " << dataArray[3] << endl;
    cout << "dataVector.at(3) = " << dataVector.at(3) << endl;
    cout << "dataArray.at(3) = " << dataArray.at(3) << endl;

    return 0;
}


