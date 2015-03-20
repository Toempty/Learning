#include < opencv2/highgui/highgui.hpp >
#include < iostream >
#include < Windows.h >
using namespace cv;
using namespace std;
int main()
{
    Mat im;
    double duration;
    duration = static_cast<</span>double>(getTickCount());
    // 待测代码
    im = imread("D:\Document\pictures\Lena.bmp",0);
    namedWindow("Lena"); imshow("Lena",im); waitKey(1000);
    // 待测代码
    duration = static_cast<</span>double>(getTickCount()) - duration;
    duration /= getTickFrequency();
    cout <<"运行时间为：" << duration << 's' << endl;
    Sleep(20000);
    return 0;
}