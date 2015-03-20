#include <reg52.h>
#define uchar unsigned char
#define uint unsigned  int
uchar i;
uchar  code table[]="0123456789";//需写成字符串形式，否则会乱码
uint shi1,shi2,fen1,fen2,miao1,miao2,num,numshi,numfen,nummiao;
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
	write_com(0x80+0x05);
	write_com(0x0f);
	while(1)
	{		
	
		write_com(0x80+0x05);//设置初始地址
				shi1=numshi/10;
				shi2=numshi%10;
				fen1=numfen/10;
				fen2=numfen%10;
				miao1=nummiao/10;
				miao2=nummiao%10;

				write_data(table[shi1]);
				delay(0);
				write_data(table[shi2]);
				write_data(':');
				delay(0);

				write_data(table[fen1]);
				delay(0);
				write_data(table[fen2]);
				write_data(':');
				delay(0);

				write_data(table[miao1]);
				delay(0);
				write_data(table[miao2]);
				delay(0);
			
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
	TMOD=0x01;//对TMOD赋值，以确定T0和T1的工作方式
	TH0=(65536-50000)/256;//赋初值
	TL0=(65536-50000)%256;
	EA=1;//开总中断
	ET0=1;//开定时中断0
	TR0=1;//启动定时器
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
	delay(4);
	lcde=1;//高脉冲，写数据
	delay(4);
	lcde=0;
}
void write_data(uchar da)
{
	lcdrs=1;//写数据时RS需置高电平
	P0=da;//DB0-DB7
	delay(4);
	lcde=1;//高脉冲，写数据
	delay(4);
	lcde=0;
}
void timer0 ()interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
	if(num%20==0)
		{
			nummiao++;//秒数
			num=0;
			if(nummiao%60==0)
					{
						numfen++;//分数
						nummiao=0;
						 if(numfen%60==0)
							{
								numshi++;//时数
								numfen=0;
								if(numshi==24)
									{
										numshi=0;
									}
							}
					}
		}

}
