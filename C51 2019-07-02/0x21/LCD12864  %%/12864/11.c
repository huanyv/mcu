void set_xy(uchar x,uchar y)//x为行， y为列
{
	if(y>=64)// 列地址大于等于 64时右屏显示
	{
		CS=1;
		y=y-64;
	}
	else//列地址小于 64时左屏显示
	{
		CS=2;
	}
	write_cm(0x40|y);//写列地址
	_nop_();
	write_cm(0xb8|x);//写行地址
}


void Disp_zf(uchar R,uchar L,uchar *p)//用来显示 ASCII字符，其程序代码如下：
void Disp_zf(uchar R,uchar L,uchar *p)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		set_xy(2*R,8*L+i);
		write_data(p[i]);
		set_xy(2*R+1,8*L+i);
		write_data(p[i+8]);
	}
}



