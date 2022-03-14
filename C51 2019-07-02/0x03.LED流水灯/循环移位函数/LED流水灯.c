#include<reg52.h>
#include "intrins.h" //intrins.h
typedef unsigned int uint;
#define led P2
void yanshi(uint x)		  //   x * 0.5ms  ×Óº¯Êý
{
	 int i,j;
	 for(i=0;i<x;i++)
		for(j=0;j<60;j++);
}
int main()
{

	uint i;
	led=0xfe;		  //1111  1110
	yanshi(2000);
	while(1)
	{	 
		for(i=0;i<7;i++)
		{
			led=_crol_(led,1);
			yanshi(2000);		 
		}
	  	for(i=0;i<7;i++)
		{
			led=_cror_(led,1);
			yanshi(2000);	
		}
	}
	return 0;
}