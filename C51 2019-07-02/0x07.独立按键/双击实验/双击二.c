﻿uchar readkey()
{
	static uchar keystate=0;
	static uchar keycount=0;
	static uint keytime=0;
	uchar key_return=0;
	switch(keystate)
	{
		case 0:
			if(k1==1)//没有按下
			{
				key_return=0;
			}
			else//按下
			{
				keystate=1;
				keytime=0;
			}break;		
		case 1:
			if(k1==1)
			{
				keytime++;
				if(keytime<=1000)
				{
					keycount++;
				}
				else
				{
					keystate=2;
				}
			}
			else
			{
				keystate=0;
			}break;
		case 2:
			if(k1==0)
			{
				if(keycount==1)
				{
					key_return=1;
					keystate=3
				}
				if(keycount==2)
				{
					key_return=11;
					keystate=3
				}
			}
		case 3:
			if(k1==1)
			{
				keystate=0;
			}break;
	}
	return key_return;
}


































