#include <iostream>

using namespace std;

struct DEMO
{
    int m;

    DEMO(int k) //构造函数
    {
        this->m = k;
        cout << "after init, m= " << m << endl;
    }

    void show() //一般函数
    {
        cout << "function of struct." << endl;
    }
};

int main()
{
    struct DEMO demo(33);
    demo.show();
    cout << "m = " << demo.m << endl;

    DEMO *pdemo = new DEMO(10);
    cout << pdemo->m << endl;
    pdemo->show();

    return 0;
}
