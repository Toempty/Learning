#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit ds=P3^5;
sbit lcdwr=P2^2;
sbit lcdrs=P2^0;
sbit lcde=P2^1;

uchar flag,i;
long uint temp,biaozhi;  //参数temp一定要声明为 int 型 
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

/*延时函数*/
void TempDelay (uchar us)  //经验表明，这里us=1时约等于6.9us 
{
   while(us--);
}



/*串口初始化，波特率9600，方式1 */
void init_com()
{
   TMOD=0x20;      //设置定时器1为模式2
   TH1=0xfd;       //装初值设定波特率
   TL1=0xfd;
   TR1=1;          //启动定时器
   SM0=0;          //串口通信模式设置
   SM1=1;
   PCON=0;         //波特率不倍频
}

/*数码管的显示 */
void display(uint temp)
{    
    uchar bai,shi,ge;
	write_com(0x80+2);//决定了在显示屏上的显示位置
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
    	
        write_data(table[bai]);//显示十位
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
   TempDelay(80); //当总线停留在低电平超过480us，总线上所以器件都将被复位，这里
                 //延时约530us总线停留在低电平超过480μs，总线上的所有器件都将被复位。
   _nop_(); 
   ds=1;           //产生复位脉冲后，微处理器释放总线,让总线处于空闲状态
   TempDelay(5); //释放总线后，以便从机18b20通过拉低总线来指示其是否在线,
                  //存在检测高电平时间：15~60us， 所以延时44us，进行1-wire presence //detect（单线存在检测）
   _nop_();
   _nop_();
   _nop_();

   if(ds==0)
        flag=1;       //detect 18b20 success
   else
        flag=0;       //detect 18b20 fail


TempDelay(20);    //存在检测低电平时间：60~240us，所以延时约140us
   _nop_();
   _nop_();
   ds=1;          //再次拉高总线，让总线处于空闲状态
}
/*----------------------------------------
读/写时间隙:
DS1820 的数据读写是通过时间隙处理位和命令字来确认信息交换。
------------------------------------------*/
bit ds_read_bit(void)    //读一位
{
   bit dat;
   ds=0;            //单片机将总线拉低

   _nop_();         //读时隙起始于微处理器将总线拉低至少1us
   ds=1;            //拉低总线后接着释放总线，让从机18b20能够接管总线，输出有效数据
	_nop_();
   _nop_();         //小延时一下，读取18b20上的数据 ,因为从ds18b20上输出的数据
                    //在读"时间隙"下降沿出现15us内有效

   dat=ds;          //主机读从机18b20输出的数据，这些数据在读时隙的下降沿出现//15us内有效 
	 TempDelay(10);    //所有读"时间隙"必须60~120us，这里77us
   return(dat);       //返回有效数据
}

/*读一字节*/
uchar ds_read_byte(  ) 
{

	uchar value,i,j;
	value=0;             //一定别忘了给初值
	for(i=0;i<8;i++)
		{
		    j=ds_read_bit();
		     value=(j<<7)|(value>>1);   
		}
	return(value);        //返回一个字节的数据
}

/*写一个字节*/
void ds_write_byte(uchar dat) 
{
	  uchar i;
	  bit onebit;        //一定不要忘了，onebit是一位

	  for(i=1;i<=8;i++) 
	  {
		    onebit=dat&0x01;
		    dat=dat>>1;

			if(onebit)      //写 1
				{
					ds=0;
					_nop_();    
					      _nop_();      //看时序图，至少延时1us，才产生写"时间隙"  
					ds=1;       //写时间隙开始后的15μs内允许数据线拉到高电平
					     TempDelay(5);  //所有写时间隙必须最少持续60us
				}
			else         //写 0
				{
					ds=0;
					     TempDelay(8);    //主机要生成一个写0 时间隙，必须把数据线拉到低电平并保持至少60μs，这里64us
					ds=1;
					_nop_();
					_nop_();
				}
	  }
}


void tem_change()
{
  ds_reset(); 
  delay(2);              //约2ms
  ds_write_byte(0xcc);
  ds_write_byte(0x44);
}

/*----------------------------------------
获得温度：
------------------------------------------*/
uint get_temperature()
{
  float wendu;
  uchar a,b;
  ds_reset();
  delay(1);              //约2ms
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

/*读ROM   */
void wendu()
{
   uint a;
   init_com();
   init();
//   while(1)
   {

     tem_change();          //12位转换时间最大为750ms
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

void init()//液晶初始化
{
	lcdwr=0;//写指令，写数据R/W均为低电平
	lcdrs=0;//写指令，RS为低电平
	lcde=0;
	write_com(0x38);//显示初始化设置
	write_com(0x0e);//显示开关及光标设置
	write_com(0x01);//清屏和数据指针
	write_com(0x80+8);//初始数据指针
}

void write_com(uchar com)//液晶写命令
{
	lcdrs=0;//写指令时RS需置低电平
	P0=com;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}

void write_data(uchar da)//液晶写数据
{
	lcdrs=1;//写数据时RS需置高电平
	P0=da;//DB0-DB7
	delay(5);
	lcde=1;//高脉冲，写数据
	delay(5);
	lcde=0;
}



