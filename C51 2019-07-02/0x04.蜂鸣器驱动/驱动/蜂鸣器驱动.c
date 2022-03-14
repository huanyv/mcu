#include<reg52.h>
typedef unsigned char uchar;
sbit feng=P1^5 ;
void yanshi(uchar i)
{
	while(i)
	{
		i--;
	}
}
int main()
{
	while(1)
	{
		feng=~feng;
		yanshi(10);
	}
}