#include <iostream>
#include <highgui.h>
#include <imgproc\imgproc.hpp>
#include "rgb2gray.h"
#include "OPert_ima.h"
#include "Salt_Pepper_ima.h"
#include "Laplacian_ima.h"
#include "filterImg.h"

using namespace std;
using namespace cv;

int main()
{
	Mat ori_ima = imread("D:\\Document\\vidpic\\pictures\\LenaRGB.bmp");
	Mat gray_ima;
	Mat Lap_ima;
	Mat Blu_ima;
	Mat test_ima;
	Mat test_ima1;

	// double operat[9]={1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9};
	float operat[][3]= {0, -1.0/4, 0, -1.0/4, 1.0, -1.0/4, 0, -1.0/4, 0};
	// float operatm[][3]={{1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}};
	 //float operatm[][5] ={{1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25},
		//				  {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25}, 
		//				  {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25}, 
		//				  {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25}, 
		//				  {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25}};
	 Mat operatMat=Mat(3, 3, CV_32F, operat);
	gray_ima = rgb2gray(ori_ima);
	Lap_ima=Laplacian_ima(gray_ima);

	 //Lap_ima = OPert_ima(gray_ima, 5); // 
	Blu_ima =  OPert_ima(gray_ima, 0);

	//test_ima=Salt_Pepper_ima(gray_ima, 10000);
	//medianBlur(test_ima, test_ima1, 3);

	test_ima=filterImg(gray_ima, operatMat);

	test_ima1=test_ima-Lap_ima;
	
	namedWindow("Ô­Ê¼Í¼Ïñ");
	imshow("Ô­Ê¼Í¼Ïñ",ori_ima);
	namedWindow("»Ò¶ÈÍ¼Ïñ");
	imshow("»Ò¶ÈÍ¼Ïñ",gray_ima);
	namedWindow("LapÍ¼Ïñ");
	imshow("LapÍ¼Ïñ",Lap_ima);
	namedWindow("BlurÍ¼Ïñ");
	imshow("BlurÍ¼Ïñ",Blu_ima);
	namedWindow("testÍ¼Ïñ");
	imshow("testÍ¼Ïñ",test_ima);
	namedWindow("test1Í¼Ïñ");
	imshow("test1Í¼Ïñ",test_ima1);
	
	waitKey(0);
}