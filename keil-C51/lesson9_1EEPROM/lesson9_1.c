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
void start()//开始信号
{
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();	
}
void stop()//停止
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}
void delay()//延时
{
	;	;
}
void delay1(uint x)
{
	uint a,b;
	for(a=x;a>0;a--)
		for(b=124;b>0;b--);
}
void respons()//应答
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
	sda=1;//总线释放
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
	sda=1;//不用时把数据总线释放
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
	write_byte(0xa0);//a表示器件地址，0表示接收数据
	respons();//应答
	write_byte(address);//写数据的地址
	respons();//应答
	write_byte(date);//写数据
	respons();//应答
	stop();//停止信号
}
uchar read_add(uchar address)
{
	uchar date;
	start();
	write_byte(0xa0);//a表示器件地址，0表示接收数据
	respons();//应答
	write_byte(address);//读数据的地址
	respons();//应答
	start();
	write_byte(0xa1);//1表示读数据
	respons();
	date=read_byte();
	stop();
	return date;
}
