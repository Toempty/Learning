#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char 
uchar num,num1;tt;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
//void delay(uint z);
void main()
{
	num=0;
	tt=0;
	TMOD=0x11;//���ö�ʱ��0�Ͷ�ʱ��1Ϊ������ʽ1�������ϣ�
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
//	TH1=(65536-20000)/256;
//	TL1=(65536-20000)%256;
	EA=1;//�����ж�
	ET0=1;//����ʱ��0�ж�
	//ET1=1;//����ʱ��1�ж�
	TR0=1;//������ʱ��0
//	TR1=1;//������ʱ��1
	P1=0xea;//11101010
	P0=0x3f;
	while(1)
	{
	/*	if(num1==25)
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

/*void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);	
}*/

void time0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	tt++;
}
/*void time1() interrupt 3
{
	TH1=(65536-20000)/256;
	TL1=(65536-20000)%256;
	num1++;	
}*/
