///////////////////////定时器溢出中断用于定时查键 大约10毫秒中断一次
keyscan_t=0;       //////这个全局变量是个定时器标志，定时中断置1，外部清0
ISR(TIMER0_OVF_vect)
{
	TCNT0=216;         ////程序启动后设TCCR0=0X04;256分频，每(256-216)*256微秒中断一次
	keyscan_t=1;       ////定时时间到标志置1
	PORTD=dispdata; ////其它刷新显示功能和按键处理无关
}

//////////////////////////////////// 读键函数keystate

	////////////////////////////////////
uchar readkey(void)//多个
{
	uchar keyval=0;  //////keyvai是最终键码，4个按键分别对应的键码是0x0e,0x0d,0x0b,0x07
	uchar newkey;      ////////newkey是当前键码，需要和上次键码比较
	static uchar keystate=0; ////状态值，起始为0，注意它是静态变量赋值后就保持到改写为止
	uchar keyOK;        /////////确认按键
	static uchar lastkey; /////lastkey记录上次检查时的键码，也是静态变量
	newkey=PINC&0X0F; /////键码就是PC口低4位取值每次都要读取
	switch(keystate)        //////按照状态值进行不同的处理，单片机启动后总是状态0，
	{
	case 0:                      /////状态0
		if(newkey!=0x0f)       //////如果有键
		{
			keystate=1;               //////有键记下状态1
			lastkey=newkey;        /////有键就用当前键码代替原来键码等待下次检查
		}
		break;                          //////如果无键直接跳出，有键进行上述处理后跳出，注意有键状态值已变
	case 1:                       ///////如上次有键，这次就转到状态1
		if(newkey==lastkey)   /////这次读取的键值如果和上次记录的一样，就是确认按键了
		{
			keyOK=1;                    //////置位按键标志
			keyval=newkey;          /////取得键码
			keystate=2;                //////按键状态下次要转状态2
		}
		else                       //////如果读键和上次不同，不确认按键，除了不进行以上处理还要把状态值清0
			keystate=0;
		break;                   ///////跳出
	case 2:                 /////////状态2
		if(newkey==0x0f)   ///////如果10毫秒后仍然无键
			keystate=0;            //////下次回到状态0
		break;
	}
	return keyval;      ////////返回键码
}
////////////////////////////////


uchar readkey()//单个
{
	static uchar keycount=0;
	uchar key_return=0;
	switch(keycount)
	{
		case 0:
			if(k1==0)
			{
				keycount=1;
			}break;
		case 1:
			if(k1==0)
			{
				keycount=2;
				key_return=1;
			}
			else
			{
				keycount=0;
			}break;
		case 2:
			if(k1==1)
			{
				keycount=0;
			}break;
	}
	return key_return;
}




uchar read_key(void){         //多个
	static uint key_time=0;
	static uchar key_state=0;
	uchar key_count=0;
	uchar key_return=0;
	key_count=P3&0x0f;
	switch(key_state){
		case 0:
			if(key_count!=0x0f){
				key_time=0;
				key_state=1;
			}break;
		case 1:
			if(key_count!=0x0f){
				key_time++;		 //消
				if(key_time>600){//抖
					key_state=2;
					switch(key_count){
						case 0x0d:key_return=1;break;
						case 0x0e:key_return=2;break;
						case 0x0b:key_return=3;break;
						case 0x07:key_return=4;break;
					}
				}
			}
			else{
				key_state=0;
			}break;
		case 2:
			if(key_count==0x0f){
				key_return=0;
				key_state=0;
			}break;
	}
	return key_return;
}



















