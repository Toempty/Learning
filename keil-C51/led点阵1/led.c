#include <REG52.H>
#define uint unsigned int

unsigned char code table1[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
unsigned char code table2[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
}
void main()
{
	uint i,j;
	while(1)
		{
			for(i=3;i>0;i--)
				{
					for(j=0;j<8;j++)
						{
							P2=table1[j];
							P0=table2[7-j];
							delay(200);
						}
				}
			P2=0xff;
			for(i=3;i>0;i--)
				{
					for(j=0;j<8;j++)
						{
							P1=table1[7-j];
							P0=table2[j];
							delay(200);
						}
				}
			P1=0xff;
		}
}
