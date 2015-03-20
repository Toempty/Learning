#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp,aa,bai,shi,ge;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void display(uchar bai,uchar shi,uchar ge);//bai��shi��ge���Բ�д��ֻ��֪�����������Ա��ڴ����ռ䣨��Ҫ֪���������ͣ���
void delay(uint z);
void init();
void main()
{	
	init();//��ʼ���ӳ���
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

		P0=table[bai];//�Ͱ�λ
		P1=0xfe;//λѡͨ��
		delay(1);

		P0=table[shi];//��ʮλ
		P1=0xfd;//λѡͨʮ
		delay(1);

		P0=table[ge];//�͸�λ
		P1=0xfb;//λѡͨ��
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
	TR0=1;	//�򿪶�ʱ���ж�
}

void timer0() interrupt 1//��ʱ���ж�
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	aa++;	
}
