#include <iostream>
#include <highgui.h>
#include <imgproc\imgproc.hpp>
#include "rgb2gray.h"
#include "filterImg.h"

using namespace std;
using namespace cv;

int main()
{
	Mat ori_img = imread("D:\\Document\\vidpic\\pictures\\LenaRGB.bmp");
	Mat gray_img; // 如果读入的是RGB图像，需转换为灰度图像，方便处理
	Mat blur_img_ker3; // 用3*3的模糊核对图像进行低通滤波
	Mat blur_img_ker5; // 用5*5的模糊核对图像进行低通滤波
	Mat lap_img_ker3;  // 用3*3的拉普拉斯核对图像进行高通滤波
	Mat sharp_img_ker3;  // 用3*3的锐化核对图像进行锐化

	float operat_Lap[][3]= {0, -1.0/4, 0, -1.0/4, 1.0, -1.0/4, 0, -1.0/4, 0};
	float operat_Sharp[][3]= {0, -1.0/4, 0, -1.0/4, 2.0, -1.0/4, 0, -1.0/4, 0};

	Mat operatMat_blur_ker3=Mat(3, 3, CV_32F, Scalar(1.0/9)); // 3*3的平均模糊核
	Mat operatMat_blur_ker5=Mat(5, 5, CV_32F, Scalar(1.0/25)); // 5*5的平均模糊核
	Mat operatMat_lap_ker3=Mat(3, 3, CV_32F, operat_Lap); // 3*3的拉普拉斯核
	Mat operatMat_sharp_ker3=Mat(3, 3, CV_32F, operat_Sharp); // 3*3的拉普拉斯核

	gray_img = rgb2gray(ori_img);

	blur_img_ker3=filterImg(gray_img, operatMat_blur_ker3);
	blur_img_ker5=filterImg(gray_img, operatMat_blur_ker5);
	lap_img_ker3=filterImg(gray_img, operatMat_lap_ker3);
	sharp_img_ker3=filterImg(gray_img, operatMat_sharp_ker3);
	
	namedWindow("原始图像");
	imshow("原始图像",ori_img);
	namedWindow("灰度图像");
	imshow("灰度图像",gray_img);
	namedWindow("blur_img_ker3");
	imshow("blur_img_ker3",blur_img_ker3);
	namedWindow("blur_img_ker5");
	imshow("blur_img_ker5",blur_img_ker5);
	namedWindow("Laplacian Image");
	imshow("Laplacian Image",lap_img_ker3);
	namedWindow("Sharpen Image");
	imshow("Sharpen Image",sharp_img_ker3);
	waitKey(0);
}