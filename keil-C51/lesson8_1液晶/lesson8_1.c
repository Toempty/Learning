#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table []="WHO ARE YOU?";
uchar code table1 []="I AM LICHAO!";
uchar code table2[]="AND YOU?    ";
uchar code table3[]="I AM123?    ";
uchar i;
sbit lcdwr=P0^5;
sbit lcdrs=P0^4;
sbit lcde=P0^6;
void delay(uchar z);
void init();
void flash();
void write_com(uchar com);
void write_data(uchar da);
void main()
{
	init();
	for(i=0;i<12;i++)
		{
				write_data(table[i]);//写数据
				delay(50);					
	}
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(1000);
		 }
			
	write_com(0x80+0x40+0x10);//重新设置数据指针，使开始在第二行显示
	for(i=0;i<12;i++)
		{
				delay(50);
				write_data(table1[i]);//写数据			
	}
    flash();//闪烁
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(500);
		 }
		
		
		delay(1000);
		init();//初始化
for(i=0;i<12;i++)
		{
				write_data(table2[i]);//写数据
				delay(50);					
	}
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(1000);
		 }
			
	write_com(0x80+0x40+0x10);//重新设置数据指针，使开始在第二行显示
	for(i=0;i<12;i++)
		{
				delay(50);
				write_data(table3[i]);//写数据			
	}
    flash();//闪烁
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(500);
		 }

	while(1);
}
void delay(uchar z)
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
	write_com(0x0e);//显示开关及光标设置
	write_com(0x01);//清屏和数据指针
	write_com(0x80+0x10);//初始数据指针
}
void write_com(uchar com)
{
	lcdrs=0;//写指令时RS需置低电平
	P2=com;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}
void write_data(uchar da)
{
	lcdrs=1;//写数据时RS需置高电平
	P2=da;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}
void flash()    //闪烁子程序                                                           
{                                                                          
    delay(600);                     //控制停留时间                         
    write_com(0x08);            //关闭显示                                  
    delay(200);                    //延时                                  
    write_com(0x0c);            //开显示                                    
    delay(200);                                                            
    write_com(0x08);            //关闭显示                                  
    delay(200);                     //延时                                 
    write_com(0x0c);            //开显示                                    
    delay(200);                                                            
}    