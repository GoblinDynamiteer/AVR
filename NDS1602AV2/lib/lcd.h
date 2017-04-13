/*
LCD NDS1602AV2 to Atmega328p

Created: 2017-04-13
Author : Johan Kämpe

Pins on LCD, from data sheet
01 VSS - GND
02 VDD - 5V
03 V0  - LCD contrast, via pot
04 RS  - Register Select (OFF- Send command, ON- Send data)
05 R/W - Read/Write (High-Read, Low-Write)
06 E   - Enable Signal
07-14  - Data bus DB0-DB7
15 BLA - Back light 5V
16 BLA - Back light GND

 */

#ifndef LIBLCD_H
#define LIBLCD_H

#define F_CPU 1000000UL
#include <util/delay.h>

#include <avr/io.h>

#define READ 0
#define WRITE 0xFF

#define DATAPORT PORTD
#define DATAPORT_DDR DDRD
#define CONTROLPORT PORTC
#define CONTROLPORT_DDR DDRC
#define RS 3
#define RW 4
#define EN 5

#define CMD_CLEARDISPLAY 0x01
#define CMD_SETBITMODE 0x38 //8-bit mode
//Entire display ON, Cursor ON, no blink
#define CMD_SETDISPLAYMODE (0b00001110)

/* lcd.h */
void LCDSendChar(uint8_t character);
void LCDSendCommand(uint8_t command);
void LCDBusyCheck(void);
void LCDEnable(void);
void LCDInit(void);

#endif
