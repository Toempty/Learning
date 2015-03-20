#include<reg51.h>
sbit  p1_1=P1^0;
unsigned int a;
void main()
{
	while(1)
		{
	        a=9000;
			p1_1=0;
			while(a--);
			a=9000;
			p1_1=1;
			while(a--);
}
}
