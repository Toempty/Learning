#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar temp,t1,t2,qian,bai,shi,ge,flag,flag1;
uint di=3210;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,
0x76,0x79,0x38,0x3f,0};
void delay(uint z);
void init();
void display(uchar a7,uchar a6,uchar a5,uchar a4,uchar qian,uchar bai,uchar shi,uchar ge);
void main()
{
	init();
	while(1)
	{
		if(flag1!=1)
            display(7,6,5,4,qian,bai,shi,ge);
        else
			display(16,17,18,18,19,20,20,20);
		
		
	}	
}
void init()
{
	temp=0xfe;
	P1=temp;
	TMOD=0x11;
    TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
    EA=1;
    ET0=1;
	ET1=1;
	TR0=1;
	TR1=1;
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t1++;
	if(flag!=1)
	{
		if(t1==10)
		{	t1=0;
			temp=_crol_(temp,1);
			P1=temp;
		}
	}
	else
		{
			if(t1%1==0)
			P1=~P1;
			if(t1==60)
			{
				TR0=0;
				P1=0xff;
                flag1=1;
			}
		}
}
void timer1() interrupt 3
{
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	t2++;	
	if(t2==5)
	{
		t2=0;
		di--;
		qian=di/1000;
		bai=di%1000/100;
		shi=di%100/10;
		ge=di%10;	
	}
		if(di==3101)
		{
			TR0=0;
			TH1=(65536-50000)/256;
			TL1=(65536-50000)%256;
			TR0=1;
			t1=0;
			flag=1;
			TR1=0;
		}	    
}
void display(uchar a7,uchar a6,uchar a5,uchar a4,uchar qian,uchar bai,uchar shi,uchar ge)
{
		P0=table[a7];//送a7
		P2=0x7f;//位选通数码管7
		delay(1);	
		P0=table[a6];//送a6
		P2=0xbf;//位数码管6
		delay(1);
		P0=table[a5];//送a5
		P2=0xdf;//位数码管5
		delay(1);
		P0=table[a4];//送a4
		P2=0xef;//位选通数码管a4
		delay(1);

		P0=table[qian];//送千位
		P2=0xf7;//位选通千
		delay(1);

		P0=table[bai];//送百位
		P2=0xfb;//位选通百
		delay(1);

		P0=table[shi];//送十位
		P2=0xfd;//位选通十
		delay(1);

		P0=table[ge];//送个位
		P2=0xfe;//位选通个
		delay(1);
}
	
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
}
