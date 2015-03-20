/**
 *@brief uchar型图像转换为float型图像,保证图像处理过程中的精度
 *@param[in] uchar_img Mat型  CV_8U 型 
 *@param[out]
 *@return    float_img Mat型  CV_32F
 *@pre       输入的Mat型数据必须是单通道CV_8U型的
 *@post      输出的Mat型数据是单通道CV_32F型的
 *@code
   Mat test_img(100, 100, CV_8U, Scalar(0));
   Mat test_img1(test_img.rows, test_img.cols, CV_32F, Scalar(0.0));
   test_img1=uchar2float(test_img);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/
// 此函数可以用Mat中的convertTo替换

#include "uchar2float.h"

Mat uchar2float(Mat& uchar_img)
{	
	if (uchar_img.depth() != 0)
	{
		cout << "错误的输入，请输入uchar型图像！" << endl;
		Sleep(2000);
		exit(-1);
	}
	Mat float_img(uchar_img.rows, uchar_img.cols, CV_32F, Scalar(0.0));

	// uchar_img.convertTo(float_img, CV_32F);
	for (int i=0; i<uchar_img.rows; i++)
	{
		uchar* data1 = uchar_img.ptr<uchar>(i); // 源图像行指针
		float* data  = float_img.ptr<float>(i); // 新图像行指针
		for (int j=0; j<uchar_img.cols; j++)
		{
			data[j] = float(data1[j]);
		}
	}

	return float_img;
}