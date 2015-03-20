#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
#define delayNOP();  {_nop_();_nop_();_nop_();_nop_();}

void delay(uchar z);  //z*0.14MS
void delay1(uint ms);//ms=1,1ms
void lcd_wcmd(uchar cmd);//写命令
void lcd_wdat(uchar dat);//写数据
uchar lcd_busy();//显示状态检测
void lcd_pos(uchar pos);//设置显示位置
void lcd_init();//lcd初始化

sbit IRIN = P3^2;         //红外接收器数据线
//sbit LCD_RS = P0^4;             
//sbit LCD_RW = P0^5;
//sbit LCD_EN = P0^6;

sbit LCD_RW=P2^5;
sbit LCD_RS=P2^6;
sbit LCD_EN=P2^7;

uchar IRCOM[7];
uchar keynum;
uchar code table[]="0123456789ABCDEFGHIJK";

void main()
{    
    IRIN=1;                    //I/O口初始化
    delay1(10);                 //延时

    lcd_init();                //初始化LCD             
        
 // lcd_pos(0);                //设置显示位置为第一行的第1个字符

	IE = 0x81;                 //允许总中断中断,使能 INT0 外部中断
	TCON = 0x01;               //触发方式为脉冲负边沿触发
	lcd_wcmd(0x0c);
	delay(2);
    while(1)
		{	
				lcd_pos(4);
				delay(2);
				lcd_wdat(table[IRCOM[6]]);
				delay(8); 
				lcd_wdat(table[IRCOM[5]]);
				delay(8); 
				lcd_wdat(table[keynum]);
				delay(8); 
				
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
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}


/*写数据 */
void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}

/*  LCD初始化   */
void lcd_init()
{ 
    delay1(15);                   
    lcd_wcmd(0x38);      //16*2显示，5*7点阵，8位数据
    delay1(5);
    lcd_wcmd(0x38);         
    delay1(5);
    lcd_wcmd(0x38);         
    delay1(5);

    lcd_wcmd(0x0c);      //显示开，关光标
    delay1(5);
    lcd_wcmd(0x06);      //移动光标
    delay1(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay1(5);
}

/*  设定显示位置    */
void lcd_pos(uchar pos)
	{                          
	  lcd_wcmd(pos | 0x80);  //数据指针=80+地址变量
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

   IRCOM[5]=IRCOM[2] & 0x0F;     //取键码的低四位
   IRCOM[6]=IRCOM[2] >> 4;       //右移4次，高四位变为低四位




		if(IRCOM[2]==0x12)
			{ 
					keynum=10; 
			}
		if(IRCOM[2]==0x1A)
			{ 
					keynum=11; 
			}
		if(IRCOM[2]==0x1E)
			{ 
					keynum=12;  
			}
		if(IRCOM[2]==0x0A)
			{ 
					keynum=13;  
			}
		if(IRCOM[2]==0x1B)
			{ 
					keynum=14;  
			}
		if(IRCOM[2]==0x1F)
			{ 
					keynum=15; 
			}
		if(IRCOM[2]==0x0C)
			{ 
					keynum=16; 
			}
		if(IRCOM[2]==0x0D)
			{ 
					keynum=17;
			}
		if(IRCOM[2]==0x0E)
			{ 
					keynum=18;
			}
		if(IRCOM[2]==0x00)
			{ 
					keynum=0; 
			}
		if(IRCOM[2]==0x0F)
			{ 
					keynum=19; 
			}
		if(IRCOM[2]==0x19)
			{ 
					keynum=20; 
			}
		if(IRCOM[2]==0x01)
			{ 
					keynum=1;
			}
		if(IRCOM[2]==0x02)
			{ 
					keynum=2;
			}
		if(IRCOM[2]==0x03)
			{ 
					keynum=3;
			}
		if(IRCOM[2]==0x04)
			{ 
					keynum=4; 
			}
		if(IRCOM[2]==0x05)
			{ 
					keynum=5; 
			}
		if(IRCOM[2]==0x06)
			{ 
					keynum=6;
			}
		if(IRCOM[2]==0x07)
			{ 
					keynum=7; 
			}
		if(IRCOM[2]==0x08)
			{ 
					keynum=8;  
			}
		if(IRCOM[2]==0x09)
			{ 
					keynum=9; 
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

/**********************************************************/
void delay1(uint ms)//1ms
{
	uint x,y;
		for(x=ms;x>0;x--)
			for(y=124;y>0;y--);
}
