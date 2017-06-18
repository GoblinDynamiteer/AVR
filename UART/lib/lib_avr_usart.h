/*
    AVR Atmega328p function library

    by Johan Kampe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#ifndef BAUD_RATE
#define BAUD_RATE 2400
#endif

#ifndef _LIBAVRUSART_H
#define _LIBAVRUSART_H

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;

#include <avr/io.h>
#include <stdlib.h> //itoa()
#include <math.h> //round()


void USART_Init(uint32_t f_cpu, uint32_t baud_rate);
void USART_Send_Byte(uint8_t data);
void USART_Send(char * data);
void USART_Send_NewLine(char * data);
void USART_Send_Num(int n, uint8_t base);
void USART_Send_Num_NewLine(int n, uint8_t base);
void USART_Send_CRLF(void);
uint16_t USART_BaudToBrr(uint32_t f_cpu, uint32_t baud_rate);

#endif
