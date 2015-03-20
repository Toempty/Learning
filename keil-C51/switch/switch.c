#include <reg52.h>
#define uint unsigned char
uint i,j ,k,m;
void main()
{
	i=5;
	while(1)
	    {
			j++;
			k++;
			m++;
	
			switch(i)					  
			     {	    
					case 0:j=0; k=0; m=0; break;         
			        case 1:j=1; k=0; m=0; break;             	
			        case 2:j=0; k=1; m=0; break; 
			        case 3:j=1; k=1; m=0; break; 
					case 4:j=0; k=0; m=1; break;
					case 5:j=1; k=0; m=1; break;
					case 6:j=0; k=1; m=1; break;
					case 7:j=1; k=1; m=1; break;
				}		
		  }
}
