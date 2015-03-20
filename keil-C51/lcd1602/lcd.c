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
	lcdwr=0;//写指令，写数据R/W均为低电平
	lcdrs=0;//写指令，RS为低电平
	lcde=0;
	write_com(0x38);//显示初始化设置
	write_com(0x0e);//显示开关及光标设置
	write_com(0x01);//清屏和数据指针
	write_com(0x80+0x10);//初始数据指针
}
void write_com(uchar com)
{
	lcdwr=0;//写指令，写数据R/W均为低电平
	lcdrs=0;//写指令时RS需置低电平
	P2=com;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}
void write_data(uchar da)
{
	lcdwr=0;//写指令，写数据R/W均为低电平
	lcdrs=1;//写数据时RS需置高电平
	P2=da;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}
void delay(uchar z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
