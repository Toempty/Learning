#include "stdafx.h"
#include <iostream>
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

Mat ShowmnImage(int m,int n,Mat Image,Mat DispImage) //在DispImage的（m,n）位置开始显示Image
{
	Mat imageROI;
	if((m<0)||(m>DispImage.cols-Image.cols)||(n<0)||(n>DispImage.rows-Image.rows))
	{
		cout<<"参数输入错误！"<<endl;
		m=0;
		n=0;
	}
	imageROI=DispImage(Rect(m,n,Image.cols,Image.rows));
	Image.copyTo(imageROI,Image);
	return DispImage;
}

Mat Show8Image(int x,int y,Mat Image)//显示要求的画中画视频
{
	x=(x<1000)? 1000:x;//x,y 最小为1000
	y=(y<1000)? 1000:y;

	Mat DispImage(x,y,CV_8UC3);
	int m=20,n=20;//默认图像间隔为20
	int size=320;//默认子图像最大为320 ，可以调用resize
	
	for(int j=0;j<3;j++)
	{
		for(int i=0;i<3;i++)
		{			
			if((j*3+i)!=4)
			{
				DispImage=ShowmnImage(i*(m+size), j*(n+size),Image,DispImage);

			}
		}
	}	
	return DispImage;
}
int main()
{
	Mat frame,Disp8Image;
	int m=1000,n=1000;//m,n为整体视频的大小
	namedWindow("源视频");
	namedWindow("画中画");

	VideoCapture Capture("D:\\Document\\vidpic\\video\\video.short.mjpg.avi");
	if(!Capture.isOpened()){ return 1;}
	bool stop(false);


	while(!stop)
	{
		if(!Capture.read(frame)){ break;}
		imshow("源视频",frame);

		Disp8Image=Show8Image(m,n,frame);
		imshow("画中画",Disp8Image);
		if(waitKey(33)>=0){ stop=true;}
	}
	Capture.release();
}

