#include <reg52.h>
#include<EEPROM.h>
void main()
{
	init();
	write_add(13,1);

	delay1(100);
	
	P0=read_add(13);
	while(1);
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
	scl=1;//
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
}
