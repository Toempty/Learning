#ifndef SALT_PEPPER_IMA_H
#define SALT_PEPPER_IMA_h

#include <iostream>
#include <highgui.h>
#include <Windows.h>

using namespace std;
using namespace cv;

Mat Salt_Pepper_ima(Mat& ori_ima, int n); // 图像添加椒盐噪声
#endif