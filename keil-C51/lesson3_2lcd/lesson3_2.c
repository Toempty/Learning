#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char 
uchar num;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delay(uint z);
void main()
{
	P0=0xea;//11101010
	while(1)
	{
		for(num=0;num<16;num++)
			{
				P0=table[num];
				delay(1000);	
			}
	}
}

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);	
}