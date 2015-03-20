#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit SCK=P3^6;	//时钟	
sbit SDA=P3^4;	//数据	
sbit RST = P3^5;// DS1302复位
sbit lcdwr=P2^5;
sbit lcdrs=P2^6;
sbit lcde=P2^7;

sbit IRIN = P3^2;         //红外接收器数据线


uchar l_tmpdate[7]={56,34,12,11,8,2,11};//秒分时日月周年11-08-11 12:00:00
uchar l_tmpdisplay[8];

uchar code write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //秒分时日月周年 最低位读写位
uchar code read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  
uchar table[]="0123456789:-";
uchar table1[]="2011-8-11";
uchar table2[]="12:34:56";
uchar i,j; 

/******************************************************************/
/*                    函数声明                                    */
/******************************************************************/												
void Write_Ds1302_byte(unsigned char temp); 
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
void Read_RTC(void);//read RTC 
void Set_RTC(void); //set RTC 
void display();
void delay(uint);
void write_com(uchar com);//写液晶指令
void write_data(uchar da);//写液晶数据
void init();
/******************************************************************/
/*                   主函数                                       */
/******************************************************************/
void main(void)    
{
 	Set_RTC(); //写入时钟值
	init();

 while(1)
	{
		Read_RTC();

		l_tmpdisplay[0]=l_tmpdate[2]/16;			//数据的转换，将数据分开
		l_tmpdisplay[1]=l_tmpdate[2]&0x0f;
		l_tmpdisplay[2]=10;					    	//加入":"
		l_tmpdisplay[3]=l_tmpdate[1]/16;
		l_tmpdisplay[4]=l_tmpdate[1]&0x0f;
		l_tmpdisplay[5]=10;
		l_tmpdisplay[6]=l_tmpdate[0]/16;
		l_tmpdisplay[7]=l_tmpdate[0]&0x0f;
					 
			display();
			delay(1);
	}
}


/******************************************************************/
/*                   写一个字节                                   */
/******************************************************************/
void Write_Ds1302_Byte(uchar temp) 
{
 uchar i;
 for (i=0;i<8;i++)     	//循环8次 写入数据
  { 
   SCK=0;
     SDA=temp&0x01;     //每次传输低字节 
     temp>>=1;  		//右移一位
     SCK=1;
   }
}   
/******************************************************************/
/*                  写入DS1302                                    */
/******************************************************************/
void Write_Ds1302( uchar address,uchar dat )     
{
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;	
   	_nop_();                    //启动
 	Write_Ds1302_Byte(address);	//发送地址
 	Write_Ds1302_Byte(dat);		//发送数据
 	RST=0;  		            //恢复
}
/******************************************************************/
/*                   读出DS1302数据                               */
/******************************************************************/
uchar Read_Ds1302 ( uchar address )
{
 	uchar i,temp=0x00;
 	RST=0;
	_nop_();
	_nop_();
 	SCK=0;
	_nop_();
	_nop_();
 	RST=1;
	_nop_();
	_nop_();
 	Write_Ds1302_Byte(address);
 	for (i=0;i<8;i++) 		//循环8次 读取数据
 	{		
 		if(SDA)
 		temp|=0x80;			//每次传输低字节
		SCK=0;
		temp>>=1;			//右移一位
		_nop_();
	   _nop_();
	   _nop_();
 		SCK=1;
	} 
 	RST=0;
	_nop_();	          	//以下为DS1302复位的稳定时间
 	_nop_();
	RST=0;
	SCK=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCK=1;
	_nop_();
	_nop_();
	SDA=0;
	_nop_();
	_nop_();
	SDA=1;
	_nop_();
	_nop_();
	return (temp);			//返回
}
/******************************************************************/
/*                   读时钟数据                                   */
/******************************************************************/
void Read_RTC(void)	        //读取 日历
{
 uchar i,*p;
 p=read_rtc_address; 	    //地址传递
 for(i=0;i<7;i++)		    //分7次读取 秒分时日月周年
 {
  l_tmpdate[i]=Read_Ds1302(*p);
  p++;
 }
}
/******************************************************************/
/*                  设定时钟数据                                  */
/******************************************************************/
void Set_RTC(void)		    //设定 日历
{
	uchar i,*p,tmp;
	for(i=0;i<7;i++){       //BCD处理
		tmp=l_tmpdate[i]/10;
		l_tmpdate[i]=l_tmpdate[i]%10;
		l_tmpdate[i]=l_tmpdate[i]+tmp*16;
	}  
 	Write_Ds1302(0x8E,0X00);
	
 	p=write_rtc_address;	//传地址	
 	for(i=0;i<7;i++)		//7次写入 秒分时日月周年
 	{
		  Write_Ds1302(*p,l_tmpdate[i]);
 		 p++;  
	 }
	 Write_Ds1302(0x8E,0x80);
}
void display()  //显示
                           
{

    static uchar i,num;

	write_com(0x80+0x40);
	for(i=0;i<8;i++)
		{
			write_data(table[l_tmpdisplay[i]]);	//		   
		}
	j++;
	if(j==8)
	  {
	   j=0;
	   num++;
	  }
 }
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
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
void init()
{
	lcdwr=0;//写指令，写数据R/W均为低电平
	lcdrs=0;//写指令，RS为低电平
	lcde=0;
	write_com(0x38);//显示初始化设置
	write_com(0x0c);//显示开关及光标设置
	write_com(0x01);//清屏和数据指针
	write_com(0x80);//初始数据指针

	for(i=0;i<9;i++)
		{
				write_data(table1[i]);//写数据
				delay(5);					
	}
	write_com(0x80+0x40);
	for(i=0;i<8;i++)
		{
				write_data(table2[i]);//写数据
				delay(5);					
	}
}


