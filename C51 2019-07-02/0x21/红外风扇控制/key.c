#include "key.h"
#include "timer.h"


extern uint speed;

void KEY_Ctrl(void)
{
	static bit KEY_LETGO = 0;
	if( (k1 == 0)&&(KEY_LETGO == 0) )
	{
		delay(2000);
		if(k1 == 0)
		{
			KEY_LETGO = 1;
			
			speed = 2;
		}
	}
	if( (k2 == 0)&&(KEY_LETGO == 0) )
	{
		delay(2000);
		if(k2 == 0)
		{
			KEY_LETGO = 1;
			
			speed = 5;
		}
	}
	if( (k3 == 0)&&(KEY_LETGO == 0) )
	{
		delay(2000);
		if(k3 == 0)
		{
			KEY_LETGO = 1;
			
			speed = 10;
			
		}
	}
	if( (k1 == 1)&&(k2 == 1)&&(k3 == 1) )
		KEY_LETGO = 0;	
}
