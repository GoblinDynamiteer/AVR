/*   Atmega328p function library

    by Johan K�mpe
    by Johan K�mp    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#ifndef _LIBAVR_H
#define _LIBAVR_H

#include <avr/io.h>

typedef unsigned char uint8_t;

enum{INPUT, OUTPUT};
enum{OFF, ON};

/*  libavr.c */
void pinMode(uint8_t pin, uint8_t io);
uint8_t getPortPin(uint8_t pin);
uint8_t getPort(uint8_t pin);
void setPin(uint8_t pin, uint8_t onOff);

void SerialSend(char * data);
void SerialSendNL(char * data);
void _SerialSendData(char data);
void SerialInit(uint8_t ubrr);
void _SerialNewLine(void);

#define sleep(x) _delay_ms(x)
#define wait(x) _delay_ms(x)

#endif
