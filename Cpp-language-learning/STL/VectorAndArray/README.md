### 数组的代替品

#### 模板类 vector

模板类vector类似与string， 也是一种动态数组。可在运行阶段设置vector对象的长度，可在末尾或中间附加数据。

vector使用new和delete来管理内存，所以vector创建的数组位于（自由存储区或者称为堆区）。

使用vector，需要包含头文件vector，另外，vector也包含在命名空间std中。

一般而言，下面的声明创建一个名为vt的vector对象，它可存储nElem个数据类型为typeName的元素，其中参数nElem可以是整型常量或者整型变量。另外，并把数组的初始值设为init，很多设为0。

    vector<typeName> vt(nElem, init);

更一般的用法：

    #include <iostream>
    #include <vector>

    using namespace std;

    int main()
    {
        vector<int> vi;

        int n;
        cin >> n;
        vector<double> vd(n);

        return 0;
    }


#### 模板类 array

vector类的功能比数组强大，但是效率较低。如果需要的是固定长度的数组，那么使用数组是更好的选择，但是代价是不方便、不安全。考虑到此，C++11 新增类array模板类，用于分配固定长度的数组。array分配的数组位于堆区，效率与数组相同，但更安全、方便。

使用array，需要包含头文件array，另外，array也包含在命名空间std中。

下面的声明创建类一个名为arr的array对象，它可存储nElem个数据类型为typeName的元素，其中参数nElem必须是整型常量。

    array<typeName, nElem> arr;

#### 比较

vector用于定义动态数组，分配的数组位于堆区。

array用于定义固定数组，分配的数组位于栈区。因此array的效率高于vector。
#### vector 和 array 优势

可以使用成员函数at()来避免数组索引时候的越界问题。
