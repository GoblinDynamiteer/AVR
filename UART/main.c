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
#define F_CPU 1000000UL
#include <util/delay.h>
#include "lib/libavr.h"

#define BAUD_RATE 2400

int main(void){
	pinMode(28, OUTPUT); //LED-pin
	SerialInit(F_CPU/16/BAUD_RATE-1);
	while(1){
    SerialSendNL("LED ON");
		setPin(28, ON);
		wait(1000);
		SerialSendNL("LED OFF");
		setPin(28, OFF);
		wait(1000);
	}
	return 0;
}
