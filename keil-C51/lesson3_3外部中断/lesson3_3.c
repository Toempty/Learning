#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char 

sbit d1=P2^5;
uchar num;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delay(uint z);
void main()
{
	EA=1;//�����ж�,�α�341ҳ
	EX0=1;//���ⲿ�ж�0
    IT0=1;//(������)
	P2=0xea;//11101010
	while(1)
	{
		for(num=0;num<16;num++)
			{
				d1=1;
				P0=table[num];
				delay(1000);	
			}
	}
}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);	
}

void exter0() interrupt 0
{
	d1=0;
}
