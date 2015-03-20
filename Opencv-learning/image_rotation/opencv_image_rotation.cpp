#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void decide_bound(double in,double low,double high)
{
	if((in<low)||(in>high))
	{
		cout<<"输入的角度超出范围！"<<endl;
		_sleep(2000);
		exit(0);
	}
}

int main()
{
	float angle=0;
	float angle_r=0;
	float max,min;
	int new_R=0,new_C=0; //新的行和列
	int Ri,Rj;

	//读入原始图像并显示
	Mat ori_ima;//原始图像	
	ori_ima=imread("D:\\Document\\vidpic\\pictures\\LenaRGB.bmp");

	//输入旋转角度
	cout<<"请输入旋转角度(-90,90）,按回车结束:"<<endl;
	cin>>angle;
	decide_bound(angle,-90,90);

	angle_r=angle/180*CV_PI;

	//变换矩阵
	float t[2][2]={cos(angle_r),-sin(angle_r),sin(angle_r),cos(angle_r)};
	Mat T=Mat(2,2,CV_32F,t);//变换矩阵

	//计算新图像的大小
	float rw_[4][2]={{1,1},{1,ori_ima.cols},{ori_ima.rows,1},{ori_ima.rows,ori_ima.cols}};
	Mat rw=Mat(4,2,CV_32F,rw_);//
	Mat RW(4,2,CV_32F);//
	RW=rw*T;
	Mat maxm,minm;
	reduce(RW,maxm,0,CV_REDUCE_MAX,-1);//每一列的最大值
	reduce(RW,minm,0,CV_REDUCE_MIN,-1);//每一行的最大值
	Mat new_RW=maxm-minm;
	new_R=ceil(new_RW.at<float>(0,0));//新的行数
	new_C=ceil(new_RW.at<float>(0,1));//新的列数

	
	Mat new_ima(new_R,new_C,CV_8UC3,Scalar(0,0,0));//旋转后的图像

	Mat RIJ=Mat(1,2,CV_32F,Scalar(0)),RIJ_=Mat(1,2,CV_32F,Scalar(0));
	int ri,rj;

	for(int i=0;i<new_R;i++)
	{
		for(int j=0;j<new_C;j++)
		{

			RIJ.at<float>(0,0)=i-1;
			RIJ.at<float>(0,1)=j-1;
			RIJ=(RIJ+minm)*T.inv();
			ri=ceil(RIJ.at<float>(0,0));//在原始图的行数
			rj=ceil(RIJ.at<float>(0,1));//在原始图的列数

			if((ri>=0)&&(rj>=0)&&(ri<ori_ima.rows)&&(rj<ori_ima.cols))
			{
				new_ima.at<Vec3b>(i,j)[0]=ori_ima.at<Vec3b>(ri,rj)[0];
				new_ima.at<Vec3b>(i,j)[1]=ori_ima.at<Vec3b>(ri,rj)[1];
				new_ima.at<Vec3b>(i,j)[2]=ori_ima.at<Vec3b>(ri,rj)[2];
			}
		}
	}
	
	namedWindow("原始图像");
	imshow("原始图像",ori_ima);
	namedWindow("旋转后的图像");
	imshow("旋转后的图像",new_ima);
	
	waitKey(0);
}