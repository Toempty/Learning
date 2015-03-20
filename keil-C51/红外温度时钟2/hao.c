#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
#define delayNOP();  {_nop_();_nop_();_nop_();_nop_();}

sbit SCK=P0^2;	//时钟	
sbit SDA=P0^1;	//数据	
sbit RST = P0^0;// DS1302复位

void delay(uchar z);  //z*0.14MS
void delay1(uint);

uchar lcd_busy();//显示状态检测
void init();//lcd初始化
void Write_Ds1302_byte(uchar); //
void Write_Ds1302( uchar address,uchar dat );//
uchar Read_Ds1302 ( uchar address );//
void Read_RTC(void);//read RTC 读时钟芯片
void Set_RTC(void); //set RTC  设置时钟芯片
void write_data(uchar);
void lcd_wcmd(uchar);
void shizhong();

uchar szflag;
uchar code table[]="0123456789:-.";
uchar table1[]="2011-8-11";
uchar table2[]="12:00:00";
uchar l_tmpdate[7]={0,0,12,11,8,2,11};//秒分时日月周年11-08-11 12:00:00
uchar l_tmpdisplay[8];
uchar code write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //秒分时日月周年 最低位读写位
uchar code read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d}; 

void init_date();//液晶日历初始化

sbit IRIN = P3^2;         //红外接收器数据线
sbit LCD_RS = P0^4;             
sbit LCD_RW = P0^5;
sbit LCD_EN = P0^6;


uchar IRCOM[7];
uchar keynum;
uchar code table3[]="0123456789ABCDEFGHIJK";

void TempDelay (uchar us) ;
void init_com();
void display(uint temp);
void ds_reset();
bit ds_read_bit();
uchar ds_read_byte(); 
void ds_write_byte(uchar dat);
void tem_change();
uint get_temperature();
long uint temp,biaozhi;  //参数temp一定要声明为 int 型 
sbit ds=P3^7;
uchar flag;
void wendu();

void main()
{    
    IRIN=1;                    //I/O口初始化
    delay1(5);                 //延时

    init();                //初始化LCD             
        
	IE = 0x81;                 //允许总中断中断,使能 INT0 外部中断
	TCON = 0x01;               //触发方式为脉冲负边沿触发
	lcd_wcmd(0x0c);
	delay(2);
	shizhong();
    while(1)
		{
			while(keynum==17)	
	
			{init();
			lcd_wcmd(0x80+0x40);
			write_data(table[1]);
			delay(70);
			write_data(table[2]);
			}

			while(keynum==18)	
	
			{init();
			lcd_wcmd(0x80+0x40);
			write_data(table[3]);
			delay(70);
			write_data(table[4]);
			}
			while(keynum==0)
			shizhong();
			while(keynum==1)
			wendu();
		}
			

}
 
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。 */
uchar lcd_busy()
{
	uchar result;
	LCD_RS=0;
	LCD_RW=1;
	LCD_EN=1;
	delayNOP();
	result=(bit)(P0&0x80);
	LCD_EN=0;
	return(result);
}
/*写指令数据到LCD  */
void lcd_wcmd(uchar cmd)
{                          
   while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P2 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}


/*写数据 */
void write_data(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P2 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}

/*  LCD初始化   */
void init()
{ 
    delay1(1);                   
    lcd_wcmd(0x38);      //16*2显示，5*7点阵，8位数据
    delay1(1);
    lcd_wcmd(0x38);         
    delay1(1);

    lcd_wcmd(0x0c);      //显示开，关光标
    delay(1000);
    lcd_wcmd(0x06);      //移动光标
    delay(1000);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(1000);
}

void IR_IN() interrupt 0 using 0
{
     uchar j,k,N=0;
     EX0 = 0;   
	 delay(15);

	 if (IRIN==1) 
	     { EX0 =1;
		   return;
		 } 
	                           //确认IR信号出现

  while (!IRIN)            //等IR变为高电平，跳过9ms的前导低电平信号。
    {
		delay(1);
	}

 for (j=0;j<4;j++)         //收集四组数据
	 { 
		  for (k=0;k<8;k++)        //每组数据有8位
			  {
				   while (IRIN)            //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
				     {
						delay(1);
					 }
					while (!IRIN)          //等 IR 变为高电平
					     {	
							 delay(1);
						 }

				     while (IRIN)           //计算IR高电平时长
				      	{
						    delay(1);
						    N++;           
						    if (N>=30)
								 {
									 EX0=1;
								 	return;
								 }            //0.14ms计数过长自动离开。
						}                     //高电平计数完毕                
					  IRCOM[j]=IRCOM[j] >> 1; //数据最高位补“0”
					  if (N>=8)
						 {
							IRCOM[j] = IRCOM[j] | 0x80;
						 }                    //数据最高位补“1”
					     N=0;
			  }//end for k
	 }//end for j
   
   if (IRCOM[2]!=~IRCOM[3])
    {
		 EX0=1;
	     return;
	}
	switch(IRCOM[2])
		{
			case   0x16 : keynum=0;break;
			case   0x0C : keynum=1;break;
			case   0x18 : keynum=2;break;
			case   0x5E : keynum=3;break;
			case   0x08 : keynum=4;break;
			case   0x1C : keynum=5;break;
			case   0x5A : keynum=6;break;
			case   0x42 : keynum=7;break;
			case   0x52 : keynum=8;break;
			case   0x4A : keynum=9;break;
			case   0x45 : keynum=10;break;
			case   0x46 : keynum=11;break;
			case   0x47 : keynum=12;break;
			case   0x44 : keynum=13;break;
			case   0x40 : keynum=14;break;
			case   0x43 : keynum=15;break;
			case   0x07 : keynum=16;break;
			case   0x15 : keynum=17;break;
			case   0x09 : keynum=18;break;
			case   0x19 : keynum=19;break;
			case   0x0D : keynum=20;break;
		}
     EX0 = 1; 
} 


void delay(uchar z)    //z*0.14MS
{
 	uchar i;
  	while(z--)
		 {
		  for (i = 0; i<13; i++) {}
		 }
}
void delay1(uint z)
{
	uint x,y;
		for(x=z;x>0;x--)
			for(y=124;y>0;y--);
}

/**********************************************************/

void init_date()
{
		uint i;
		for(i=0;i<9;i++)
		{
				write_data(table1[i]);//写数据
				delay(1);					
		}
}
/////////////////////////1302写字节
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

//////////////////////写入DS1302                      
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

//////////////////////////读出DS1302数据
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

/////////////////////////读时钟数据 
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

////////////////////////设定时钟数据
void Set_RTC(void)		    //设定 日历
{
	uchar i,*p,tmp;
	for(i=0;i<7;i++)//BCD处理
	{       
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

void shizhong()    
{

    uint i;
	if(szflag==0)
		{	init();
			Set_RTC(); //写入时钟值	
			szflag++;
		}

	{
		Read_RTC();	
		lcd_wcmd(0x80);
		init_date();/////////////////////需要修改

		l_tmpdisplay[0]=l_tmpdate[2]/16;			//数据的转换，将数据分开
		l_tmpdisplay[1]=l_tmpdate[2]&0x0f;		//l_tmpdate[0--7]存的分别为秒分时日月周年
		l_tmpdisplay[2]=10;					    	//加入":"
		l_tmpdisplay[3]=l_tmpdate[1]/16;
		l_tmpdisplay[4]=l_tmpdate[1]&0x0f;
		l_tmpdisplay[5]=10;
		l_tmpdisplay[6]=l_tmpdate[0]/16;
		l_tmpdisplay[7]=l_tmpdate[0]&0x0f; 
	
		lcd_wcmd(0x80+0x40);	
		for(i=0;i<8;i++)
			{
				write_data(table[l_tmpdisplay[i]]);	
				delay(2);		   
			}
	}		
}
/*延时函数*/
void TempDelay (uchar us)  //经验表明，这里us=1时约等于6.9us 
{
   while(us--);
}



/*串口初始化，波特率9600，方式1 */
void init_com()
{
   TMOD=0x20;      //设置定时器1为模式2
   TH1=0xfd;       //装初值设定波特率
   TL1=0xfd;
   TR1=1;          //启动定时器
   SM0=0;          //串口通信模式设置
   SM1=1;
   PCON=0;         //波特率不倍频
}

/*数码管的显示 */
void display(uint temp)
{    
    uchar bai,shi,ge;
		lcd_wcmd(0x80);//决定了在显示屏上的显示位置
    {
      	 bai=temp/100;
         shi=temp/10%10;
	     ge=temp%10;

	   if(biaozhi==1)
		     {
		     	biaozhi=0;
		        delay(2);
		        write_data(table[11]);
		        delay(2);
		 	}
    	
        write_data(table[bai]);//显示十位
     	delay(2);
        write_data(table[shi]);  
		delay(2);
		write_data(table[12]);
    	delay(2);
        write_data(table[ge]);
        delay(2);
	  }
 }

void ds_reset(void)
{
   ds=1;
   _nop_();        //1us
   ds=0;
   TempDelay(80); //当总线停留在低电平超过480us，总线上所以器件都将被复位，这里
                 //延时约530us总线停留在低电平超过480μs，总线上的所有器件都将被复位。
   _nop_(); 
   ds=1;           //产生复位脉冲后，微处理器释放总线,让总线处于空闲状态

   TempDelay(5); //释放总线后，以便从机18b20通过拉低总线来指示其是否在线,
                  //存在检测高电平时间：15~60us， 所以延时44us，进行1-wire presence //detect（单线存在检测）
   _nop_();
   _nop_();
   _nop_();
   if(ds==0)
        flag=1;       //detect 18b20 success
   else
        flag=0;       //detect 18b20 fail
TempDelay(20);    //存在检测低电平时间：60~240us，所以延时约140us
   _nop_();
   _nop_();
   ds=1;          //再次拉高总线，让总线处于空闲状态
}
/*----------------------------------------
读/写时间隙:
DS1820 的数据读写是通过时间隙处理位和命令字来确认信息交换。
------------------------------------------*/
bit ds_read_bit(void)    //读一位
{
   bit dat;
   ds=0;            //单片机将总线拉低
   _nop_();         //读时隙起始于微处理器将总线拉低至少1us
   ds=1;            //拉低总线后接着释放总线，让从机18b20能够接管总线，输出有效数据
   _nop_();
   _nop_();         //小延时一下，读取18b20上的数据 ,因为从ds18b20上输出的数据
                    //在读"时间隙"下降沿出现15us内有效

   dat=ds;          //主机读从机18b20输出的数据，这些数据在读时隙的下降沿出现//15us内有效 
   TempDelay(10);    //所有读"时间隙"必须60~120us，这里77us
   return(dat);       //返回有效数据
}

/*读一字节*/
uchar ds_read_byte(  ) 
{

	uchar value,i,j;
	value=0;             //一定别忘了给初值
	for(i=0;i<8;i++)
		{
		    j=ds_read_bit();
		     value=(j<<7)|(value>>1);   
		}
	return(value);        //返回一个字节的数据
}

/*写一个字节*/
void ds_write_byte(uchar dat) 
{
	  uchar i;
	  bit onebit;        //一定不要忘了，onebit是一位

	  for(i=1;i<=8;i++) 
	  {
		    onebit=dat&0x01;
		    dat=dat>>1;

			if(onebit)      //写 1
				{
					ds=0;
					_nop_();    
					      _nop_();      //看时序图，至少延时1us，才产生写"时间隙"  
					ds=1;       //写时间隙开始后的15μs内允许数据线拉到高电平
					     TempDelay(5);  //所有写时间隙必须最少持续60us
				}
			else         //写 0
				{
					ds=0;
					     TempDelay(8);    //主机要生成一个写0 时间隙，必须把数据线拉到低电平并保持至少60μs，这里64us
					ds=1;
					_nop_();
					_nop_();
				}
	  }
}


void tem_change()
{
  ds_reset(); 
  delay(2);              //约2ms
  ds_write_byte(0xcc);
  ds_write_byte(0x44);
}

/*----------------------------------------
获得温度：
------------------------------------------*/
uint get_temperature()
{
  float wendu;
  uchar a,b;
  ds_reset();
  delay(1);              //约2ms
  ds_write_byte(0xcc);
  ds_write_byte(0xbe);
  a=ds_read_byte();
  b=ds_read_byte();
  temp=b;
  temp<<=8;
  temp=temp|a;
  wendu=temp*0.0625;     
  temp=wendu*10+0.5;
  return temp;
}

/*读ROM   */
void wendu()
{
   uint a;
   init_com();
   init();



     tem_change();          //12位转换时间最大为750ms
		for(a=10;a>0;a--)
			{
			    display( get_temperature());
			}
}