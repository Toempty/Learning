#include<reg52.h>// AD/DA
#define uchar unsigned char
#define uint unsigned int
sbit scl=P2^1;
sbit sda=P2^0;
void delay(uint z)
{
	uint t1,y;
	for(t1=z;t1>0;t1--)
		for(y=124;y>0;y--);
}
void init();
void start();
void main()
{
	init();
	while(1)
	{
		start();
		delay(10);
		sda=1;
       delay(10);
		sda=0;
		delay(10);
	}	
}

void init()
{
	P0=0;
}
void start()
{
	scl=0;
	scl=1;
	scl=0;	
}

