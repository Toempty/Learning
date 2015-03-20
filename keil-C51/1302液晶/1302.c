#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit SCK=P3^6;	//ʱ��	
sbit SDA=P3^4;	//����	
sbit RST = P3^5;// DS1302��λ
sbit lcdwr=P2^5;
sbit lcdrs=P2^6;
sbit lcde=P2^7;

sbit IRIN = P3^2;         //���������������


uchar l_tmpdate[7]={56,34,12,11,8,2,11};//���ʱ��������11-08-11 12:00:00
uchar l_tmpdisplay[8];

uchar code write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //���ʱ�������� ���λ��дλ
uchar code read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  
uchar table[]="0123456789:-";
uchar table1[]="2011-8-11";
uchar table2[]="12:34:56";
uchar i,j; 

/******************************************************************/
/*                    ��������                                    */
/******************************************************************/												
void Write_Ds1302_byte(unsigned char temp); 
void Write_Ds1302( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302 ( unsigned char address );
void Read_RTC(void);//read RTC 
void Set_RTC(void); //set RTC 
void display();
void delay(uint);
void write_com(uchar com);//дҺ��ָ��
void write_data(uchar da);//дҺ������
void init();
/******************************************************************/
/*                   ������                                       */
/******************************************************************/
void main(void)    
{
 	Set_RTC(); //д��ʱ��ֵ
	init();

 while(1)
	{
		Read_RTC();

		l_tmpdisplay[0]=l_tmpdate[2]/16;			//���ݵ�ת���������ݷֿ�
		l_tmpdisplay[1]=l_tmpdate[2]&0x0f;
		l_tmpdisplay[2]=10;					    	//����":"
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
/*                   дһ���ֽ�                                   */
/******************************************************************/
void Write_Ds1302_Byte(uchar temp) 
{
 uchar i;
 for (i=0;i<8;i++)     	//ѭ��8�� д������
  { 
   SCK=0;
     SDA=temp&0x01;     //ÿ�δ�����ֽ� 
     temp>>=1;  		//����һλ
     SCK=1;
   }
}   
/******************************************************************/
/*                  д��DS1302                                    */
/******************************************************************/
void Write_Ds1302( uchar address,uchar dat )     
{
 	RST=0;
	_nop_();
 	SCK=0;
	_nop_();
 	RST=1;	
   	_nop_();                    //����
 	Write_Ds1302_Byte(address);	//���͵�ַ
 	Write_Ds1302_Byte(dat);		//��������
 	RST=0;  		            //�ָ�
}
/******************************************************************/
/*                   ����DS1302����                               */
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
 	for (i=0;i<8;i++) 		//ѭ��8�� ��ȡ����
 	{		
 		if(SDA)
 		temp|=0x80;			//ÿ�δ�����ֽ�
		SCK=0;
		temp>>=1;			//����һλ
		_nop_();
	   _nop_();
	   _nop_();
 		SCK=1;
	} 
 	RST=0;
	_nop_();	          	//����ΪDS1302��λ���ȶ�ʱ��
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
	return (temp);			//����
}
/******************************************************************/
/*                   ��ʱ������                                   */
/******************************************************************/
void Read_RTC(void)	        //��ȡ ����
{
 uchar i,*p;
 p=read_rtc_address; 	    //��ַ����
 for(i=0;i<7;i++)		    //��7�ζ�ȡ ���ʱ��������
 {
  l_tmpdate[i]=Read_Ds1302(*p);
  p++;
 }
}
/******************************************************************/
/*                  �趨ʱ������                                  */
/******************************************************************/
void Set_RTC(void)		    //�趨 ����
{
	uchar i,*p,tmp;
	for(i=0;i<7;i++){       //BCD����
		tmp=l_tmpdate[i]/10;
		l_tmpdate[i]=l_tmpdate[i]%10;
		l_tmpdate[i]=l_tmpdate[i]+tmp*16;
	}  
 	Write_Ds1302(0x8E,0X00);
	
 	p=write_rtc_address;	//����ַ	
 	for(i=0;i<7;i++)		//7��д�� ���ʱ��������
 	{
		  Write_Ds1302(*p,l_tmpdate[i]);
 		 p++;  
	 }
	 Write_Ds1302(0x8E,0x80);
}
void display()  //��ʾ
                           
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
	lcdrs=0;//дָ��ʱRS���õ͵�ƽ
	P0=com;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}
void write_data(uchar da)
{
	lcdrs=1;//д����ʱRS���øߵ�ƽ
	P0=da;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}
void init()
{
	lcdwr=0;//дָ�д����R/W��Ϊ�͵�ƽ
	lcdrs=0;//дָ�RSΪ�͵�ƽ
	lcde=0;
	write_com(0x38);//��ʾ��ʼ������
	write_com(0x0c);//��ʾ���ؼ��������
	write_com(0x01);//����������ָ��
	write_com(0x80);//��ʼ����ָ��

	for(i=0;i<9;i++)
		{
				write_data(table1[i]);//д����
				delay(5);					
	}
	write_com(0x80+0x40);
	for(i=0;i<8;i++)
		{
				write_data(table2[i]);//д����
				delay(5);					
	}
}


