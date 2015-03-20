#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit sda=P2^0;
sbit scl=P2^1;
uchar temp,aa,bai,shi,ge;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void start();
void stop();
void delay();
void delay1(uint);
void init();
void respons();
void display(uchar bai,uchar shi,uchar ge);
void write_byte(uchar date);
void write_add(uchar address,uchar date);
uchar read_byte();
uchar read_add(uchar address);
uchar num,bai,ge,shi;
uint t;
void main()
{
	init();
	while(1)
		{
			
			bai=t/100;
			shi=t%100/10;
			ge=t%10;
			display(bai,shi,ge);
		}
}
void start()//��ʼ�ź�
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();	
}
void stop()//ֹͣ
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}
void delay()//��ʱ
{
	;	;
}
void delay1(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=124;b>0;b--);
}
void respons()//Ӧ��
{
	uchar i;
	scl=1;
	delay();
	while((sda==1)&&(i<250))
			i++;
	scl=0;
	delay();
}
void init()
{
	sda=1;//�����ͷ�
	scl=1;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}
void write_byte(uchar date)
{
	uchar i,temp;
	temp=date;
	scl=0;
	delay();
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		sda=CY;
		delay();
		scl=1;
		delay();
		scl=0;
		delay();
	}
	sda=1;//����ʱ�����������ͷ�
	delay();
}
uchar read_byte()
{
	uchar i,j,k;
	sda=1;
	delay();
	for (i=0;i<8;i++)
		{
			scl=1;
			delay();
			j=sda;
			k=(k<<1)|j;
			scl=0;
			delay();
		}
	return k;
}
void write_add(uchar address,uchar date)
{
	start();
	write_byte(0xa0);//a��ʾ������ַ��0��ʾ��������
	respons();//Ӧ��
	write_byte(address);//д���ݵĵ�ַ
	respons();//Ӧ��
	write_byte(date);//д����
	respons();//Ӧ��
	stop();//ֹͣ�ź�
}
uchar read_add(uchar address)
{
	uchar date;
	start();
	write_byte(0xa0);//a��ʾ������ַ��0��ʾ��������
	respons();//Ӧ��
	write_byte(address);//�����ݵĵ�ַ
	respons();//Ӧ��
	start();
	write_byte(0xa1);//1��ʾ������
	respons();
	date=read_byte();
	stop();
	return date;
}void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	   num++;
		t=read_add(13);
		if(num%20==0)
		{

			t++;
			num=0;
  			write_add(13,t);
			delay1(10);
		}
}
void display(uchar bai,uchar shi,uchar ge)
{

		P0=table[bai];//�Ͱ�λ
		P1=0xfe;//λѡͨ��
		delay1(1);

		P0=table[shi];//��ʮλ
		P1=0xfd;//λѡͨʮ
		delay1(1);

		P0=table[ge];//�͸�λ
		P1=0xfb;//λѡͨ��
		delay1(1);
}
