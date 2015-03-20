#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table []="WHO ARE YOU?";
uchar code table1 []="I AM LICHAO!";
uchar code table2[]="AND YOU?    ";
uchar code table3[]="I AM123?    ";
uchar i;
sbit lcdwr=P0^5;
sbit lcdrs=P0^4;
sbit lcde=P0^6;
void delay(uchar z);
void init();
void flash();
void write_com(uchar com);
void write_data(uchar da);
void main()
{
	init();
	for(i=0;i<12;i++)
		{
				write_data(table[i]);//д����
				delay(50);					
	}
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(1000);
		 }
			
	write_com(0x80+0x40+0x10);//������������ָ�룬ʹ��ʼ�ڵڶ�����ʾ
	for(i=0;i<12;i++)
		{
				delay(50);
				write_data(table1[i]);//д����			
	}
    flash();//��˸
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(500);
		 }
		
		
		delay(1000);
		init();//��ʼ��
for(i=0;i<12;i++)
		{
				write_data(table2[i]);//д����
				delay(50);					
	}
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(1000);
		 }
			
	write_com(0x80+0x40+0x10);//������������ָ�룬ʹ��ʼ�ڵڶ�����ʾ
	for(i=0;i<12;i++)
		{
				delay(50);
				write_data(table3[i]);//д����			
	}
    flash();//��˸
	for (i=0;i<16;i++)	
		 {			
			write_com(0x18);
			delay(500);
		 }

	while(1);
}
void delay(uchar z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void init()
{
	lcdwr=0;//дָ�д����R/W��Ϊ�͵�ƽ
	lcdrs=0;//дָ�RSΪ�͵�ƽ
	lcde=0;
	write_com(0x38);//��ʾ��ʼ������
	write_com(0x0e);//��ʾ���ؼ��������
	write_com(0x01);//����������ָ��
	write_com(0x80+0x10);//��ʼ����ָ��
}
void write_com(uchar com)
{
	lcdrs=0;//дָ��ʱRS���õ͵�ƽ
	P2=com;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}
void write_data(uchar da)
{
	lcdrs=1;//д����ʱRS���øߵ�ƽ
	P2=da;//DB0-DB7
	delay(5);
	lcde=1;//�����壬д����
	delay(5);
	lcde=0;
}
void flash()    //��˸�ӳ���                                                           
{                                                                          
    delay(600);                     //����ͣ��ʱ��                         
    write_com(0x08);            //�ر���ʾ                                  
    delay(200);                    //��ʱ                                  
    write_com(0x0c);            //����ʾ                                    
    delay(200);                                                            
    write_com(0x08);            //�ر���ʾ                                  
    delay(200);                     //��ʱ                                 
    write_com(0x0c);            //����ʾ                                    
    delay(200);                                                            
}    