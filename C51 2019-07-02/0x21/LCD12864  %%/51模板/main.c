#include"reg52.h"
#include"intrins.h"
#include"lcd12864.h"




void main(void){
	LCD_Init();
	LCD_Pos(0,0);
	LCD_WriteData("w");
	
	delay(1);
	
	
	while(1) {
		
	}
}













