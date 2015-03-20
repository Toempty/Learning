#ifndef UCHAR2FLOAT_H
#define UCHAR2FLOAT_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>

using namespace std;
using namespace cv;

Mat uchar2float(Mat& uchar_ima); // uchar型图像转换为float型图像

#endif