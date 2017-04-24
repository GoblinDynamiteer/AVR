/*
 * TIMER.c
 *
 * Created: 2017-04-24
 * Author : Johan Kämpe
 */

#include <avr/io.h>
#include "lib/libavr.h"

#define LEDPIN 28

int main(void){
  pinMode(LEDPIN, OUTPUT);
  while(1){
    setPin(LEDPIN, ON);
    sleep(1200);
    setPin(LEDPIN, OFF);
    sleep(1200);
  }
}
