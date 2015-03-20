#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
#define delayNOP();  {_nop_();_nop_();_nop_();_nop_();}

sbit SCK=P0^2;	//ʱ��	
sbit SDA=P0^1;	//����	
sbit RST = P0^0;// DS1302��λ

void delay(uchar z);  //z*0.14MS
void delay1(uint);

uchar lcd_busy();//��ʾ״̬���
void init();//lcd��ʼ��
void Write_Ds1302_byte(uchar); //
void Write_Ds1302( uchar address,uchar dat );//
uchar Read_Ds1302 ( uchar address );//
void Read_RTC(void);//read RTC ��ʱ��оƬ
void Set_RTC(void); //set RTC  ����ʱ��оƬ
void write_data(uchar);
void lcd_wcmd(uchar);
void shizhong();

uchar szflag;
uchar code table[]="0123456789:-.";
uchar table1[]="2011-8-11";
uchar table2[]="12:00:00";
uchar l_tmpdate[7]={0,0,12,11,8,2,11};//���ʱ��������11-08-11 12:00:00
uchar l_tmpdisplay[8];
uchar code write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //���ʱ�������� ���λ��дλ
uchar code read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d}; 

void init_date();//Һ��������ʼ��

sbit IRIN = P3^2;         //���������������
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
long uint temp,biaozhi;  //����tempһ��Ҫ����Ϊ int �� 
sbit ds=P3^7;
uchar flag;
void wendu();

void main()
{    
    IRIN=1;                    //I/O�ڳ�ʼ��
    delay1(5);                 //��ʱ

    init();                //��ʼ��LCD             
        
	IE = 0x81;                 //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
	TCON = 0x01;               //������ʽΪ���帺���ش���
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
    P2 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}


/*д���� */
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

/*  LCD��ʼ��   */
void init()
{ 
    delay1(1);                   
    lcd_wcmd(0x38);      //16*2��ʾ��5*7����8λ����
    delay1(1);
    lcd_wcmd(0x38);         
    delay1(1);

    lcd_wcmd(0x0c);      //��ʾ�����ع��
    delay(1000);
    lcd_wcmd(0x06);      //�ƶ����
    delay(1000);
    lcd_wcmd(0x01);      //���LCD����ʾ����
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
				write_data(table1[i]);//д����
				delay(1);					
		}
}
/////////////////////////1302д�ֽ�
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

//////////////////////д��DS1302                      
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

//////////////////////////����DS1302����
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

/////////////////////////��ʱ������ 
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

////////////////////////�趨ʱ������
void Set_RTC(void)		    //�趨 ����
{
	uchar i,*p,tmp;
	for(i=0;i<7;i++)//BCD����
	{       
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

void shizhong()    
{

    uint i;
	if(szflag==0)
		{	init();
			Set_RTC(); //д��ʱ��ֵ	
			szflag++;
		}

	{
		Read_RTC();	
		lcd_wcmd(0x80);
		init_date();/////////////////////��Ҫ�޸�

		l_tmpdisplay[0]=l_tmpdate[2]/16;			//���ݵ�ת���������ݷֿ�
		l_tmpdisplay[1]=l_tmpdate[2]&0x0f;		//l_tmpdate[0--7]��ķֱ�Ϊ���ʱ��������
		l_tmpdisplay[2]=10;					    	//����":"
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
/*��ʱ����*/
void TempDelay (uchar us)  //�������������us=1ʱԼ����6.9us 
{
   while(us--);
}



/*���ڳ�ʼ����������9600����ʽ1 */
void init_com()
{
   TMOD=0x20;      //���ö�ʱ��1Ϊģʽ2
   TH1=0xfd;       //װ��ֵ�趨������
   TL1=0xfd;
   TR1=1;          //������ʱ��
   SM0=0;          //����ͨ��ģʽ����
   SM1=1;
   PCON=0;         //�����ʲ���Ƶ
}

/*����ܵ���ʾ */
void display(uint temp)
{    
    uchar bai,shi,ge;
		lcd_wcmd(0x80);//����������ʾ���ϵ���ʾλ��
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
    	
        write_data(table[bai]);//��ʾʮλ
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
   TempDelay(80); //������ͣ���ڵ͵�ƽ����480us������������������������λ������
                 //��ʱԼ530us����ͣ���ڵ͵�ƽ����480��s�������ϵ�����������������λ��
   _nop_(); 
   ds=1;           //������λ�����΢�������ͷ�����,�����ߴ��ڿ���״̬

   TempDelay(5); //�ͷ����ߺ��Ա�ӻ�18b20ͨ������������ָʾ���Ƿ�����,
                  //���ڼ��ߵ�ƽʱ�䣺15~60us�� ������ʱ44us������1-wire presence //detect�����ߴ��ڼ�⣩
   _nop_();
   _nop_();
   _nop_();
   if(ds==0)
        flag=1;       //detect 18b20 success
   else
        flag=0;       //detect 18b20 fail
TempDelay(20);    //���ڼ��͵�ƽʱ�䣺60~240us��������ʱԼ140us
   _nop_();
   _nop_();
   ds=1;          //�ٴ��������ߣ������ߴ��ڿ���״̬
}
/*----------------------------------------
��/дʱ��϶:
DS1820 �����ݶ�д��ͨ��ʱ��϶����λ����������ȷ����Ϣ������
------------------------------------------*/
bit ds_read_bit(void)    //��һλ
{
   bit dat;
   ds=0;            //��Ƭ������������
   _nop_();         //��ʱ϶��ʼ��΢��������������������1us
   ds=1;            //�������ߺ�����ͷ����ߣ��ôӻ�18b20�ܹ��ӹ����ߣ������Ч����
   _nop_();
   _nop_();         //С��ʱһ�£���ȡ18b20�ϵ����� ,��Ϊ��ds18b20�����������
                    //�ڶ�"ʱ��϶"�½��س���15us����Ч

   dat=ds;          //�������ӻ�18b20��������ݣ���Щ�����ڶ�ʱ϶���½��س���//15us����Ч 
   TempDelay(10);    //���ж�"ʱ��϶"����60~120us������77us
   return(dat);       //������Ч����
}

/*��һ�ֽ�*/
uchar ds_read_byte(  ) 
{

	uchar value,i,j;
	value=0;             //һ�������˸���ֵ
	for(i=0;i<8;i++)
		{
		    j=ds_read_bit();
		     value=(j<<7)|(value>>1);   
		}
	return(value);        //����һ���ֽڵ�����
}

/*дһ���ֽ�*/
void ds_write_byte(uchar dat) 
{
	  uchar i;
	  bit onebit;        //һ����Ҫ���ˣ�onebit��һλ

	  for(i=1;i<=8;i++) 
	  {
		    onebit=dat&0x01;
		    dat=dat>>1;

			if(onebit)      //д 1
				{
					ds=0;
					_nop_();    
					      _nop_();      //��ʱ��ͼ��������ʱ1us���Ų���д"ʱ��϶"  
					ds=1;       //дʱ��϶��ʼ���15��s�����������������ߵ�ƽ
					     TempDelay(5);  //����дʱ��϶�������ٳ���60us
				}
			else         //д 0
				{
					ds=0;
					     TempDelay(8);    //����Ҫ����һ��д0 ʱ��϶������������������͵�ƽ����������60��s������64us
					ds=1;
					_nop_();
					_nop_();
				}
	  }
}


void tem_change()
{
  ds_reset(); 
  delay(2);              //Լ2ms
  ds_write_byte(0xcc);
  ds_write_byte(0x44);
}

/*----------------------------------------
����¶ȣ�
------------------------------------------*/
uint get_temperature()
{
  float wendu;
  uchar a,b;
  ds_reset();
  delay(1);              //Լ2ms
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

/*��ROM   */
void wendu()
{
   uint a;
   init_com();
   init();



     tem_change();          //12λת��ʱ�����Ϊ750ms
		for(a=10;a>0;a--)
			{
			    display( get_temperature());
			}
}