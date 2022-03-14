 #include<reg52.h>
 typedef unsigned int uint;
 sbit LED=P2^0;
 void yanshi(uint i)
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
		LED=0;
		yanshi(100000);
		LED=1;
		yanshi(100000);
	}
 } 