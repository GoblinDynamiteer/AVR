#include "lib/lcd.h"

int main(void){
	LCDInit();
	LCDSendString("PUSS!");
	LCDSendStringAt("PUSS!!", 4, 2);
	_delay_ms(400);
	LCDSendStringAt("/Johan", 11, 1);
  while(1){}
}
