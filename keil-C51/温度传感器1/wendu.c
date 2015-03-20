#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

#define nop() _nop_();//�����ָ�������intrins.h��

sbit    LS138A=P2^2;       //�ܽŶ���
sbit    LS138B=P2^3;
sbit    LS138C=P2^4; 
sbit    D0=P3^7;

uchar code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};

uchar code CrcTable [256]={
0,  94, 188,  226,  97,  63,  221,  131,  194,  156,  126,  32,  163,  253,  31,  65,
157,  195,  33,  127,  252,  162,  64,  30,  95,  1,  227,  189,  62,  96,  130,  220,
35,  125,  159,  193,  66,  28,  254,  160,  225,  191,  93,  3,  128,  222,  60,  98,
190,  224,  2,  92,  223,  129,  99,  61,  124,  34,  192,  158,  29,  67,  161,  255,
70,  24,  250,  164,  39,  121,  155,  197,  132,  218,  56,  102,  229,  187,  89,  7,
219,  133, 103,  57,  186,  228,  6,  88,  25,  71,  165,  251,  120,  38,  196,  154,
101,  59, 217,  135,  4,  90,  184,  230,  167,  249,  27,  69,  198,  152,  122,  36,
248,  166, 68,  26,  153,  199,  37,  123,  58,  100,  134,  216,  91,  5,  231,  185,
140,  210, 48,  110,  237,  179,  81,  15,  78,  16,  242,  172,  47,  113,  147,  205,
17,  79,  173,  243,  112,  46,  204,  146,  211,  141,  111,  49,  178,  236,  14,  80,
175,  241, 19,  77,  206,  144,  114,  44,  109,  51,  209,  143,  12,  82,  176,  238,
50,  108,  142,  208,  83,  13,  239,  177,  240,  174,  76,  18,  145,  207,  45,  115,
202,  148, 118,  40,  171,  245,  23,  73,  8,  86,  180,  234,  105,  55,  213, 139,
87,  9,  235,  181,  54,  104,  138,  212,  149,  203,  41,  119,  244,  170,  72,  22,
233,  183,  85,  11,  136,  214,  52,  106,  43,  117,  151,  201,  74,  20,  246,  168,
116,  42,  200,  150,  21,  75,  169,  247,  182,  232,  10,  84,  215,  137,  107,  53};
uint  display[5],num,num1,Temperature;
uchar flag,*p,id[8],temp[9];

void delay(uchar);
void delay1(uint);
void time0_init();
void GetTemp();
void init1820 ();
void write_byte (uchar);
void read_byte (uchar);
void read_bytes (uchar);
uchar CRC (uchar);
void TemperatuerResult();
void GemTemp ();
void Config1820 ();

void wendu()
{
	uint i;
	time0_init();

    while(1)
   {	
	  GetTemp();

       num1=Temperature;      //��ʵ���¶��͵�num1������ 
	  display[0]=table[num1%10000/1000];
      display[1]=table[num1%1000/100];
      display[2]=table[num1%100/10];	 //ʮλ
      display[3]=table[num1%10];    //��λ

  	  
    for(i=0; i<5; i++) 
	  {		
		 P0 = display[i] ;
	  			 	 	  	
		switch(i)					  
         {	    	  //138����
			case 0:LS138A=0; LS138B=0; LS138C=0; break;         
            case 1:LS138A=1; LS138B=0; LS138C=0; break;             	
            case 2:LS138A=0; LS138B=1; LS138C=0; break; 
            case 3:LS138A=1; LS138B=1; LS138C=0; break; 
         }
		 
		delay1(1);
	  }

	  P0 = 0;  
  
    }
}

void delay(uchar z)//��ʱ9*z΢��
{
	while(z--);
}

void delay1(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
}

void timer0 () interrupt 1
{
	TH0= (65536-50000)/256;    
    TL0= (65536-50000)%256;	
	num++;
}

void time0_init()
{

    TMOD=0x01;
	EA=1;
    TH0= (65536-50000)/256;    
    TL0= (65536-50000)%256;	
	ET0=1;
    TR0=1;//�򿪶�ʱ��1
}

void init1820 ()//DS1820�ĳ�ʼ��
{
	D0=1;//P3^7  I/O��
	_nop_();
	D0=0;
	delay(60);   //delay 540 uS  12Mhzÿ��ָ��9us��11.0592Mhzÿ��ָ��10us
	_nop_();
	D0=1;
	delay(10);   //delay 100 uS
	_nop_();
	_nop_();
	_nop_();
	
	if(D0==0)
		flag = 1;   //detect�����֣�ʶ�� 1820 success!
	else
		flag = 0;    //detect 1820 fail!
	delay(17);       
	_nop_();
	_nop_();
	D0 = 1;
}

void write_byte (uchar  wr)  //���ֽ�д��
{
	uchar i;
	for (i=0;i<8;i++)
	{
		D0 = 0;
		_nop_();
		D0=wr&0x01;
		delay(5);   //delay 45 uS //5
		_nop_();
		_nop_();
		D0=1;
		wr >>= 1;
	}
}

uchar read_byte ()     //��ȡ���ֽ�//****ע��*****
{
	uchar i,u=0;
	for(i=0;i<8;i++)
	{
		D0 = 0;
		u >>= 1;
		D0 = 1;//�ͷ�����
		if(D0==1)
		u |= 0x80;
		delay(2);
		_nop_();
	}
	return(u);
}

void read_bytes (uchar j)
{
	 uchar i;
	 for(i=0;i<j;i++)
	 {
		  *p = read_byte();
		  p++;
	 }
}

uchar CRC (uchar j)//CRCУ��
{
   	uchar i,crc_data=0;
  	for(i=0;i<j;i++)  //���У��
    	crc_data = CrcTable[crc_data^temp[i]];
    return (crc_data);
}

void GemTemp ()
{
   read_bytes (9);
   if (CRC(9)==0) //У����ȷ
   {
	    Temperature = temp[1]*0x100 + temp[0];
		Temperature /= 16;
		delay(1);
    }
}

/************************************************************
*Function:�ڲ�����
*parameter:
*Return:
*Modify:
*************************************************************/
void Config1820 ()  //�������ñ����޶�ֵ�ͷֱ���
{
     init1820();
     write_byte(0xcc);  //cc skip rom cmomand
     write_byte(0x4e);  //write scratchpad�ccommand ���м����ݴ�����
     write_byte(0x19);  //����
     write_byte(0x1a);  //����
     write_byte(0x7f);     //set 11 bit (0.125)
     init1820();
     write_byte(0xcc);  //skip rom
     write_byte(0x48);  //�����趨ֵ 48 copy scratchpad command����������ȴ�10ms
     init1820();
     write_byte(0xcc);  //skip rom
     write_byte(0xb8);  //�ص��趨ֵ b8 read scratchpad command
}

/************************************************************
*Function:��18B20ID
*parameter:
*Return:
*Modify:
*************************************************************/
void ReadID ()//��ȡ���� id
{
	init1820();
	write_byte(0x33);  //read rom command
	read_bytes(8);
}

/************************************************************
*Function:18B20IDȫ����
*parameter:
*Return:
*Modify:
*************************************************************/
void TemperatuerResult()
{
  	p = id;
  	ReadID();
  	Config1820();
	init1820 ();
	write_byte(0xcc);   //skip rom
	write_byte(0x44);   //Temperature convert��issue �C��convert T��command

	init1820 ();
	write_byte(0xcc);   //skip rom
	write_byte(0xbe);   //read Temperature
	p = temp;
	GemTemp();
}


void GetTemp()
{       
     if(num==20) //ÿ�� 1000ms ��ȡ�¶�
	{  num=0;
	   TemperatuerResult();
	}

}

