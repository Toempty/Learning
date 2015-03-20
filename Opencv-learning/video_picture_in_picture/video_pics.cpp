#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
using namespace std;

IplImage* cvShow8Images(char* Images, int nArgs, ...)
{	
	IplImage *img;
	IplImage *DispImage;

	int size=200;
	int x, y;
	int m = 40,n = 40;//视频窗口之间的间隔
	int w=3,h=3;
	float scale;
	int max;

	DispImage = cvCreateImage( cvSize(m*(w-1)+size*w, n*h+size*h), 8, 3 );
	va_list args;
	va_start(args, nArgs);//得到第一个可变参数地址	
	//nArgs 子视频个数
	for(int j=0;j<3;j++)
	{
		for(int i=0;i<3;i++)
		{			
			if((j*3+i)!=4)
			{
				img = va_arg(args, IplImage*);
				if(img == 0) 
				{
					cout<<"Not enough  arguments！"<<endl;
					cvReleaseImage(&DispImage);
					return 0;
				}
				x = img->width;
				y = img->height;

				max = (x > y)? x: y;
				scale = (float) ( (float) max / size );
				cvSetImageROI(DispImage, cvRect(i*(m+size), j*(n+size)+n, (int)( x/scale ), (int)( y/scale )));
				cvResize(img, DispImage);
				cvResetImageROI(DispImage);
			}
		}
	}
	va_end(args);//置空args
	return DispImage;
}

void test_frame_proce( IplImage* img ) 
{
	for( int y=100; y<200; y++ ) 
	{
		uchar* ptr = (uchar*) (img->imageData + y * img->widthStep );
		for( int x=100; x<200; x++ )
		{
			ptr[3*x]   = 255;
			ptr[3*x+1] = 0;
			ptr[3*x+2] = 0;
		}
	}
}

int main(int argc,char **argv)
{
	int frame_num=0;
	CvCapture *capture;
	capture=cvCreateFileCapture("D:\\Document\\vidpic\\video\\video.short.mjpg.avi");

	IplImage *frame;
	IplImage *DispImage;

	cvNamedWindow("画中画",1);
	cvResizeWindow("画中画",980,1020);
	while (1)
	{
		//1:frame 原始视频
		frame=cvQueryFrame( capture );
		if (!frame)
		{
			break;
		}

		//2:frame_not 视频取反
		IplImage *frame_not=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
		cvNot(frame,frame_not);

		//3:frame_gray 彩色视频变灰度视频
		IplImage *frame_gray=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
		IplImage *frame_gray3=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
		cvCvtColor(frame,frame_gray,CV_BGR2GRAY);//frame_gray：得到的灰度图
		cvCvtColor(frame_gray,frame_gray3,CV_GRAY2BGR);

		//4:frame_canny3 caany边缘检测
		IplImage *frame_canny=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
		IplImage *frame_canny3=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
		cvCanny(frame_gray,frame_canny,20,75,3);
		cvCvtColor(frame_canny,frame_canny3,CV_GRAY2BGR);

		//5:frame_Laplacian 拉普拉斯边缘检测
		IplImage *frame_Laplacian=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
		cvLaplace(frame,frame_Laplacian,3);

		//6:frame_smoooth 拉普拉斯边缘平和
		IplImage *frame_smooth=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
		cvSmooth(frame_Laplacian,frame_smooth,CV_GAUSSIAN,3,0,0,0);

		//7:frame_sub 帧差值
		IplImage *frame_sub=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
		IplImage *frame_sub1=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
		IplImage *frame_mid1=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);

		if(frame_num>0)
		{
			cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT,frame_num-1);
			frame=cvQueryFrame( capture );
			cvCvtColor(frame,frame_mid1,CV_BGR2GRAY);
			cvAbsDiff(frame_gray,frame_mid1,frame_sub1);
			cvThreshold( frame_sub1, frame_sub1, 20, 255, CV_THRESH_BINARY );
			cvCvtColor(frame_sub1,frame_sub,CV_GRAY2BGR);
			
			cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT,frame_num+1);
			frame_num++;
		}
		else
		{
			cvAbsDiff(frame_gray,frame_gray,frame_sub1);
			cvCvtColor(frame_sub1,frame_sub,CV_GRAY2BGR);
			frame_num++;
		}
		

		IplImage *frame_test=cvCreateImage(cvGetSize(frame),frame->depth,frame->nChannels);

		cvCopy(frame,frame_test);

		test_frame_proce(frame_test);

		DispImage=cvShow8Images("画中画",8,frame,frame_not,frame_gray3,frame_canny3,frame_Laplacian,frame_smooth,frame_test,frame_sub);

		cvShowImage("画中画",DispImage);
		if(cvWaitKey(33)>=0)
		{
			break;
		}
		cvReleaseImage(&frame_not);
		cvReleaseImage(&frame_gray3);
		cvReleaseImage(&frame_gray);
		cvReleaseImage(&frame_canny3);
		cvReleaseImage(&frame_canny);
		cvReleaseImage(&frame_Laplacian);
		cvReleaseImage(&frame_sub);
	}
	cvReleaseImage(&DispImage);
	cvWaitKey(0);
	cvDestroyWindow("画中画");
	cvReleaseCapture(&capture);
	return 0;
}