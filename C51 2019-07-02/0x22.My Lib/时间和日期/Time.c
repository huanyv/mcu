#include<time.h>

void delay(uint i)
{
	while(i--);
}


uint leapyear()/************�Ƿ�����************/
{
	 if((year%4==0&&year%100!=0)||(year%400==0))
	 	return 1;
	 else
	 	return 0;
}


uint datnumber()/************�ж�����************/
{
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
		return 31;
	else if(month==4||month==6||month==9||month==11)
		return 30;
	else 
	{
		if(leapyear()==1)
			return 29;
		else
			return 28;
	} 	
}


void time()            //ʱ����ʾ 
{
	if(seconds<59)				   //��䶯
		seconds++;

	else
	{
		seconds=0;
		if(minute<59)			  //���ӽ�λ
			minute++;
		else
		{
			minute=0;
			if(hour<23)			   //Сʱ��λ
				hour++;
			else
				hour=0;
		}
	}
}


void time&date()//ʱ���������ʾ
{
	if(seconds<59)				   //��䶯
		seconds++;
	else
	{
		seconds=0;
		if(minute<59)			  //���ӽ�λ
			minute++;
		else
		{
			minute=0;
			if(hour<23)	
			{		   //Сʱ��λ
				hour++;
			}
			else
			{
				hour=0;
				if(dat<datnumber())
					dat++;
				else
				{
					dat=1;
					if(month<12)
						month++;
					else
					{
						month=1;
						if(year<100)
							year++;
						else
						{
							year=0;
							year_h++;
						}
					}
				}
			}
		}
	}
}



void datekongzhi()/**************���ڿ���***************/
{
	if(k3==0)
	{
		delay(2000);
		if(k3==0)
		{
			dat++;
			if(dat==datnumber()+1)dat=1; 
			while(!k3);
		}
	}
	if(k2==0)
	{
		delay(2000);
		if(k2==0)
		{
			month++;
			if(month==13)month=1; 
			while(!k2);
		}
	}
	if(k1==0)
	{
		delay(2000);
		if(k1==0)
		{
			year++;
			if(year==100)
			{
				year=0;
				year_h++;
				if(year_h==100)
				year_h=20;
			} 
			while(!k1);
		}
	}
}

void timekongzhi()//ʱ�����
{
	if(k3==0)
	{
		delay(2000);
		seconds++;
		if(seconds==60)seconds=0; 
		while(!k3);
	}
	if(k2==0)
	{
		delay(2000);
		minute++;
		if(minute==60)minute=0; 
		while(!k2);
	}
	if(k1==0)
	{
		delay(2000);
		hour++;
		if(hour==24)hour=0; 
		while(!k1);
	}
}