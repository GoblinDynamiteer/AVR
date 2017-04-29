/*   Atmega328p function library

    by Johan Kämpe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#ifndef BAUD_RATE
#define BAUD_RATE 2400
#endif

#define BAUD_VAL F_CPU/16/BAUD_RATE-1 //Data sheet page 173

#define SCL_FREQUENCY 100000UL //100kHz
#define I2C_START_TRANSMITTED 0x08 //data sheet page 273
#define I2C_SLA_W_ACK_RECIEVED 0x18 //data sheet page 273
#define I2C_DATA_SENT_ACK_RECIEVED 0x28 //data sheet page 274

#ifndef _LIBAVR_H
#define _LIBAVR_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h> //itoa

typedef unsigned char uint8_t;

enum{INPUT, OUTPUT};
enum{OFF, ON};
enum{ADC0, ADC1, ADC2, ADC3, ADC4, ADC5}; //Analog pins

#define sleep(x) _delay_ms(x)
#define wait(x) _delay_ms(x)

#define TIMER_PRESCALER_OFF (0b00000001)
#define TIMER_PRESCALER_8 (0b00000010)
#define TIMER_PRESCALER_64 (0b00000011)
#define TIMER_PRESCALER_256 (0b00000100)
#define TIMER_PRESCALER_1024 (0b00000101)

#define GET_COUNTER0 TCNT0
#define SET_COUNTER0 TCNT0

#define GET_COUNTER1 TCNT1
#define SET_COUNTER1 TCNT1

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
void SerialSendNum(int n, uint8_t base);
void SerialSendNumNL(int n, uint8_t base);
void _SerialSendData(char data);
void SerialInit(uint8_t ubrr);
void _SerialNewLine(void);

/*  Analog to digital conversion  */
uint16_t ADCRead(uint8_t ADCpin);
void _ADCStart(void);
void ADCInit(void);

/*  Timers */
void timer0init(uint8_t prescaler);
void timer1init(uint8_t prescaler);

/*  I2C */
void i2cInit(void);
uint8_t i2cWrite(uint8_t adress);
uint8_t i2cSendByte(uint8_t data);
void i2cStop(void);
void i2cScanner(void);
uint8_t _i2cSetStartCondition(void);
void _i2cSetStopCondition(void);
void _i2cWaitIntFlag(void);
uint8_t _i2cSetDeviceAdress(uint8_t a, uint8_t readWrite);
uint8_t _i2cCheckTWSR(uint8_t status);



#endif
