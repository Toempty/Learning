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


using namespace std;

const int N(50000); // 定义常数
// static int g_idata[N] = {0};

int main()
{
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof (memStatus);
    GlobalMemoryStatusEx (&memStatus);

    char *dynamic=new char[100*1024*1024];

    MEMORYSTATUSEX memStatusData;
    memStatusData.dwLength = sizeof (memStatusData);
    GlobalMemoryStatusEx (&memStatusData);

    cout << "内存消耗情况：" << endl;

    cout << "消耗物理内存 = " << double(memStatus.ullAvailPhys - memStatusData.ullAvailPhys) /(1024*1024) << "M" << endl;
    cout << "消耗页文件 = " << double(memStatus.ullAvailPageFile - memStatusData.ullAvailPageFile) /(1024*1024) << "M" << endl;
    cout << "消耗进程空间 = " << double(memStatus.ullAvailVirtual - memStatusData.ullAvailVirtual) /(1024*1024) << "M" << endl << endl;

    system("pause");

    return 0;
}
