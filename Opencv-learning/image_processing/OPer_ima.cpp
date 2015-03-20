/**
 *@brief 输入算子,对灰度图像进行处理
 *@param[in] ori_ima Mat型  CV_8U 型; operat double型数组，长度9
 *@param[out]
 *@return    new_ima Mat型  CV_8U
 *@pre       输入的Mat型数据必须是单通道CV_8U型的
 *@post      输出的Mat型数据是单通道CV_8U型的
 *@code
   Mat test_ima=imread("Lena.bmp");
   double operat[9]={1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9};
   Mat test_ima1(test_ima.rows, test_ima.cols, CV_8U, Scalar(0));
   test_ima1=Oper_ima(test_ima, operat);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/
#include "OPer_ima.h"

Mat OPer_ima(Mat& ori_ima, double* operat)
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
			data[j] = data0[j-1] * operat[0] + data0[j] * operat[1] + data0[j+1] * operat[2]
					+ data1[j-1] * operat[3] + data1[j] * operat[4] + data1[j+1] * operat[5]
					+ data2[j-1] * operat[6] + data2[j] * operat[7] + data2[j+1] * operat[8];
		}
	}
	new_ima=float2uchar(float_ima); // float型图像转换为uchar型图像
	return new_ima;
}