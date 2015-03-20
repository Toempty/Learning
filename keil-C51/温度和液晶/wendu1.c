#include <reg52.h>
#include <intrins.h>

sbit ds1=P3^4;
unsigned char flag1;
unsigned long  int temp1,biaozhi1;  //参数temp一定要声明为 int 型 
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


/*数码管的显示 */
void display1(unsigned int temp1)
{    
    unsigned char bai,shi,ge;
	write_com(0x80+0x40);//决定了在显示屏上的显示位置
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

void ds1_reset(void)
{
   ds1=1;
   _nop_();        //1us
   ds1=0;
   TempDelay(80); //当总线停留在低电平超过480us，总线上所以器件都将被复位，这里
                 //延时约530us总线停留在低电平超过480μs，总线上的所有器件都将被复位。
   _nop_(); 
   ds1=1;           //产生复位脉冲后，微处理器释放总线,让总线处于空闲状态
   TempDelay(5); //释放总线后，以便从机18b20通过拉低总线来指示其是否在线,
                  //存在检测高电平时间：15~60us， 所以延时44us，进行1-wire presence //detect（单线存在检测）
   _nop_();
   _nop_();
   _nop_();

   if(ds1==0)
        flag1=1;       //detect 18b20 success
   else
        flag1=0;       //detect 18b20 fail


TempDelay(20);    //存在检测低电平时间：60~240us，所以延时约140us
   _nop_();
   _nop_();
   ds1=1;          //再次拉高总线，让总线处于空闲状态
}
/*----------------------------------------
读/写时间隙:
DS1820 的数据读写是通过时间隙处理位和命令字来确认信息交换。
------------------------------------------*/
bit ds1_read_bit(void)    //读一位
{
   bit dat1;
   ds1=0;            //单片机将总线拉低

   _nop_();         //读时隙起始于微处理器将总线拉低至少1us
   ds1=1;            //拉低总线后接着释放总线，让从机18b20能够接管总线，输出有效数据
	_nop_();
   _nop_();         //小延时一下，读取18b20上的数据 ,因为从ds18b20上输出的数据
                    //在读"时间隙"下降沿出现15us内有效

   dat1=ds1;          //主机读从机18b20输出的数据，这些数据在读时隙的下降沿出现//15us内有效 
	 TempDelay(10);    //所有读"时间隙"必须60~120us，这里77us
   return(dat1);       //返回有效数据
}

/*读一字节*/
unsigned char ds1_read_byte(  ) 
{

	unsigned char value,i,j;
	value=0;             //一定别忘了给初值
	for(i=0;i<8;i++)
		{
		    j=ds1_read_bit();
		     value=(j<<7)|(value>>1);   
		}
	return(value);        //返回一个字节的数据
}

/*写一个字节*/
void ds1_write_byte(unsigned char dat1) 
{
	  unsigned char i;
	  bit onebit;        //一定不要忘了，onebit是一位

	  for(i=1;i<=8;i++) 
	  {
		    onebit=dat1&0x01;
		    dat1=dat1>>1;

			if(onebit)      //写 1
				{
					ds1=0;
					_nop_();    
					      _nop_();      //看时序图，至少延时1us，才产生写"时间隙"  
					ds1=1;       //写时间隙开始后的15μs内允许数据线拉到高电平
					     TempDelay(5);  //所有写时间隙必须最少持续60us
				}
			else         //写 0
				{
					ds1=0;
					     TempDelay(8);    //主机要生成一个写0 时间隙，必须把数据线拉到低电平并保持至少60μs，这里64us
					ds1=1;
					_nop_();
					_nop_();
				}
	  }
}


void tem_change1()
{
  ds1_reset(); 
  delay(2);              //约2ms
  ds1_write_byte(0xcc);
  ds1_write_byte(0x44);
}

/*----------------------------------------
获得温度：
------------------------------------------*/
unsigned int get_temperature1()
{
  float wendu1;
  unsigned char a,b;
  ds1_reset();
  delay(1);              //约2ms
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

/*读ROM   */
void wendu1()
{
   unsigned int a;
   init_com();
   init();
  // while(1)
   {

     tem_change1();          //12位转换时间最大为750ms
		for(a=10;a>0;a--)
			{
			    display1( get_temperature1());
			}
	}
}










