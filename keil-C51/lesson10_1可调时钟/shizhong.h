
#define uchar unsigned char
#define uint unsigned int

uchar code table[]="2011.7.31 SUN";
uchar code table1[]="   00:00:00";
uchar code table2[]="0123456789";

sbit wr=P2^5;
sbit rs=P2^6;
sbit lcde=P2^7;
sbit key1=P3^0;//�����������
sbit key2=P3^1;
sbit key3=P3^2;
sbit key4=P3^3;
sbit key5=P3^4;
sbit key6=P3^5;
sbit key7=P3^6;
sbit key8=P3^7;

void delay(uint);
void write_com(uchar);//дָ��
void write_data(uchar);//д����
void init();//��ʼ��
void setclock();//����ʱ��
void write_sfm(uchar,uchar,uchar);//дʱ����
uchar keyscan();//������̼��

uint num,shi,shi1,shi2,fen,fen1,fen2,miao,miao1,miao2,m,n;
uchar i,temp;
uchar key11,key22,key33;//��¼key1��key2��key3���´���