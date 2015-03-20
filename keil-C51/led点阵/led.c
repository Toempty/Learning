
#include <REG52.H>
#define uint unsigned int

unsigned char code taba[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
unsigned char code tabb[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
}

void main(void)
{
	unsigned char i,j;

while(1)
	{
			for(j=0;j<3;j++)//¡¡´Ó×óÍùÓÒÂÌ
			{
				for(i=0;i<8;i++)
					{
					P2=taba[i];
					P0=0xff;
					delay(200);
					}
					P2=0xff;//¹Ø±ÕµÆ
			}
		
			for(j=0;j<3;j++)//¡¡¡¡´ÓÓÒÍù×óºì
				{
					for(i=0;i<8;i++)
					{
					P1=taba[7-i];
					P0=0xff;
					delay(200);
					}
					P1=0xff;//¹Ø±ÕµÆ
				}
		
			for(j=0;j<3;j++)//¡¡´ÓÉÏÍùÏÂÂÌ
				{
					for(i=0;i<8;i++)
						{
						P2=0x00;
						P0=tabb[7-i];
						
						delay(200);
						}
						P0=0x00;
				}
		
			for(j=0;j<3;j++)//¡¡´ÓÏÂÍùÉÏºì
			{
				for(i=0;i<8;i++)
					{
					P1=0x00;
					P0=tabb[i];
					
					delay(200);
					}
					P1=0xff;
					P0=0xff;	
			}
		}
}
