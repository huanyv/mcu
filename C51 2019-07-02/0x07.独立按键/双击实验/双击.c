u8 click_N_Double (u8 time)
{
	static u8 flag_key,count_key,double_key;
	static u16 count_single,Forever_count;
	if(KEY2==0) Forever_count++; //长按标志位未置1
	else Forever_count=0;
	if(0==KEY2&&0==flag_key) flag_key=1;
	if(0==count_key)
	{
		if(flag_key==1)//单击一次进去一次
		{
			double_key++;
			count_key=1;
		}
		if(double_key==2)//判断双击
		{
			double_key=0;
			count_single=0;
			return 2;//双击执行的指令
		}
	}
	if(1==KEY2) flag_key=0,count_key=0;
	if(1==double_key)
	{
		count_single++;
		if(count_single>time&&Forever_count<time)
		{
			//中间间隔时间太长 判断为的单击
			double_key=0;
			count_single=0;
			return 1;//单击执行的指令
		}
		if(Forever_count>time)
		{
			//长按不放
			double_key=0;
			count_single=0;
		}
	}
	return 0;
}
