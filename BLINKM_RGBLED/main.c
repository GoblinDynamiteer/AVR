/*
 * BLINKM_RGBLED.c
 *
 * Created: 2017-04-28
 * Author : Johan Kämpe
 */

#define F_CPU 1000000UL
#define BAUD_RATE 2400

#include <avr/io.h>
#include "lib/i2c.h"
#include "lib/libavr.h"
#include "lib/avrblinkm.h"

int main(void){
  uint8_t success;
  SerialInit(F_CPU/16/BAUD_RATE-1);
  /*   INIT I2C, NO PRESCALING  */
  //i2c_init();
  i2cInit();
  _delay_us(10);
  success = blinkM_stopScript();
  if(success){
    SerialSendNL("Stopped BlinkM Script!");
  }
  else{
    SerialSendNL("ERROR stopping BlinkM Script!");
  }
  blinkM_setFadeSpeed(13);

  while(1){
    if(blinkM_fadeToRGB(0xFF,0x0,0x0)){
      SerialSendNL("Setting RED");
    }
    else{
      SerialSendNL("Error setting color RED");
    }
    sleep(1000);
    if(blinkM_fadeToRGB(0x00,0xFF,0x0)){
      SerialSendNL("Setting GREEN");
    }
    else{
      SerialSendNL("Error setting color GREEN");
    }
    sleep(1000);
    if(blinkM_fadeToRGB(0x0,0x0,0xFF)){
      SerialSendNL("Setting BLUE");
    }
    else{
      SerialSendNL("Error setting color BLUE");
    }
    sleep(1000);
  }
  return 0;
}
