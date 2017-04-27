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

#define TIMER_PRESCALER_OFF (0b00000001)
#define TIMER_PRESCALER_8 (0b00000010)
#define TIMER_PRESCALER_64 (0b00000011)
#define TIMER_PRESCALER_256 (0b00000100)
#define TIMER_PRESCALER_1024 (0b00000101)

#define GET_COUNTER0 TCNT0
#define SET_COUNTER0 TCNT0

#define GET_COUNTER1 TCNT1
#define SET_COUNTER1 TCNT1

void timer0init(uint8_t prescaler);

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
    if(secTicker >= 10){
      togglePin(LEDPIN);
      secTicker = 0;
    }
  }
}

/*   TIMER0: 8 bit  */
void timer0init(uint8_t prescaler){
    /*  Set up Timer/Counter 0 with prescaling   */
    TCCR0B |= prescaler; //Data sheet page 141
    /*  Init Timer/Counter 0   */
    SET_COUNTER0 = 0; //Data sheet page 145
}

/*   TIMER1: 16 bit  */
void timer1init(uint8_t prescaler){
    /*  Set up Timer/Counter 0 with prescaling   */
    TCCR1B |= prescaler; //Data sheet page 141
    /*  Init Timer/Counter 0   */
    SET_COUNTER1 = 0; //Data sheet page 145
}
