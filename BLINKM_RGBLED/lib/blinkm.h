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
#define BLINKM_CMD_STARTSCRIPT 0x70
#define BLINKM_CMD_SETCOLOR 0x6E
#define BLINKM_CMD_FADETOCOLOR 0x63
#define BLINKM_CMD_SETFADESPEED 0x66

#define BLINKM_SETTING_SCRIPT_FIRST_LINE_START 0x00

#define BLINKM_SCRIPT_PREDEFINED_MOOD_LIGHT 11
#define BLINKM_SCRIPT_PREDEFINED_VIRTUAL_CANDLE 12
#define BLINKM_SCRIPT_PREDEFINED_WATER_REFLECTIONS 13
#define BLINKM_SCRIPT_PREDEFINED_OLD_NEON 14
#define BLINKM_SCRIPT_PREDEFINED_THE_SEASONS 15
#define BLINKM_SCRIPT_PREDEFINED_THUNDERSTORM 16
#define BLINKM_SCRIPT_PREDEFINED_STOP_LIGHT 17
#define BLINKM_SCRIPT_PREDEFINED_SOS 18

void BlinkM_SetColor(uint8_t pwm_red, uint8_t pwm_green, uint8_t pwm_blue);
void BlinkM_FadeToColor(uint8_t pwm_red, uint8_t pwm_green, uint8_t pwm_blue);
void BlinkM_SetFadeSpeed(uint8_t speed);
void BlinkM_PlayScript(uint8_t script_number, uint8_t repeat);
void BlinkM_StopScript(void);

#endif
