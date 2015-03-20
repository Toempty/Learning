#include<reg52.h>
#define uint unsigned int
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=124;y>0;y--);
}
void main()
{
	P0=0xc0;
	delay(1000);
	P0=0x06;

	while(1);
}
/*0x3f  , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d ,
   0	  1	      2	  3        4         5
 0x7d , 0x07 , 0x7f  , 0x6f , 0x77 , 0x7c ,
   6	  7	      8	  9        A        B
 0x39 , 0x5e , 0x79 , 0x71 , 0x00
   C        D        E         F	     Œﬁœ‘ æ
*/

