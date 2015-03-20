/**
 *@brief RGB图像转换为灰度图像,GRAY=0.299*R+0.587*G+0.114*B,Mat中按BGR存储
 *@param[in] ori_ima Mat型  CV_8UC3 型, RGB图
 *@param[out]
 *@return    new_ima Mat型  CV_8U
 *@pre       输入的Mat型数据必须是三通道CV_8U型的
 *@post      输出的Mat型数据是单通道CV_8U型的
 *@code
   Mat test_ima=imread("LenaRGB.bmp");
   Mat test_ima1(test_ima.rows, test_ima.cols, CV_8U, Scalar(0));
   test_ima1=rgb2gray(test_ima);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/
#include "rgb2gray.h"

Mat rgb2gray(Mat& ori_ima)
{
	Mat gray(ori_ima.rows, ori_ima.cols, CV_8U, Scalar(0));
	if (ori_ima.channels() != 3)
	{
		cout << "错误的输入，请输入RGB图像！" << endl;
		Sleep(2000);
		exit(-1);
	}
	else
	{
		for (int i=0; i<ori_ima.rows; i++)
		{
			uchar* data = gray.ptr<uchar>(i);
			for (int j=0; j<ori_ima.cols; j++)
			{
				data[j] = uchar(0.114*ori_ima.at<Vec3b>(i,j)[0]
								+0.587*ori_ima.at<Vec3b>(i,j)[1]
								+0.299*ori_ima.at<Vec3b>(i,j)[2]);
			}
		}
	}
	return gray;
}