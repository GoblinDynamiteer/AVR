/*
 * RESISTOR_LADDER_DAC.c
 *
 * Created: 2017-05-02
 * Author : Johan Kämpe
 *
 * 4 bits -> analog
 */

#include <avr/io.h>
#include "lib/libavr.h"

#define DECIMAL_BASE 10
#define BINARY_BASE 2
#define HEXADECIMAL_BASE 16
#define ANALOG_READ_PIN ADC5 //analog input


int main(void){
  SerialInit(BAUD_VAL);
  ADCInit();
  DDRB = 0xFF; //Digital input pins connected to PB0, PB1, PB2, PB3
  uint16_t analog;
  while(1){
	SerialSendNL("DAC 4bit w/ resistor ladder!");
    for(int i = 0x00; i <= 0b00001111; i++){
      PORTB = i;
      analog = ADCRead(ANALOG_READ_PIN);
	  SerialSend("Digital: ");
	  SerialSendNum(i, BINARY_BASE);
	  SerialSend(" - Analog: ");
      SerialSendNumNL(analog, DECIMAL_BASE);
      sleep(2000);
    }
  }
}
