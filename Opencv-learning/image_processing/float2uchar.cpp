/**
 *@brief float型图像转换为uchar型图像,将处理过的数据重新转换为uchar型
 *@param[in] float_ima Mat型  CV_32F 型 
 *@param[out]
 *@return    uchar_ima Mat型  CV_8U
 *@pre       输入的Mat型数据必须是单通道CV_32F型的
 *@post      输出的Mat型数据是单通道CV_8U型的
 *@code
   Mat test_ima(100, 100, CV_32F, Scalar(100.0));
   Mat test_ima1(test_ima.rows, test_ima.cols, CV_8U, Scalar(0));
   test_ima1=float2uchar(test_ima);
 *@endcode

 *@since 2013.10.16
 *@author lichao
*/

#include "float2uchar.h"

Mat float2uchar(Mat& float_ima)
{	
	if (float_ima.depth() != 5)
	{
		cout << "错误的输入，请输入float型图像！" << endl;
		Sleep(2000);
		exit(-1);
	}
	normalize(float_ima, float_ima, 1.0, 0.0, NORM_MINMAX); // float数据归一化
	float_ima=255*float_ima; // 所有数据乘以255

	Mat uchar_ima(float_ima.rows, float_ima.cols, CV_8U, Scalar(0));

	//for (int i=0; i<uchar_ima.rows; i++)
	//{
	//	uchar* data = uchar_ima.ptr<uchar>(i);
	//	float* data1  = float_ima.ptr<float>(i);
	//	for (int j=0; j<float_ima.cols; j++)
	//	{
	//		data[j] = uchar(data1[j]);
	//	}
	//}
	float_ima.convertTo(uchar_ima, CV_8U); // 此行与上面的代码实现相同的功能
	return uchar_ima;
}