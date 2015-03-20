#include<iostream>

using namespace std;

int g_i = 3; // 全局变量
int g_iu; // 全局变量
static int s_i = 4; // 静态常量
static int s_iu; // 静态常量
const int c_i = 5; // 全局常量
char *g_p = "abc"; // 全局char指针，指向常量字符串
char *g_pu; // 全局char指针
char *g_p2 = "abcd"; // 全局char指针，指向常量字符串

void fun() // 函数
{}

static void s_fun() // 静态函数
{}

int main()
{
    const int c = 6; // 局部常量
    char *str = "abc"; // 指向字符串常量的字符指针
    int ul_i; // 未初始化的局部变量
    const int cc = 5;
    int l_i = 3; // 局部变量
    int *p_i = new int; // int指针指向new开辟的int空间
    int *p_i2 = new int; // int指针指向new开辟的int空间
    int *pp_i = (int *) malloc(sizeof(int)); // int指针指向malloc开辟的int空间
    int *p_i3 = new int; // int指针指向new开辟的int空间
    int arr[200000]; // 局部int型数组

    printf("\n%08x : static int i s_iu\n", &s_iu);
    printf("%08x : global char pointer g_pu\n", &g_pu);
    printf("%08x : global int i g_iu g_iu\n", &g_iu);

    printf("\n%08x : global char pointer g_p2\n", &g_p2);
    printf("%08x : global char pointer  g_p\n", &g_p);
    printf("%08x : static int i s_i\n", &s_i);
    printf("%08x : global int i g_i\n", &g_i);

    printf("\n%08x : global char pointer point content g_p2\n", g_p2);
    printf("%08x : global char pointer point content g_p\n", g_p);
    printf("%08x : local char pointer point content str\n", str);
    printf("%08x : global const int\n", &c_i);

    printf("\n%08x : static function addresss\n", s_fun);
    printf("%08x : function address\n", fun);

    printf(".............................................................");

    printf("\n%08x : local int pointer point address(new) p_i3\n", p_i3);
    printf("%08x : local int pointer point address(malloc) pp_i\n", pp_i);
    printf("%08x : local int pointer point address(new) p_i2\n", p_i2);
    printf("%08x : local int pointer point address(new) p_i\n", p_i);

    printf(".............................................................");

    printf("\n%08x : local const int c\n", &c);
    printf("%08x : local char pointer str\n", &str);
    printf("%08x : local int l_i\n", &l_i);
    printf("%08x : local int pointer p_i\n", &p_i);
    printf("%08x : local int pointer pp_i\n", &pp_i);
    printf("%08x : local int pointer p_i2\n", &p_i2);
    printf("%08x : local int pointer p_i3\n", &p_i3);
    printf("%08x : array end address\n", &arr[199999]);
    printf("%08x : array start address\n", &arr[0]);

    printf(".............................................................");

    printf("\n%08x : global char pointer point content g_pu\n", g_pu);

    system("pause");
    return 0;
}
