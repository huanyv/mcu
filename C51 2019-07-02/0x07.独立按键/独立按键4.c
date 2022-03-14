#include<reg52.h>
#include<intrins.h>

typedef unsigned char ucahr;
typedef unsigned int uint;

sbit led1=P2^0;
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

#define N 1000

#define LED P2

void yanshi(uint i)
{
	 uint x,y;
	 for(x=0;x<i;x++)
	 for(y=0;y<60;y++);
}

void guanbi()
{
	if(k4==0)
	{
		yanshi(20);
		if(k4==0)
		{
			while(1)
			{
				LED=0xff;
				if(k2==0||k3==0||k1==0)
				{
					LED=0xff;break;
				}
			}
		}
		while(!k4);
	}
}

void anjian_liushui()
{
	uint i=0;
	if(k3==0)
	{
		yanshi(20);
		if(k3==0)
		{
			LED=0xfe;
			yanshi(N);
			while(1)
			{
				for(i=0;i<7;i++)
				{
					LED=_crol_(LED,1);
					yanshi(N);
					if(k2==0||k1==0||k4==0)
					{
						LED=0xff;break;
					}
		 		}
				for(i=0;i<7;i++)
				{
					LED=_cror_(LED,1);
					yanshi(N);
					if(k2==0||k1==0||k4==0)
					{
						LED=0xff;break;
					}
		 		}
				if(k2==0||k1==0||k4==0)
				{
					LED=0xff;break;
				}
			}
		}
		while(!k3);
	}
}

void anjian_shanshuo()
{

	if(k2==0)
	{
		yanshi(20);
		if(k2==0)
		{
			while(1)
			{
				led1=~led1;
				yanshi(N);
				if(k1==0||k3==0||k4==0)
				{
					LED=0xff;break;
				}
			}
			while(!k2);
		}
	}
}

void anjian_liang()
{
	
	if(k1==0)
	{
		yanshi(20);
		if(k1==0);
		{
			while(1)
			{
				led1=0;
				if(k2==0||k3==0||k4==0)
				{
					LED=0xff;break;
				}
			}	
		}
		while(!k1);
	}
}

int main()
{
	while(1)
	{
		anjian_liang();
		anjian_shanshuo();
		anjian_liushui();
		guanbi();
	}
	return 0;
}
