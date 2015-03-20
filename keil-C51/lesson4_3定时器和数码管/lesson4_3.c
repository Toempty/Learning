#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp,aa,bai,shi,ge;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void display(uchar bai,uchar shi,uchar ge);//bai，shi，ge可以不写，只需知道变量数，以便内存分配空间（需要知道变量类型），
void delay(uint z);
void init();
void main()
{	
	init();//初始化子程序
	while(1)
	{
		if(aa==20)
		  {
			aa=0;
			temp++;
			if(temp==100)
			   {
					temp=0;
			   }
			bai=temp/100;
			shi=temp%100/10;
			ge=temp%10;
		  }
		display(bai,shi,ge);
	}
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void display(uchar bai,uchar shi,uchar ge)
{

		P0=table[bai];//送百位
		P1=0xfe;//位选通百
		delay(1);

		P0=table[shi];//送十位
		P1=0xfd;//位选通十
		delay(1);

		P0=table[ge];//送个位
		P1=0xfb;//位选通个
		delay(1);
}

void init()
{	

	temp=0;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;	//打开定时器中断
}

void timer0() interrupt 1//定时器中断
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	aa++;	
}
