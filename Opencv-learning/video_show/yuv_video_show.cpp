//#include "stdafx.h"

#include "cv.h"
#include "highgui.h"
#include <string>


using namespace cv;
using namespace std;
int main( )
{
	FILE *fp;
	int type_cif=4;//代表cif的类型 default：sub_QCIF 1:QCIF 2:CIF 4:4CIF 8:16CIF
	int width=0;   //每一帧的宽度
	int hight=0;   //每一帧的长度
	int frames=300;  //帧数
	//int aa;

	errno_t ff;			//标记是否成功打开文件
	char originalfiel[50];
	if(type_cif==2)
	{
		sprintf_s(originalfiel,"crew-720p.yuv");
	}
	else if(type_cif==4)
	{
		sprintf_s(originalfiel,"original_300fps_4CIF.yuv");
	}
	else if(type_cif==1)
	{
		sprintf_s(originalfiel,"akiyo_qcif.yuv");
	}
	ff=fopen_s(&fp,originalfiel,"rb");//成功ff=0,否则，ff!=0 
	
	if(ff!=0)
	{
		cout<<"error"<<endl;
		exit(0);
	}

	switch (type_cif) //根据类型选择视频每帧的大小
	{
	case 1  :hight=144,   width=176;  break;//QCIF
	case 2  :hight=144*2, width=176*2;break;//CIF
	case 4  :hight=144*4, width=176*4;break;//4CIF
	case 8  :hight=144*8, width=176*8;break;//16CIF
	default :hight=128,   width=96;   break;//sub_QCIF
	}

	int sz[3] = {hight, width,3};
	Mat mat_image(3, sz, CV_8U, Scalar::all(0));
	uchar* p = mat_image.data;

	cvNamedWindow("YUV视频显示",1);


	uchar *maty = (uchar*)malloc(width*hight * sizeof(uchar));//读入Y分量
	uchar *matu = (uchar*)malloc(width*hight * sizeof(uchar)/4);//读入U分量
	uchar *matv = (uchar*)malloc(width*hight * sizeof(uchar)/4);//读入V分量

	double Y,U,V,R,G,B;

	for (int frame_i=0;frame_i<frames;frame_i++)
	{
		//fread(matyy,sizeof(uchar),hight*width,fp);
		//fread(matuu,sizeof(uchar),hight*width/4,fp);
		//fread(matvv,sizeof(uchar),hight*width/4,fp);

		fread(maty,sizeof(uchar),hight*width,fp);
		fread(matu,sizeof(uchar),hight*width/4,fp);
		fread(matv,sizeof(uchar),hight*width/4,fp);



		for(int j=0;j<width;j++)
		{
			for(int i=0;i<hight;i++)
			{
				Y=double(maty[j*hight+i]);
				U=double(matu[j*hight/4+i/2]);
				V=double(matv[j*hight/4+i/2]);
				
				R=Y+1.140*(V-128);
				G=Y-0.395*(U-128)-0.581*(V-128);
				B=Y+2.032*(U-128);
				//Y=maty[j*hight+i];
				//U=matu[j*hight/4+i/2];
				//V=matv[j*hight/4+i/2];
				//
				//R=uchar((int(298*(Y-16)+409*(V-128)+128))>>8);
				//G=uchar((int(298*(Y-16)+100*(U-128)+208*(V-128)+128))>>8);
				//B=uchar((int(298*(Y-16)+516*(U-128)+128))>>8);
				//R=Y+1.402*(V-128);
				//G=Y-0.34414*(U-128)-0.71414*(V-128);
				//B=Y+1.772*(U-128);

				R=R>255 ? 255:R;
				R=R<0   ? 0:R;
				G=G>255 ? 255:G;
				G=G<0   ? 0:G;
				B=B>255 ? 255:B;
				B=B<0   ? 0:B;


				p[j*hight+i]=uchar(B);
				p[hight*width+j*hight+i]=uchar(G);
				p[2*hight*width+j*hight+i]=uchar(R);
				if(i>=574)
				{
					cout<<"j="<<j<<endl;
					cout<<i<<endl;
				}
			}
		}
		imshow("YUV视频显示",mat_image);

			cvWaitKey(10);
		
	}
	//cvReleaseImage(&frame);
	cvWaitKey(1000);
	cvDestroyWindow("YUV视频显示");
	return 0;
}