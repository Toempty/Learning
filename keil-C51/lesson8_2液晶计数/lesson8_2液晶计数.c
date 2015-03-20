#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar i,num;
uchar  code table[]="0123456789";//需写成字符串形式，否则会乱码
uint bai,shi,ge;
sbit lcdwr=P2^5;
sbit lcdrs=P2^6;
sbit lcde=P2^7;
void delay(uint z);
void init();
void write_com(uchar com);
void write_data(uchar da);
void main()
{
	init();
	while(1)
	{		
		write_com(0x80+0x05);
		delay(980);
		num++;
		bai=num/100;
		shi=num%100/10;
		ge=num%10;
		write_data(table[bai]);
		delay(5);
		write_data(table[shi]);
		delay(5);
		write_data(table[ge]);
		write_data(':');
			
	}

}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void init()
{
	lcdwr=0;//写指令，写数据R/W均为低电平
	lcdrs=0;//写指令，RS为低电平
	lcde=0;
	write_com(0x38);//显示初始化设置
	write_com(0x0c);//显示开关及光标设置
	write_com(0x01);//清屏和数据指针
	write_com(0x80+0x10);//初始数据指针
}
void write_com(uchar com)
{
	lcdrs=0;//写指令时RS需置低电平
	P0=com;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}
void write_data(uchar da)
{
	lcdrs=1;//写数据时RS需置高电平
	P0=da;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}