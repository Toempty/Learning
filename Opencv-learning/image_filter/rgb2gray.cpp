/**
 *@brief RGB图像转换为灰度图像,GRAY=0.299*R+0.587*G+0.114*B,Mat中按BGR存储
 *@param[in] ori_img Mat型  CV_8UC3 型, RGB图
 *@param[out]
 *@return    new_img Mat型  CV_8U
 *@pre       输入的Mat型数据必须是三通道CV_8U型的
 *@post      输出的Mat型数据是单通道CV_8U型的
 *@code
   Mat test_img=imread("LenaRGB.bmp");
   Mat test_img1(test_img.rows, test_img.cols, CV_8U, Scalar(0));
   test_img1=rgb2gray(test_img);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/

// 此函数可以用imgproc库中的cvtColor函数替换
#include "rgb2gray.h"

Mat rgb2gray(Mat& ori_img)
{
	Mat gray_img(ori_img.rows, ori_img.cols, CV_8U, Scalar(0));
	if (ori_img.channels() != 3)
	{
		cout << "错误的输入，请输入RGB图像！" << endl;
		Sleep(2000);
		exit(-1);
	}
	else
	{
		// cvtColor(ori_img, gray_img, CV_RGB2GRAY);
		for (int i=0; i<ori_img.rows; i++)
		{
			uchar* data = gray_img.ptr<uchar>(i);
			for (int j=0; j<ori_img.cols; j++)
			{
				data[j] = uchar(0.114*ori_img.at<Vec3b>(i,j)[0]
								+0.587*ori_img.at<Vec3b>(i,j)[1]
								+0.299*ori_img.at<Vec3b>(i,j)[2]);
			}
		}
	}
	
	return gray_img;
}