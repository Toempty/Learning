/**
 *@brief 对灰度图像进行滤波处理，operat中是滤波算子
 *@param[in] ori_img Mat型  CV_8U 型; operat Mat型 CV_32F 型;
 *@param[out]
 *@return    new_img Mat型  CV_8U
 *@pre       输入的Mat型数据必须是单通道CV_8U型的
 *@post      输出的Mat型数据是单通道CV_8U型的
 *@code
   Mat test_img=imread("Lena.bmp");
   Mat test_img1(test_img.rows, test_img.cols, CV_8U, Scalar(0));
   test_img1=Opert_img(test_img, operat);
 *@endcode

 *@since 2013.10.17
 *@author lichao
*/
#include "filterImg.h"
Mat filterImg(Mat& ori_img, Mat& operat)
{
	if(ori_img.channels()!=1)
	{
		cout<<"请输入灰度图！"<<endl;
		Sleep(2000);
		exit(-1);
	}
	Mat new_img(ori_img.rows, ori_img.cols, CV_8U, Scalar(0));
	Mat float_img(ori_img.rows, ori_img.cols, CV_32F, Scalar(0.0)); // 中间图像变量
	Mat float_img_mid(ori_img.rows, ori_img.cols, CV_32F, Scalar(0.0));  //
	Mat imgRoi;

	float_img_mid=uchar2float(ori_img);
	int k=operat.rows/2;
	int windrow=operat.rows;
	int windcol=operat.cols;
	Mat midMat(operat.rows, operat.cols, CV_32F, Scalar(0.0));
	for(int i=k; i<ori_img.rows-k; i++)
	{
		float* data=float_img.ptr<float>(i);
		for(int j=k; j<ori_img.cols-k; j++)
		{
			imgRoi=float_img_mid(Rect(j-k,i-k,windcol,windrow)); // 提取感兴趣区域
			midMat=imgRoi.mul(operat);
			data[j]=sum(midMat).val[0]; // 点乘
		}		
	}
	new_img=float2uchar(float_img);
	return new_img;
}