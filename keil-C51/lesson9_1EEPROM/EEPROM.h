#define uchar unsigned char
#define uint unsigned int
sbit sda=P2^0;
sbit scl=P2^1;
void start();//����
void stop();//ֹͣ
void delay();
void delay1(uint);
void init();//��ʼ��
void respons();//Ӧ����
void write_byte(uchar date);
void write_add(uchar address,uchar date);
uchar read_byte();
uchar read_add(uchar address);