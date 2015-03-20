#ifndef FLOAT2UCHAR_H
#define FLOAT2UCHAR_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>

using namespace std;
using namespace cv;

Mat float2uchar(Mat& float_img); // float型图像转换为uchar型图像

#endif