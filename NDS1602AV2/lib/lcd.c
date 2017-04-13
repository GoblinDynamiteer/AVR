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

#include "lcd.h"

void LCDInit(void){
	CONTROLPORT_DDR |= (1 << RS) | (1 << RW) | (1 << EN);
	_delay_ms(15);
	LCDSendCommand(CMD_CLEARDISPLAY);
	_delay_ms(2);
	LCDSendCommand(CMD_SETBITMODE);
	_delay_us(50);
	LCDSendCommand(CMD_SETDISPLAYMODE);
	_delay_us(50);
}

/* Send enable signal */
void LCDEnable(void){
	CONTROLPORT |= (1 << EN);
	asm volatile ("nop");
	asm volatile ("nop");
	CONTROLPORT &= ~(1 << EN);
}

/* Wait until display is not busy */
void LCDBusyCheck(void){
	DATAPORT_DDR = READ;
	CONTROLPORT |= (1 << RW);
	CONTROLPORT &= ~(1 << RS);
	while(DATAPORT >= (0b10000000)){
		LCDEnable();
	}
	DATAPORT_DDR = WRITE;
}

/* Send command to display */
void LCDSendCommand(uint8_t command){
	LCDBusyCheck();
	DATAPORT = command;
	CONTROLPORT &= ~(1 << RW | 1 << RS);
	LCDEnable();
	DATAPORT = 0;
}

/* Print a single character on display */
void LCDSendChar(uint8_t character){
	LCDBusyCheck();
	DATAPORT = character;
	CONTROLPORT &= ~(1 << RW);
	CONTROLPORT |= (1 << RS);
	LCDEnable();
	DATAPORT = 0;
}

/* Prints out a string on display */
void LCDSendString(char * string){
  for(int i = 0; string[i] != '\0'; i++){
      LCDSendChar(string[i]);
      _delay_ms(150);
  }
}

/* Prints out a string on display, second row */
void LCDSendStringSR(char * string){
  LCDSetCursorSR();
  LCDSendString(string);
}

/* Prints string at row and position */
void LCDSendStringAt(char * string, uint8_t pos, uint8_t row){
  LCDSendCommand(CMD_CURSORHOME);
  _delay_ms(2);
  if(row == 2){
    LCDSetCursorSR();
  }
  for(int i = 0; i < pos-1; i++){
    LCDSendCommand(CMD_CURSORRIGHT);
    _delay_us(50);
  }
  LCDSendString(string);
}

/* Sets cursor at second row start position*/
void LCDSetCursorSR(void){
  LCDSendCommand(CMD_CURSORHOME);
  _delay_ms(2);
  for(int i = 0; i < 40; i++){
    LCDSendCommand(CMD_CURSORRIGHT);
    _delay_us(50);
  }
}
