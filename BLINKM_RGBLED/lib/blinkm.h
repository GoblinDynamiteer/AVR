/*   BlinkM on Atmega328p function library

    by Johan Kampe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#ifndef _AVRBLINKM_H_
#define _AVRBLINKM_H_

#include "lib_avr_i2c.h"

#define BLINKM_ADDRESS 0x09
#define BLINKM_ADDRESS_ALTERNATIVE 0x12

#define BLINKM_CMD_STOPSCRIPT 0x6F
#define BLINKM_CMD_SETCOLOR 0x6E
#define BLINKM_CMD_SETFADESPEED 0x66
#define BLINKM_CMD_SETCOLORWITHFADE 0x63

uint8_t BlinkM_SetColor(uint8_t pwm_red, uint8_t pwm_green, uint8_t pwm_blue);

#endif
