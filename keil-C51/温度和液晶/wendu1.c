#include <reg52.h>
#include <intrins.h>

sbit ds1=P3^4;
unsigned char flag1;
unsigned long  int temp1,biaozhi1;  //����tempһ��Ҫ����Ϊ int �� 
extern unsigned char code table[];

extern delay(unsigned char z);
extern init();
extern write_com(unsigned char com);
extern write_data(unsigned char da);
extern TempDelay (unsigned char us) ;
extern init_com();
void display1(unsigned int temp1);
void ds1_reset();
bit ds1_read_bit();
unsigned char ds1_read_byte(); 
void ds1_write_byte(unsigned char dat);
void tem_change1();
unsigned int get_temperature1();
extern keynum,m;


/*����ܵ���ʾ */
void display1(unsigned int temp1)
{    
    unsigned char bai,shi,ge;
	write_com(0x80+0x40);//����������ʾ���ϵ���ʾλ��
    {
      	 bai=temp1/100;
         shi=temp1/10%10;
	     ge=temp1%10;

	   if(biaozhi1==1)
		     {
		     	biaozhi1=0;
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

void ds1_reset(void)
{
   ds1=1;
   _nop_();        //1us
   ds1=0;
   TempDelay(80); //������ͣ���ڵ͵�ƽ����480us������������������������λ������
                 //��ʱԼ530us����ͣ���ڵ͵�ƽ����480��s�������ϵ�����������������λ��
   _nop_(); 
   ds1=1;           //������λ�����΢�������ͷ�����,�����ߴ��ڿ���״̬
   TempDelay(5); //�ͷ����ߺ��Ա�ӻ�18b20ͨ������������ָʾ���Ƿ�����,
                  //���ڼ��ߵ�ƽʱ�䣺15~60us�� ������ʱ44us������1-wire presence //detect�����ߴ��ڼ�⣩
   _nop_();
   _nop_();
   _nop_();

   if(ds1==0)
        flag1=1;       //detect 18b20 success
   else
        flag1=0;       //detect 18b20 fail


TempDelay(20);    //���ڼ��͵�ƽʱ�䣺60~240us��������ʱԼ140us
   _nop_();
   _nop_();
   ds1=1;          //�ٴ��������ߣ������ߴ��ڿ���״̬
}
/*----------------------------------------
��/дʱ��϶:
DS1820 �����ݶ�д��ͨ��ʱ��϶����λ����������ȷ����Ϣ������
------------------------------------------*/
bit ds1_read_bit(void)    //��һλ
{
   bit dat1;
   ds1=0;            //��Ƭ������������

   _nop_();         //��ʱ϶��ʼ��΢��������������������1us
   ds1=1;            //�������ߺ�����ͷ����ߣ��ôӻ�18b20�ܹ��ӹ����ߣ������Ч����
	_nop_();
   _nop_();         //С��ʱһ�£���ȡ18b20�ϵ����� ,��Ϊ��ds18b20�����������
                    //�ڶ�"ʱ��϶"�½��س���15us����Ч

   dat1=ds1;          //�������ӻ�18b20��������ݣ���Щ�����ڶ�ʱ϶���½��س���//15us����Ч 
	 TempDelay(10);    //���ж�"ʱ��϶"����60~120us������77us
   return(dat1);       //������Ч����
}

/*��һ�ֽ�*/
unsigned char ds1_read_byte(  ) 
{

	unsigned char value,i,j;
	value=0;             //һ�������˸���ֵ
	for(i=0;i<8;i++)
		{
		    j=ds1_read_bit();
		     value=(j<<7)|(value>>1);   
		}
	return(value);        //����һ���ֽڵ�����
}

/*дһ���ֽ�*/
void ds1_write_byte(unsigned char dat1) 
{
	  unsigned char i;
	  bit onebit;        //һ����Ҫ���ˣ�onebit��һλ

	  for(i=1;i<=8;i++) 
	  {
		    onebit=dat1&0x01;
		    dat1=dat1>>1;

			if(onebit)      //д 1
				{
					ds1=0;
					_nop_();    
					      _nop_();      //��ʱ��ͼ��������ʱ1us���Ų���д"ʱ��϶"  
					ds1=1;       //дʱ��϶��ʼ���15��s�����������������ߵ�ƽ
					     TempDelay(5);  //����дʱ��϶�������ٳ���60us
				}
			else         //д 0
				{
					ds1=0;
					     TempDelay(8);    //����Ҫ����һ��д0 ʱ��϶������������������͵�ƽ����������60��s������64us
					ds1=1;
					_nop_();
					_nop_();
				}
	  }
}


void tem_change1()
{
  ds1_reset(); 
  delay(2);              //Լ2ms
  ds1_write_byte(0xcc);
  ds1_write_byte(0x44);
}

/*----------------------------------------
����¶ȣ�
------------------------------------------*/
unsigned int get_temperature1()
{
  float wendu1;
  unsigned char a,b;
  ds1_reset();
  delay(1);              //Լ2ms
  ds1_write_byte(0xcc);
  ds1_write_byte(0xbe);
  a=ds1_read_byte();
  b=ds1_read_byte();
  temp1=b;
  temp1<<=8;
  temp1=temp1|a;
  wendu1=temp1*0.0625;     
  temp1=wendu1*10+0.5;
  return temp1;
}

/*��ROM   */
void wendu1()
{
   unsigned int a;
   init_com();
   init();
  // while(1)
   {

     tem_change1();          //12λת��ʱ�����Ϊ750ms
		for(a=10;a>0;a--)
			{
			    display1( get_temperature1());
			}
	}
}










