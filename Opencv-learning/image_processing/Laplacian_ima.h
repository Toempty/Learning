#ifndef LAPLACIAN_IMA_H
#define LAPLACIAN_IMA_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>
#include "uchar2float.h"
#include "float2uchar.h"

using namespace std;
using namespace cv;

Mat Laplacian_ima(Mat& ori_ima); // 拉普拉斯梯度

#endif 