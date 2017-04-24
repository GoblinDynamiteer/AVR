/*
 * ADC.c
 *
 * Created: 2017-04-24
 * Author : Johan Kämpe
 *
 * Analog to digital conversion
 */

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#include "lib/libavr.h"

#define LEDPIN 28

int main(void){
  pinMode(LEDPIN, OUTPUT); //LED-output
  while(1){
    setPin(LEDPIN, ON);
    sleep(500);
    setPin(LEDPIN, OFF);
    sleep(500);
  }
}
