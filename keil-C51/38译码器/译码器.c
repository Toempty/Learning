#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
 uchar display1[8];

uchar code  table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};

sbit LS138A=P2^2;
sbit LS138B=P2^3;
sbit LS138C=P2^4;

void init();
void delay(uint);
void display(uchar,uchar,uchar,uchar,uchar,uchar);

uint num,i,numshi,numfen,nummiao,shi1,shi2,fen1,fen2,miao1,miao2;

void main()
{
	init();

	while(1)
		{
			shi1=numshi/10;
			shi2=numshi%10;
			fen1=numfen/10;
			fen2=numfen%10;
			miao1=nummiao/10;
			miao2=nummiao%10;
			display(shi1,shi2,fen1,fen2,miao1,miao2);
		}
}
void display(uchar a,uchar b,uchar c,uchar d,uchar e,uchar f)
{
  

  	i=0;LS138A=0; LS138B=0; LS138C=0;
	P0=table[a];
	delay(1);
	P0=0;
	i=1;LS138A=1; LS138B=0; LS138C=0;
	P0=table[b];
	delay(1);
	P0=0;

	i=2;LS138A=0; LS138B=1; LS138C=0;
	P0=0x40;
	delay(1);
	P0=0;

	i=3;LS138A=1; LS138B=1; LS138C=0;
	P0=table[c];
	delay(1);
	P0=0;

	i=4;LS138A=0; LS138B=0; LS138C=1;
	P0=table[d];
	delay(1);
	P0=0;

	i=5;LS138A=1; LS138B=0; LS138C=1;
	P0=0x40;
	delay(1);
	P0=0;

	i=6;LS138A=0; LS138B=1; LS138C=1;
	P0=table[e];
	delay(1);
	P0=0;

	i=7;LS138A=1; LS138B=1; LS138C=1;
	P0=table[f];
	delay(1);
	P0=0;

	
}

void timer0()interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
	if(num==20)
			{
			nummiao++;//秒数
			num=0;
			if(nummiao%60==0)
					{
						numfen++;//分数
						nummiao=0;
						 if(numfen%60==0)
							{
								numshi++;//时数
								numfen=0;
								if(numshi==24)
									{
										numshi=0;
									}
							}
					}
		}
}

void init()
{
	TMOD=0x01;//设置定时器0为工作方式1
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;//赋初值
	EA=1;//开总中断
	ET0=1;//开Timer0中断
	TR0=1;//启动定时器Timer0
	LS138A=0;
	LS138B=0;
	LS138C=0;
}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
}
