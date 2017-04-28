/*   BlinkM on Atmega328p function library

    by Johan Kämpe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#ifndef _AVRBLINKM_H_
#define _AVRBLINKM_H_

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include "i2c.h"
#include <util/delay.h>

//#define BLINKM_ADDRESS 0x09
#define BLINKM_ADDRESS 0x12

/*  Blinkm Addresses/commands   */
#define BLINKM_CMD_STOPSCRIPT 0x6f
#define BLINKM_CMD_SETCOLOR 0x6e
#define BLINKM_CMD_SETFADESPEED 0x66
#define BLINKM_CMD_SETCOLORWITHFADE 0x63

/*   avrblinkm.c  */
uint8_t blinkM_stopScript(void);
uint8_t blinkM_setRGB(uint8_t r, uint8_t g, uint8_t b);
uint8_t blinkM_fadeToRGB(uint8_t r, uint8_t g, uint8_t b);
uint8_t _blinkM_startI2C(void);
uint8_t blinkM_setFadeSpeed(uint8_t n);
uint8_t _blinkM_sendCommand0arg(uint8_t c);
uint8_t _blinkM_sendCommand1arg(uint8_t c, uint8_t a1);
uint8_t _blinkM_sendCommand3arg(uint8_t c, uint8_t a1, uint8_t a2, uint8_t a3);

#endif
