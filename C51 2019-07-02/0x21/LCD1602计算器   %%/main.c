#include<reg52.h>
#include<lcd1602.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>

#define duli P1

uchar weizhi;

uchar code zifu[]="123+456-789* 0=/";
char str[20];

int n=0,i1=0;
float num=100.55;
char record[20];
float product();
float change();
float muli()
{
	float summ;
	summ=product();
	while(record[n]=='-'||record[n]=='+')
	{
		switch(record[n])
		{
		case '+':n++;summ+=product();break;
		case '-':n++;summ-=product();break;
		}
	}
	return summ;
}
float product()
{
	float sump;
	sump=change();
	while(record[n]=='*'||record[n]=='/')
	{
		switch(record[n])
		{
		case '*':n++;sump*=change();break;
		case '/':n++;sump/=change();break;
		}
	}
	return sump;
}
float change()
{
	float sumc;
	char rec[20],i=0;
	if(record[n]=='(')
	{
		n++;
		sumc=muli();
	}
	if(record[n]==')')
		n++;
	while(isdigit(record[n])||record[n]=='.')
	{
		while(isdigit(record[n])||record[n]=='.')
			rec[i++]=record[n++];
		rec[i]='\0';
		sumc=atof(rec);
	}
	return sumc; 
}

void saomiao()
{
	 uint a=0;
	 duli=0x0f;
	 if(duli!=0x0f)
	 {
	 	delay(200);
		switch(duli)
		{
			case 0x07:weizhi=1;break;
			case 0x0b:weizhi=2;break;
			case 0x0d:weizhi=3;break;
			case 0x0e:weizhi=4;break;	
		}
		duli=0xf0;
		switch(duli)
		{
			case 0x70:break;
			case 0xb0:weizhi=weizhi+4;break;
			case 0xd0:weizhi=weizhi+8;break;
			case 0xe0:weizhi=weizhi+12;break;
		}
		if(weizhi!=13)
			i1++;
		else
			for(a=0;record[a]!='\0';a++)
			{
				record[a]=' ';i1=0;
			}
		while(duli!=0xf0);
	 }
}

void lcdfuzhi()
{
	record[i1-1]=zifu[weizhi-1];
	num=muli();
	if(weizhi==15)
	{
		sprintf(str,"%f",num); 
	//	itoa(muli(), str, 10);
	}
}

void display()
{
	uint i,j=0;
	for(i=0;record[i]!='\0';i++)
	{
		LCD_X_Y(1,j++,record[i]);
	}j=0;
	for(i=0;str[i]!='\0';i++)
	{
		LCD_X_Y(2,j++,str[i]);
	}
}

int main()
{
	LCD_init();
	while(1)
	{
		saomiao();
		lcdfuzhi();
		display();
	}
	return 0;
}