/*
 * BLINKM_RGBLED.c
 *
 * Created: 2017-04-28
 * Author : Johan Kämpe
 */

#define F_CPU 1000000UL
#define BAUD_RATE 2400

#include <avr/io.h>
#include "lib/libavr.h"
#include "lib/avrblinkm.h"

int main(void){
  SerialInit(F_CPU/16/BAUD_RATE-1);
  /*   INIT I2C, NO PRESCALING  */
  i2cInit();
  _delay_us(10);
  blinkM_stopScript();
  blinkM_setFadeSpeed(13);
  while(1){
    blinkM_fadeToRGB(0xFF,0x0,0x0);
    sleep(1000);
    blinkM_fadeToRGB(0x00,0xFF,0x0);
    sleep(1000);
    blinkM_fadeToRGB(0x0,0x0,0xFF);
    sleep(1000);
  }
  return 0;
}
