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


// typedef struct _MEMORYSTATUSEX
// {
//     DWORD     dwLength; //本结构长度
//     DWORD     dwMemoryLoad; //已用内存百分比
//     DWORDLONG ullTotalPhys; //物理内存总量
//     DWORDLONG ullAvailPhys; //可用物理内存
//     DWORDLONG ullTotalPageFile; //交换文件总的大小
//     DWORDLONG ullAvailPageFile; //交换文件中空余部分大小
//     DWORDLONG ullTotalVirtual; //用户可用地址空间
//     DWORDLONG ullAvailVirtual; //当前空闲的地址空间
//     DWORDLONG ullAvailExtendedVirtual; //保留值，设为0
// } MEMORYSTATUSEX, *LPMEMORYSTATUSEX;

// VS2012 Win7 64位 x64编译
// 内存初始状态：
// 内存繁忙程度 = 43
// 总物理内存 = 8066.03M
// 可用物理内存 = 4541.91M
// 总页文件 = 8064.21M
// 可用页文件 = 4174.58M
// 总进程空间 = 8.38861e+006M
// 可用进程空间 = 8.3886e+006M

// VS2012 Win7 64位 Win32编译
// 内存初始状态：
// 内存繁忙程度 = 43
// 总物理内存 = 8066.03M
// 可用物理内存 = 4518.97M
// 总页文件 = 8064.21M
// 可用页文件 = 4148.94M
// 总进程空间 = 2047.88M
// 可用进程空间 = 2034.26M

using namespace std;

int main()
{
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof (memStatus);
    GlobalMemoryStatusEx (&memStatus);

    cout << "内存初始状态：" << endl;
    cout << "内存繁忙程度 = " << memStatus.dwMemoryLoad << endl;
    cout << "总物理内存 = " << double(memStatus.ullTotalPhys) /(1024*1024) << "M" << endl;
    cout << "可用物理内存 = " << double(memStatus.ullAvailPhys) /(1024*1024) << "M" << endl;
    cout << "总页文件 = " << double(memStatus.ullTotalPageFile) /(1024*1024) << "M" << endl;
    cout << "可用页文件 = " << double(memStatus.ullAvailPageFile) /(1024*1024) << "M" << endl;
    cout << "总进程空间 = " << double(memStatus.ullTotalVirtual) /(1024*1024) << "M" << endl;
    cout << "可用进程空间 = " << double(memStatus.ullAvailVirtual) /(1024*1024) << "M" << endl << endl;

    system("pause");

    return 0;
}
