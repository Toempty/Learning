#include <reg52.h>
sbit buzz=P1^0;

extern wendu();
extern delay(uint);
extern wendu1();

void main()
{	
	buzz=0;
	while(1)
	{
		wendu();
		delay(10);
		wendu1();
		delay(10);
	}

}

