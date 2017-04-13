#include "lib/lcd.h"
#include <stdio.h>

int main(void){
	LCDInit();
	LCDSendString("PUSS!");
	LCDSendStringAt("PUSS!!", 4, 2);
	_delay_ms(400);
	LCDSendStringAt("/Johan", 11, 1);

  while(0){
		for(int i = 0; i <= 0xff; i++){
			LCDSendCommand(CMD_CLEARDISPLAY);
			_delay_ms(2);
			LCDSendChar(i);
			char num[10];
			sprintf(num, "%.8i", i);
			LCDSendStringAt(num, 1, 2);
			_delay_ms(100);
		}
	}
}
