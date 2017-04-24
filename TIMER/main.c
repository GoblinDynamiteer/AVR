/*
 * TIMER.c
 *
 * Created: 2017-04-24
 * Author : Johan Kämpe
 */

#include <avr/io.h>
#include "lib/libavr.h"

#define LEDPIN 28

void timerInit64(void);

int main(void){
  pinMode(LEDPIN, OUTPUT);
  setPin(LEDPIN, OFF);
  timerInit64();
  while(1){
    if(TCNT1 >= 15624){
      togglePin(LEDPIN);
      TCNT1 = 0;
    }
  }
}

void timerInit64(void){
  TCCR1B |= ((1 << CS10) | (1 << CS11)); // Set up timer at Fcpu/64
}
