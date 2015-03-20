#ifndef	_FILTERIMG_H
#define _FILTERIMG_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>
#include "uchar2float.h"
#include "float2uchar.h"

using namespace std;
using namespace cv;

Mat filterImg(Mat& ori_img, Mat& operat);
#endif