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
#define TRIGGER = 999 //1ms

void dimmer(uint16_t on);
uint16_t convertValue(uint16_t pv);

uint16_t PWMon = 0;
uint16_t PWMoff = 0;
uint8_t OnOff = 1;

int main(void){
 pinMode(LEDPIN, OUTPUT); //LED-output
 uint16_t potValue, onCount = 0, offCount = 0;
 ADCInit();
 timer1init(TIMER_PRESCALER_OFF); //16bit timer
 while(1){
  PWMon = ADCRead(POTPIN) /10 ;
  PWMoff = 102 - PWMon;
  uint8_t current = OnOff;

  if(OnOff){
    if(GET_COUNTER1 >= TRIGGER){
      SET_COUNTER1 = 0x0;
      onCount++;
    }
    if(onCount > PWMon){
      togglePin(LEDPIN)
      OnOff = 0;
      onCount = 0;
    }
  }

  if(!OnOff){
    if(GET_COUNTER1 >= TRIGGER){
      SET_COUNTER1 = 0x0;
      offCount++;
    }
    if(offCount > PWMoff){
      togglePin(LEDPIN)
      OnOff = 1;
      offCount = 0;
    }
  }
 }
}

/*  unused   */
uint16_t convertValue(uint16_t pv){
  /*   input 0-1024 -- return percentage  */
  uint16_t ret = (uint16_t)((double)pv / 1024.0 * 100.0);
  return ret;
}
