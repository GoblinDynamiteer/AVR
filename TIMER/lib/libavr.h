/*   Atmega328p function library

    by Johan K�mpe
    by Johan K�mp    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#ifndef BAUD_RATE
#define BAUD_RATE 2400
#endif

#define BAUD_VAL F_CPU/16/BAUD_RATE-1

#ifndef _LIBAVR_H
#define _LIBAVR_H

#include <avr/io.h>
#include <util/delay.h>

typedef unsigned char uint8_t;

enum{INPUT, OUTPUT};
enum{OFF, ON};
enum{ADC0, ADC1, ADC2, ADC3, ADC4, ADC5}; //Analog pins

/*  libavr.c */

/*  Misc pin/port   */
void pinMode(uint8_t pin, uint8_t io);
uint8_t getPortPin(uint8_t pin);
uint8_t getPort(uint8_t pin);
void setPin(uint8_t pin, uint8_t onOff);
void togglePin(uint8_t pin);

/*  UART Serial communication   */
void SerialSend(char * data);
void SerialSendNL(char * data);
void _SerialSendData(char data);
void SerialInit(uint8_t ubrr);
void _SerialNewLine(void);

/*  Analog to digital conversion  */
uint16_t ADCRead(uint8_t ADCpin);
int _ADCStart(void);
void ADCInit(void);

#define sleep(x) _delay_ms(x)
#define wait(x) _delay_ms(x)

#endif
