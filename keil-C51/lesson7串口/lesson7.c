#include<reg52.h>
unsigned char flag,a;
void main()
{
	TMOD=0x20;//设置定时器1为工作模式2
	TH1=0xfd;//晶振频率为11.0592， 定时器为方式2， 波特率为9600，SMOD=0时初值为0xfd
	TL1=0xfd;
	TR1=1;//打开定时器1（开始工作，有波特率）
	REN=1;//接收使能位，清0时关闭数据的接收
	SM0=0;
	SM1=1;//设置串口工作方式
//  SMOD=0;//初始值为0，可以省略此步
	EA=1;
	ES=1;//ES (IE.3) =1， 串行口中断允许位
	while(1)
	{
		if(flag==1)
		{
			ES=0;//关闭串口中断
			flag=0;
			SBUF=a;//把a中的值发送出去
			while(!TI)//等待发送完，发送完TI=1
			TI=0;//TI需要手动清0
			ES=1;			
		}
	}
}
void send () interrupt 4
{
	P1=SBUF;//接收的数据赋给P1
	a=SBUF;//接收的数据赋给a
	flag=1;//标志接收到数据
}
