/**
 *@brief 用模糊算子({{1/8, 1/9, 1/9}, {1/9, 1/9, 1/9}, {1/9, 1/9, 1/9}})
		 对灰度图像进行处理, 平滑――低通滤波
 *@param[in] ori_ima Mat型  CV_8U 型
 *@param[out]
 *@return    new_ima Mat型  CV_8U
 *@pre       输入的Mat型数据必须是单通道CV_8U型的
 *@post      输出的Mat型数据是单通道CV_8U型的
 *@code
   Mat test_ima=imread("Lena.bmp");
   Mat test_ima1(test_ima.rows, test_ima.cols, CV_8U, Scalar(0));
   test_ima1=Blur_ima(test_ima);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/
#include "Blur_ima.h"

Mat Blur_ima(Mat& ori_ima)
{
	Mat new_ima(ori_ima.rows, ori_ima.cols, CV_8U, Scalar(0));
	Mat float_ima(ori_ima.rows, ori_ima.cols, CV_32F, Scalar(0)); // 中间float图像，保证精度

	float_ima=uchar2float(ori_ima); // uchar型图像转换为float型图像
	for (int i=1; i<ori_ima.rows-1; i++)
	{
		float* data  = float_ima.ptr<float>(i);
		uchar* data0 = ori_ima.ptr<uchar>(i-1);
		uchar* data1 = ori_ima.ptr<uchar>(i);
		uchar* data2 = ori_ima.ptr<uchar>(i+1);
		for (int j=1; j<ori_ima.cols; j++)
		{
			data[j] = (data0[j-1] + data0[j] + data0[j+1] + data1[j-1] + 
				       data1[j] + data1[j+1] + data2[j-1] + data2[j] + data2[j+1])/9;
		}
	}
	new_ima=float2uchar(float_ima); // float型图像转换为uchar型图像
	return new_ima;
}