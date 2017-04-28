/*
 * TIMER.c
 *
 * Created: 2017-04-24
 * Author : Johan Kämpe
 */

#define F_CPU 1000000UL
#include <avr/io.h>
#include "lib/libavr.h"

#define LEDPIN 28

#define TARGET_DELAY_MS 200

int main(void){
  pinMode(LEDPIN, OUTPUT);
  setPin(LEDPIN, OFF);
  timer0init(TIMER_PRESCALER_256);
  timer1init(TIMER_PRESCALER_8);
   /*  From EXCEL ~20ms for 8bit timer with 256 prescaler  */
  //uint8_t timerTrigger = 78, secTicker = 0;
  uint16_t timerTrigger = 24999, secTicker = 0;
  while(1){
    if(GET_COUNTER1 >= timerTrigger){
      secTicker++;
      SET_COUNTER1 = 0;
    }
    if(secTicker >= 1000/TARGET_DELAY_MS){
      togglePin(LEDPIN);
      secTicker = 0;
    }
  }
}
