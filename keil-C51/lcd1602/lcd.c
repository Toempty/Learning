#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar i;
sbit lcdwr=P0^5;
sbit lcdrs=P0^4;
sbit lcde=P0^6;
void init();
void delay(uchar z);
void write_com(uchar com);
void write_data(uchar da);
void main()
{
	init();
	write_com(0x0e);
}

void init()
{
	lcdwr=0;//дָ�д����R/W��Ϊ�͵�ƽ
	lcdrs=0;//дָ�RSΪ�͵�ƽ
	lcde=0;
	write_com(0x38);//��ʾ��ʼ������
	write_com(0x0e);//��ʾ���ؼ��������
	write_com(0x01);//����������ָ��
	write_com(0x80+0x10);//��ʼ����ָ��
}
void write_com(uchar com)
{
	lcdwr=0;//дָ�д����R/W��Ϊ�͵�ƽ
	lcdrs=0;//дָ��ʱRS���õ͵�ƽ
	P2=com;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}
void write_data(uchar da)
{
	lcdwr=0;//дָ�д����R/W��Ϊ�͵�ƽ
	lcdrs=1;//д����ʱRS���øߵ�ƽ
	P2=da;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}
void delay(uchar z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
