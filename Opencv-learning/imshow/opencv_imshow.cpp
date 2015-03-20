#include <iostream>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main()
{
	int a = 0;
	Mat ori_ima=imread("D:\\Document\\vidpic\\pictures\\LenaRGB.bmp");//原始图像

	//图像显示
	namedWindow("原始图像");
	imshow("原始图像",ori_ima);
	waitKey(0);

	return 0;
}