#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
#define delayNOP();  {_nop_();_nop_();_nop_();_nop_();}

void delay(uchar z);  //z*0.14MS
void delay1(uint ms);//ms=1,1ms
void lcd_wcmd(uchar cmd);//д����
void lcd_wdat(uchar dat);//д����
uchar lcd_busy();//��ʾ״̬���
void lcd_pos(uchar pos);//������ʾλ��
void lcd_init();//lcd��ʼ��

sbit IRIN = P3^2;         //���������������
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
    IRIN=1;                    //I/O�ڳ�ʼ��
    delay1(10);                 //��ʱ

    lcd_init();                //��ʼ��LCD             
        
 // lcd_pos(0);                //������ʾλ��Ϊ��һ�еĵ�1���ַ�

	IE = 0x81;                 //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
	TCON = 0x01;               //������ʽΪ���帺���ش���
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
 
/*lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ� */
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
/*дָ�����ݵ�LCD  */
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


/*д���� */
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

/*  LCD��ʼ��   */
void lcd_init()
{ 
    delay1(15);                   
    lcd_wcmd(0x38);      //16*2��ʾ��5*7����8λ����
    delay1(5);
    lcd_wcmd(0x38);         
    delay1(5);
    lcd_wcmd(0x38);         
    delay1(5);

    lcd_wcmd(0x0c);      //��ʾ�����ع��
    delay1(5);
    lcd_wcmd(0x06);      //�ƶ����
    delay1(5);
    lcd_wcmd(0x01);      //���LCD����ʾ����
    delay1(5);
}

/*  �趨��ʾλ��    */
void lcd_pos(uchar pos)
	{                          
	  lcd_wcmd(pos | 0x80);  //����ָ��=80+��ַ����
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
	                           //ȷ��IR�źų���

  while (!IRIN)            //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
    {
		delay(1);
	}

 for (j=0;j<4;j++)         //�ռ���������
	 { 
		  for (k=0;k<8;k++)        //ÿ��������8λ
			  {
				   while (IRIN)            //�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
				     {
						delay(1);
					 }
					while (!IRIN)          //�� IR ��Ϊ�ߵ�ƽ
					     {	
							 delay(1);
						 }

				     while (IRIN)           //����IR�ߵ�ƽʱ��
				      	{
						    delay(1);
						    N++;           
						    if (N>=30)
								 {
									 EX0=1;
								 	return;
								 }            //0.14ms���������Զ��뿪��
						}                     //�ߵ�ƽ�������                
					  IRCOM[j]=IRCOM[j] >> 1; //�������λ����0��
					  if (N>=8)
						 {
							IRCOM[j] = IRCOM[j] | 0x80;
						 }                    //�������λ����1��
					     N=0;
			  }//end for k
	 }//end for j
   
   if (IRCOM[2]!=~IRCOM[3])
    {
		 EX0=1;
	     return;
	}

   IRCOM[5]=IRCOM[2] & 0x0F;     //ȡ����ĵ���λ
   IRCOM[6]=IRCOM[2] >> 4;       //����4�Σ�����λ��Ϊ����λ




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
