    #include <iostream>
    #include <windows.h>
    //#include <winbase.h>

    // WINDOWS.H是一个最重要的头文件，它包含了其他Windows头文件。
    // 这些头文件中最重要的和最基本的是：
    // WINDEF.H 基本数据类型定义。
    // WINNT.H 支持Unicode的类型定义。
    // WINBASE.H Kernel(内核)函数。
    // WINUSER.H 用户界面函数。
    // WINGDI.H 图形设备接口函数。


    // 可以看出，页面大小是4K，区域分配粒度是64K，进程用户区是0x0001 0000~0x7FFE FFFF。
    using namespace std;

    int main()
    {
        SYSTEM_INFO sysInfo; // winbase.h
        GetSystemInfo(&sysInfo); // winbase.h

        cout << "机器属性：" << endl;
        cout << "页大小 = " << sysInfo.dwPageSize << endl;
        cout << "分配粒度 = " << sysInfo.dwAllocationGranularity << endl;
        cout << "用户区最小寻址单元 = " << sysInfo.lpMinimumApplicationAddress << endl;
        cout << "用户区最大寻址单元 = " << sysInfo.lpMaximumApplicationAddress << endl;

        system("pause");

        return 0;
    }
