#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit ds=P3^5;
sbit lcdwr=P2^2;
sbit lcdrs=P2^0;
sbit lcde=P2^1;

uchar flag,i;
long uint temp,biaozhi;  //����tempһ��Ҫ����Ϊ int �� 
uchar code table[]="0123456789.-";

void delay(uint z);
void init();
void flash();
void write_com(uchar com);
void write_data(uchar da);
void TempDelay (uchar us) ;
void init_com();
void display(uint temp);
void ds_reset();
bit ds_read_bit();
uchar ds_read_byte(); 
void ds_write_byte(uchar dat);
void tem_change();
uint get_temperature();
extern keynum,m;

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
	write_com(0x80+2);//����������ʾ���ϵ���ʾλ��
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
		write_data(table[10]);
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
//   while(1)
   {

     tem_change();          //12λת��ʱ�����Ϊ750ms
		for(a=10;a>0;a--)
			{
			    display( get_temperature());
			}
	}
}


void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void init()//Һ����ʼ��
{
	lcdwr=0;//дָ�д����R/W��Ϊ�͵�ƽ
	lcdrs=0;//дָ�RSΪ�͵�ƽ
	lcde=0;
	write_com(0x38);//��ʾ��ʼ������
	write_com(0x0e);//��ʾ���ؼ��������
	write_com(0x01);//����������ָ��
	write_com(0x80+8);//��ʼ����ָ��
}

void write_com(uchar com)//Һ��д����
{
	lcdrs=0;//дָ��ʱRS���õ͵�ƽ
	P0=com;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}

void write_data(uchar da)//Һ��д����
{
	lcdrs=1;//д����ʱRS���øߵ�ƽ
	P0=da;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}



