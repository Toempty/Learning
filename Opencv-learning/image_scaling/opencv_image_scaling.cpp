#include <iostream>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void decide_boud(double in,double low,double high)//判断参数输入是否准确
{
	if ((in<=low)||(in>high))
	{
		cout<<"输入的参数超出范围！"<<endl;
		_sleep(2000);
		exit(0) ;
	}
}
int main()
{
	Mat ori_ima=imread("D:\\Document\\vidpic\\pictures\\LenaRGB.bmp");//原始图像
	double scale_R=1;//行的缩放比
	double scale_C=1;//列的缩放比
	int new_R;//新图像的行
	int new_C;//新图像的列

	//输入缩放比例参数
	cout<<"请输入行的缩放比（0,2）："<<endl;
	cin>>scale_R;
	decide_boud(scale_R,0,2);
	cout<<"请输入列的缩放比（0,2）："<<endl;
	cin>>scale_C;
	decide_boud(scale_C,0,2);

	//计算新图像的行和列
	new_R=int(scale_R*ori_ima.rows);
	new_C=int(scale_C*ori_ima.cols);

	//初始化新的图像
	Mat new_ima(new_R,new_C,CV_8UC3,Scalar(0,0,0));

	double pix11=0,pix12=0,pix21=0,pix22=0;//双线性变换周围像素

	for(int i=0;i<new_R;i++)
		for(int j=0;j<new_C;j++)
		{
			double old_i=i/scale_R;//old_i对应原始图像的坐标
			double old_j=j/scale_C;
			if((old_i/double(int(old_i))==1.0)&&(old_j/double(int(old_j))==1.0))//整数坐标直接幅值
			{
				new_ima.at<Vec3b>(i,j)[0]=ori_ima.at<Vec3b>(old_i,old_j)[0];
				new_ima.at<Vec3b>(i,j)[1]=ori_ima.at<Vec3b>(old_i,old_j)[1];
				new_ima.at<Vec3b>(i,j)[2]=ori_ima.at<Vec3b>(old_i,old_j)[2];
			}
			else//非整数坐标，用双线性差值算法
			{
				int old_ii=double(int(old_i));
				int old_jj=double(int(old_j));
				for (uchar k=0;k<3;k++)
				{
					//取（old_i,old_j）周围的四个像素
					if((old_ii==ori_ima.rows-1)&&(old_jj!=ori_ima.cols-1))//下边界处理
					{
						pix11=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix12=double(ori_ima.at<Vec3b>(old_ii,old_jj+1)[k]);
						pix21=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix22=double(ori_ima.at<Vec3b>(old_ii,old_jj+1)[k]);
					}
					else if((old_jj==ori_ima.cols-1)&&(old_ii!=ori_ima.rows-1))//右边界处理
					{
						pix11=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix12=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix21=double(ori_ima.at<Vec3b>(old_ii+1,old_jj)[k]);
						pix22=double(ori_ima.at<Vec3b>(old_ii+1,old_jj)[k]);
					}
					else if((old_jj==ori_ima.cols-1)&&(old_ii==ori_ima.rows-1))//右下角处理
					{
						pix11=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix12=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix21=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix22=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
					}

					else
					{
						pix11=double(ori_ima.at<Vec3b>(old_ii,old_jj)[k]);
						pix12=double(ori_ima.at<Vec3b>(old_ii,old_jj+1)[k]);
						pix21=double(ori_ima.at<Vec3b>(old_ii+1,old_jj)[k]);
						pix22=double(ori_ima.at<Vec3b>(old_ii+1,old_jj+1)[k]);
					}
					new_ima.at<Vec3b>(i,j)[k]=uchar((old_jj+1-old_j)*((old_i-old_ii)*pix21+(old_ii+1-old_i)*pix11)+(old_j-old_jj)*((old_i-old_ii)*pix22+(old_ii+1-old_i)*pix12));

				}
			}
		}
		namedWindow("原始图像");
		imshow("原始图像",ori_ima);
		namedWindow("缩放后的图像");
		imshow("缩放后的图像",new_ima);
		waitKey(0);
}