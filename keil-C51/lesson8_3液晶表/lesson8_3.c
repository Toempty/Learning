#include <reg52.h>
#define uchar unsigned char
#define uint unsigned  int
uchar i;
uchar  code table[]="0123456789";//��д���ַ�����ʽ�����������
uint shi1,shi2,fen1,fen2,miao1,miao2,num,numshi,numfen,nummiao;
sbit lcdwr=P2^5;
sbit lcdrs=P2^6;
sbit lcde=P2^7;
void delay(uint z);
void init();
void write_com(uchar com);
void write_data(uchar da);
void main()
{
	init();
	write_com(0x80+0x05);
	write_com(0x0f);
	while(1)
	{		
	
		write_com(0x80+0x05);//���ó�ʼ��ַ
				shi1=numshi/10;
				shi2=numshi%10;
				fen1=numfen/10;
				fen2=numfen%10;
				miao1=nummiao/10;
				miao2=nummiao%10;

				write_data(table[shi1]);
				delay(0);
				write_data(table[shi2]);
				write_data(':');
				delay(0);

				write_data(table[fen1]);
				delay(0);
				write_data(table[fen2]);
				write_data(':');
				delay(0);

				write_data(table[miao1]);
				delay(0);
				write_data(table[miao2]);
				delay(0);
			
	}

}
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void init()
{	
	TMOD=0x01;//��TMOD��ֵ����ȷ��T0��T1�Ĺ�����ʽ
	TH0=(65536-50000)/256;//����ֵ
	TL0=(65536-50000)%256;
	EA=1;//�����ж�
	ET0=1;//����ʱ�ж�0
	TR0=1;//������ʱ��
	lcdwr=0;//дָ�д����R/W��Ϊ�͵�ƽ
	lcdrs=0;//дָ�RSΪ�͵�ƽ
	lcde=0;
	write_com(0x38);//��ʾ��ʼ������
	write_com(0x0c);//��ʾ���ؼ��������
	write_com(0x01);//����������ָ��
	write_com(0x80+0x10);//��ʼ����ָ��
}
void write_com(uchar com)
{
	lcdrs=0;//дָ��ʱRS���õ͵�ƽ
	P0=com;//DB0-DB7
	delay(4);
	lcde=1;//�����壬д����
	delay(4);
	lcde=0;
}
void write_data(uchar da)
{
	lcdrs=1;//д����ʱRS���øߵ�ƽ
	P0=da;//DB0-DB7
	delay(4);
	lcde=1;//�����壬д����
	delay(4);
	lcde=0;
}
void timer0 ()interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
	if(num%20==0)
		{
			nummiao++;//����
			num=0;
			if(nummiao%60==0)
					{
						numfen++;//����
						nummiao=0;
						 if(numfen%60==0)
							{
								numshi++;//ʱ��
								numfen=0;
								if(numshi==24)
									{
										numshi=0;
									}
							}
					}
		}

}
