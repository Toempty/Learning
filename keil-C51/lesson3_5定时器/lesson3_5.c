#include<reg52.h>
//#define uint unsigned int 
#define uchar unsigned char 
uchar num,num1;tt;
uchar code table[]={
					0x3f,0x06,0x5b,0x4f,
					0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,
					0x39,0x5e,0x79,0x71
					};
void main()
{
	num=0;
	tt=0;
	TMOD=0x01;//���ö�ʱ��0Ϊ������ʽ1
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//����ֵ
	EA=1;//�����ж�
	ET0=1;//��Timer0�ж�
//	TCON=0x01;
	TR0=1;//������ʱ��Timer0
	P1=0xea;//11101010
	P0=0x3f;
	while(1)
	{
		/*if(num1==25)
			{
				num1=0;
			}*/
		if(tt==20)
		   {
				tt=0;
				num++;
				if(num==16)
				num=0;
				P0=table[num];
			}
	}
}
void time0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	tt++;
}
