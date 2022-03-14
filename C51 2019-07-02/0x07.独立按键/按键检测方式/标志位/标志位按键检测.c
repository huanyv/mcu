void key()
{
	static bit flag1=0;
	static uchar flag2=0;
	if(k1==0&&flag2=0)
	{
		flag1++;//延时 消抖　标志位
		if(flag1>=300&&k1==0)//根据情况修改数值
		{
			flag1=0;
			flag2=1;//检测　松手　标志位
			
			
			//操作;
			
			
		}
	}
	if(k1==1)
	{
		flag1=0;
		flag2=0;
	}
}