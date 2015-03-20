#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

sbit SCL=P2^1;//ʱ������
sbit SDA=P2^0;//˫������������ݶ�

#define AddWr 0x90   //д���ݵ�ַ
#define AddRd 0x91   //�����ݵ�ַ
#define adCon 0x40   //AD�����ֽ�

sbit RS=P2^4;
sbit RW=P2^5;
sbit E=P2^6;

uint time=0;
uchar ADFlag=0;
uchar str[8]="Ci n.mv ";

//��ʱ1US
void delay(uint cnt)
{
 while(--cnt);
}
//��ʱ1MS
void delayms(uint time)
{
 uint i;
 for(i=0; i<time; i++)
  delay(120);
}
//д���ݣ�P0
void writeData(uchar Data)
{
  RS=1;
  RW=0;
  delay(1);
  E=1;
  delay(1);
  P0=Data;
  delay(5);
  E=0;
}
//д���P0
void writeCom(uchar Com)
{
  RS=0;
  RW=0;
  delay(1);
  E=1;
  delay(1);
  P0=Com;
  delay(5);
  E=0;
}
//��������
 void clear_scr(void)
 {
   writeCom(0x01);
   delayms(5);
  }

//дһ���ַ����ڣ�X,Y ��λ��
void disStr(uchar x, uchar y, uchar *str)
{
 if(y==0) writeCom(0x80+x);//��һ��
 else writeCom(0xc0+x);//�ڶ���
 while(*str)
 {
  writeData(*str);
  str++; 
 } 
}
//LCD1602��ʼ��
void lcdInitial()
{
   writeCom(0x38);//��ʾģʽ����
   delayms(5); 
   writeCom(0x08);//��ʾ�ر�
   clear_scr();//����
   writeCom(0x06); //��ʾ����ƶ�����
   delayms(5);
   writeCom(0x0C); //��ʾ����������� 
}


void start()
{
 SDA=1;
 delay(1);
 SCL=1;
 delay(5);
 SDA=0;
}


void stop()
{
 SDA=0;
 delay(1);
 SCL=1;
 delay(5);
 SDA=1;  
}


void ack()
{
 SDA=0;
 SCL=1;
 delay(1);
 SCL=0;
}


void noAck()
{
    SDA=1;
 SCL=1;
 delay(1);
 SCL=0;
}


void send(uchar Data)
{
 uchar i=0;
 uchar temp=0;

temp=Data;
 for(i=0; i<8; i++)
 {
  SCL=0;
  delay(1);
  if(temp&0x80) SDA=1;
  else SDA=0;
  delay(1);
  SCL=1;
  delay(1);
  temp<<=1;
 }
   SCL=0;
}


uchar recive()
{
 uchar i=0;
 uchar temp=0;

SDA=1;//��������
 for(i=0; i<8; i++)
 {
  SCL=0;//�����������ݸı�
  delay(1);
  SCL=1;//���߱������ݣ��ȴ�����
  delay(2);
  if(SDA) temp|=0x01;
  else temp&=0xfe; 
  if(i<7)   temp<<=1;//���λ������ɲ�����λ���������
 }
    SCL=0;
 return temp;
}


uchar read(uchar ch )
{
 uchar temp=0;

start();
 send(AddWr);//ȷ��оƬ
 ack();
 send(adCon|ch);//ȷ��ͨ��
 ack();
 //�������ݣ��Ž�temp
 start();
 send(AddRd);
 ack();
 temp=recive();
 noAck();
 stop();
 return temp;
}

uchar DAC(uchar light)
{
 start();
 send(AddWr);
 ack();
 send(0x40);  //д�����λ��ʹ��DAC���
 ack();
 send(light);
 ack();
 stop();
return light;}



void dis(uchar *date)
{

uchar i=0;
 uchar ch1,ch2,ch3  ;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 1, ch2, ch3;

for(i=0; i<4; i++)
 {
  ch1=i+48;
  str[1]=ch1;
  ch2=date[i]/50+48;
  str[3]=ch2;
  ch3=date[i]%50/10+48;
  str[5]=ch3;
  if(i>1) disStr(i*8-16, 1, str);
  else disStr(i*8, 0, str); 
 }
}


void interrupt_init()
{
 ET0=1;//��ʱ��0����ж�����
 TR0=1;//������ʱ��0
 TMOD=0X01;
 TH0=0Xd8;
 TL0=0Xf0;  
 EA=1;//�����ж�
}



void main()
{
 uchar i=0;
 uchar vot[4];

interrupt_init();
 lcdInitial();

//DAC(0);
 while(1)
 {
    if(ADFlag==1)
    {
       for(i=0; i<4; i++) vot[i]=read(i);
    DAC(200);//DAת��������0-255����
  }
    dis(vot);
 }
}

void tim0_() interrupt 1 using 1
{
   TH0=0xd8;  //���¸�ֵ
   TL0=0xf0;

time++;
   if(time==100)
      {  time=0;
      ADFlag=1;
    } //��ʱ��λAD������־λ
}
