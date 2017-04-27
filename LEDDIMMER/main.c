/*
 * LEDDIMMER.c
 *
 * Created: 2017-04-27
 * Author : Johan Kämpe
 *
 *  Dim LED using pot connected to Atmega328p
 *
 */

#include <avr/io.h>
#include "lib/libavr.h"
#define POTPIN ADC0
#define LEDPIN 28

void dimmer(uint16_t on);
uint16_t convertValue(uint16_t pv);

int main(void){
 pinMode(LEDPIN, OUTPUT); //LED-output
 uint16_t potValue;
 ADCInit();
 while(1){
  potValue = ADCRead(POTPIN);
  dimmer(potValue);
 }
}

void dimmer(uint16_t on){
  uint16_t off = 1024-on;
  setPin(LEDPIN, ON);
  while(on--){
    _delay_us(1);
  }
  setPin(LEDPIN, OFF);
  while(off--){
    _delay_us(1);
  }
}

/*  unused   */
uint16_t convertValue(uint16_t pv){
  /*   input 0-1024 -- return percentage  */
  uint16_t ret = (uint16_t)((double)pv / 1024.0 * 100.0);
  return ret;
}
