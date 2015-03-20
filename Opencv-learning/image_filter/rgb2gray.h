#ifndef RGB2GRAY_H
#define RGB2GRAY_H

#include <iostream>
#include <highgui.h>
#include <Windows.h>
#include <imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

Mat rgb2gray(Mat& ori_img); // RGBͼת�Ҷ�ͼ
#endif