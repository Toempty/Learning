#define uchar unsigned char
#define uint unsigned int
sbit sda=P2^0;
sbit scl=P2^1;
void start();//开启
void stop();//停止
void delay();
void delay1(uint);
void init();//初始化
void respons();//应答函数
void write_byte(uchar date);
void write_add(uchar address,uchar date);
uchar read_byte();
uchar read_add(uchar address);