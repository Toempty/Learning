#include < opencv2/highgui/highgui.hpp >
#include < iostream >
#include < Windows.h >

using namespace cv;
using namespace std;

int main()
{
    Mat im;
    double duration;
    im = imread(“D:\Document\pictures\Lena.bmp”,0);
    // 测试没有namedWindow时的waitKey执行时间
    duration = static_cast<double>(getTickCount());
    waitKey(10000);
    duration = static_cast<double>(getTickCount()) – duration;
    duration /= getTickFrequency();
    cout <<"第一个waitKey运行时间为：" << duration << 's' << endl;
    namedWindow("Lena");
    imshow("Lena",im);
    // 测试有namedWindow时的waitKey执行时间
    duration = static_cast<double>(getTickCount());
    waitKey(10000);
    duration = static_cast<double>(getTickCount()) – duration;
    duration /= getTickFrequency();
    cout <<"第二个waitKey运行时间为：" << duration << 's' << endl;
    Sleep(20000);
    return 0;
}