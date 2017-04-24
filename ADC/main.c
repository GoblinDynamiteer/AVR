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
#define BAUD_RATE 2400
#define POTPIN ADC0
#include <util/delay.h>
#include <string.h>
#include "lib/libavr.h"

#define LEDPIN 28
uint16_t adc_read(uint8_t ch);
uint16_t ADCRead(uint8_t ADCpin);
int _ADCStart(void);

int main(void){
  pinMode(LEDPIN, OUTPUT); //LED-output
  SerialInit(F_CPU/16/BAUD_RATE-1);
  uint16_t potValue;
  char digital[4] = "";
  ADCInit();
  while(1){
    potValue = ADCRead(POTPIN);
    if(potValue > 1024/2){
      setPin(LEDPIN, ON);
    }
    else{
      setPin(LEDPIN, OFF);
    }
    itoa(potValue, digital, 10);
    SerialSend("PotVal: ");
    SerialSendNL(digital);
    wait(200);
  }
}
