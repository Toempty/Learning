#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp,aa,num;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void main()
{
	num=0;
	aa=0;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	temp=0xfe;//temp=1111 1110 (一)
	P1=temp;
	P0=table[0];
	while(1)
	{
	}
}
void timer0() interrupt 1 //定时器中断
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	aa++;
		if(aa==20)
			{
				aa=0;
				num++;
				if(num==16)
					num=0;
				P0=table[num];		
			temp=_crol_(temp,1);//左移
	 		P1=temp;//如果将（一）及左移和该行删除则八位数码管全亮
		
			}	
}

