#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar temp,num;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0};
void delay(uint z);
void display(uchar);
uchar keyscan();
void main()
{
	num=17;
	temp=P1;
	P0=0;
	P2=0;
	while(1)
	{
		display(keyscan());
	}
}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
}
uchar keyscan()
{
		P1=0xfd;
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
			{
				delay(10);
				P1=0xfd;
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
					{
						temp=P1;
						switch(temp)
							{
								case 0xed:num=1;
										break;
								case 0xdd:num=2;
										break;
								case 0xbd:num=3;
										break;
								case 0x7d:num=4;
										break;
							}
						while(temp!=0xf0)//À… ÷º‡≤‚
							{
								temp=P1;
								temp=temp&0xf0;
							}
					}
			}
		P1=0xfb;
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
			{
				delay(10);
				P1=0xfb;
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
					{
						temp=P1;
						switch(temp)
							{
								case 0xeb:num=5;
										break;
								case 0xdb:num=6;
										break;
								case 0xbb:num=7;
										break;
								case 0x7b:num=8;
										break;
							}
						while(temp!=0xf0)
							{
								temp=P1;
								temp=temp&0xf0;
							}
					}
			}
		P1=0xf7;
		temp=P1;
		temp=temp&0xf0;
		while(temp!=0xf0)
			{
				delay(10);
				P1=0xf7;
				temp=P1;
				temp=temp&0xf0;
				while(temp!=0xf0)
					{
						temp=P1;
						switch(temp)
							{
								case 0xe7:num=9;
										break;
								case 0xd7:num=10;
										break;
								case 0xb7:num=11;
										break;
								case 0x77:num=12;
										break;
							}
						while(temp!=0xf0)
							{
								temp=P1;
								temp=temp&0xf0;
							}
					}
			}
return num;
}
void display(uchar num1)
{
	P0=table[num1-1];
}

