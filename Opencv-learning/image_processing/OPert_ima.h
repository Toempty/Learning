#ifndef OPERT_IMA_H
#define OPERT_IMA_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>
#include "uchar2float.h"
#include "float2uchar.h"

using namespace std;
using namespace cv;

Mat OPert_ima(Mat& ori_ima, int type); // 输入类型计算

#endif