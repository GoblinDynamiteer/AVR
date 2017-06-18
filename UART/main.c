/*
 * UART.c
 *
 * Created: 2017-04-24
 * Author: Johan Kämpe
 *
 *  Use USART to transmit data from Atmega328p.
 *  Pins:
 *  2 RX
 *  3 TX
 *
 *  Wires on Prolific USB-to-Serial adapter
 *  White: RX (Connect to AVR TX -- pin 2)
 *  Green: TX (Connect to AVR RX -- pin 3)
 */

#include <avr/io.h>

#define F_CPU 16000000UL
#define BAUD_RATE 115200
#define BASE_DECIMAL 10
#define BASE_HEXADECIMAL 16

#include <util/delay.h>
#include "lib/libavr.h"
#include "lib/lib_avr_usart.h"


int main(void){
	USART_Init(F_CPU, BAUD_RATE);
	while(1){
		USART_Send_NewLine("HELLOW");
		wait(1000);
		USART_Send_NewLine("BYE!");
		wait(1000);
		USART_Send_Num_NewLine(54, BASE_DECIMAL);
		USART_Send_Num(32, BASE_DECIMAL);
		USART_Send(" = 0x");
		USART_Send_Num_NewLine(32, BASE_HEXADECIMAL);
		wait(1000);
	}
	return 0;
}
