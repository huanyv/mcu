uchar readkey()
{
	static uchar keystate=0;
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
			if(k1==0)
			{
				keytime++;
				if(keytime>=500)//短按
				{
					keystate=2;
				}
			}
			else
			{
				keystate=0;
			}break;
		case 2:
			if(k1==1)
			{
				key_return=1;
				keystate=0;
			}
			else
			{
				keytime++;
				if(keytime>=5000)//长按
				{
					key_return=11;
					keystate=3;
				}
			}break;
		case 3:
			if(k1==1)
			{
				keystate=0;
			}break;
	}
	return key_return;
}


































