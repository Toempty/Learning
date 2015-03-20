/**
 *@brief uchar型图像转换为float型图像,保证图像处理过程中的精度
 *@param[in] uchar_ima Mat型  CV_8U 型 
 *@param[out]
 *@return    float_ima Mat型  CV_32F
 *@pre       输入的Mat型数据必须是单通道CV_8U型的
 *@post      输出的Mat型数据是单通道CV_32F型的
 *@code
   Mat test_ima(100, 100, CV_8U, Scalar(0));
   Mat test_ima1(test_ima.rows, test_ima.cols, CV_32F, Scalar(0.0));
   test_ima1=uchar2float(test_ima);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/

#include "uchar2float.h"

Mat uchar2float(Mat& uchar_ima)
{	
	if (uchar_ima.depth() != 0)
	{
		cout << "错误的输入，请输入uchar型图像！" << endl;
		Sleep(2000);
		exit(-1);
	}
	Mat float_ima(uchar_ima.rows, uchar_ima.cols, CV_32F, Scalar(0.0));

	//for (int i=0; i<uchar_ima.rows; i++)
	//{
	//	uchar* data1 = uchar_ima.ptr<uchar>(i); // 源图像行指针
	//	float* data  = float_ima.ptr<float>(i); // 新图像行指针
	//	for (int j=0; j<uchar_ima.cols; j++)
	//	{
	//		data[j] = float(data1[j]);
	//	}
	//}

	uchar_ima.convertTo(float_ima, CV_32F);

	return float_ima;
}