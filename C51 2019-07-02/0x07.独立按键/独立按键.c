#include<reg52.h>
#include<intrins.h>
typedef unsigned char uchar;
typedef unsigned int uint;

sbit k1=P3^1;
#define led P2

void yanshi(uint x)
{
	uint i,j;						//  0.5ms
	for(i=0;i<=x;i++)
		for(j=0;j<=60;j++);
}

void anjian()
{
	
	if(k1==0)
	{	yanshi(20);
		if(k1==0)
		{
			led=_crol_(led,1);
		}
		while(!k1);
	}
}

int main()
{
	led=0xfe;
	while(1)
	{
	 	anjian();
	}
	return 0;
}