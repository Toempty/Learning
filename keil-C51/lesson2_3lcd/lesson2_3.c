#include<reg51.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp;  //P1��Ϊ��λ�Ĵ�����uchar���ǰ�λ��//
void delay(uint);
void main()
{
	temp=0xfe;	
	P1=temp;
	while(1)
	{	
		temp=_crol_(temp,1);
		delay(905);
		P1=temp;   
	}
}
void delay(uint z)
{
	uint x,y;
	for(x=100;x>0;x--)
		for(y=z;y>0;y--);
}