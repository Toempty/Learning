/**
 *@brief float型图像转换为uchar型图像,将处理过的数据重新转换为uchar型
 *@param[in] float_img Mat型  CV_32F 型 
 *@param[out]
 *@return    uchar_img Mat型  CV_8U
 *@pre       输入的Mat型数据必须是单通道CV_32F型的
 *@post      输出的Mat型数据是单通道CV_8U型的
 *@code
   Mat test_img(100, 100, CV_32F, Scalar(100.0));
   Mat test_img1(test_img.rows, test_img.cols, CV_8U, Scalar(0));
   test_img1=float2uchar(test_img);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/
// 此函数可以用Mat中的convertTo替换

#include "float2uchar.h"

Mat float2uchar(Mat& float_img)
{	
	if (float_img.depth() != 5)
	{
		cout << "错误的输入，请输入float型图像！" << endl;
		Sleep(2000);
		exit(-1);
	}
	normalize(float_img, float_img, 1.0, 0.0, NORM_MINMAX); // float数据归一化
	float_img=255*float_img; // 所有数据乘以255

	Mat uchar_img(float_img.rows, float_img.cols, CV_8U, Scalar(0));

	// float_img.convertTo(uchar_img, CV_8U); 
	for (int i=0; i<uchar_img.rows; i++)
	{
		uchar* data = uchar_img.ptr<uchar>(i);
		float* data1  = float_img.ptr<float>(i);
		for (int j=0; j<float_img.cols; j++)
		{
			data[j] = uchar(data1[j]);
		}
	}

	return uchar_img;
}