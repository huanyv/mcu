u8 click_N_Double (u8 time)
{
	static u8 flag_key,count_key,double_key;
	static u16 count_single,Forever_count;
	if(KEY2==0) Forever_count++; //������־λδ��1
	else Forever_count=0;
	if(0==KEY2&&0==flag_key) flag_key=1;
	if(0==count_key)
	{
		if(flag_key==1)//����һ�ν�ȥһ��
		{
			double_key++;
			count_key=1;
		}
		if(double_key==2)//�ж�˫��
		{
			double_key=0;
			count_single=0;
			return 2;//˫��ִ�е�ָ��
		}
	}
	if(1==KEY2) flag_key=0,count_key=0;
	if(1==double_key)
	{
		count_single++;
		if(count_single>time&&Forever_count<time)
		{
			//�м���ʱ��̫�� �ж�Ϊ�ĵ���
			double_key=0;
			count_single=0;
			return 1;//����ִ�е�ָ��
		}
		if(Forever_count>time)
		{
			//��������
			double_key=0;
			count_single=0;
		}
	}
	return 0;
}
