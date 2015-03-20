#include <reg52.h>
sbit buzz=P0^3;
void delay(unsigned int);
void main()
{
	while(1)
	{
		buzz=1;
		delay(100);
		buzz=0;
		delay(100);
	}
}
void delay(unsigned int z)
{
	unsigned int x,y;
		for(x=z;x>0;x--)
			for(y=124;y>0;y--);
}

