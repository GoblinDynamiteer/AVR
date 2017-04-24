/*
 * UART.c
 *
 * Created: 2017-04-24
 * Author: Johan Kämpe
 */

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

int main(void){
  DDRC = (1 << PC5);
  while(1){
    PORTC |= (1 << PC5);
    _delay_ms(150);
    PORTC &= ~(1 << PC5);
    _delay_ms(150);
  }
}
