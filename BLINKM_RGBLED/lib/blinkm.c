/*   BlinkM on Atmega328p function library

    by Johan Kämpe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#include "blinkm.h"

/*   BlinkM_SetColor
     Set RGB color of BlinkM
     Parameters
        pwm_red:    Red value
        pwm_green:  Green value
        pwm_blue:   Blue value
     */
void BlinkM_SetColor(uint8_t pwm_red, uint8_t pwm_green, uint8_t pwm_blue){
    uint8_t data_buffer[4] = {
        BLINKM_CMD_SETCOLOR,
        pwm_red,
        pwm_green,
        pwm_blue
	};
    I2C_SendData(BLINKM_ADDRESS, data_buffer, 4);
}

/*   BlinkM_FadeToColor
     Fade to RGB color, from current color
     Parameters
        pwm_red:    Red value
        pwm_green:  Green value
        pwm_blue:   Blue value
     */
void BlinkM_FadeToColor(uint8_t pwm_red, uint8_t pwm_green, uint8_t pwm_blue){
    uint8_t data_buffer[4] = {
        BLINKM_CMD_FADETOCOLOR,
        pwm_red,
        pwm_green,
        pwm_blue
	};
    I2C_SendData(BLINKM_ADDRESS, data_buffer, 4);
}

/*   BlinkM_SetFadeSpeed
     Set fade speed color for scripts and fade commands
     Parameters
        speed:  Fade speed value between 1 and 255
     Notes
        A speed value of 0 is invalid, 255 is used for instant
     */
void BlinkM_SetFadeSpeed(uint8_t speed){
    uint8_t data_buffer[2] = {
        BLINKM_CMD_SETFADESPEED,
        speed,
	};
    I2C_SendData(BLINKM_ADDRESS, data_buffer, 2);
}

/*   BlinkM_PlayScript
     Play BlinkM script
     Parameters
        script_number:  Script id number
        repeat:         Number of times to repeat script, 0 for endless
     */
void BlinkM_PlayScript(uint8_t script_number, uint8_t repeat){
    uint8_t data_buffer[4] = {
        BLINKM_CMD_STARTSCRIPT,
        script_number,
        repeat,
        BLINKM_SETTING_SCRIPT_FIRST_LINE_START
    };
    I2C_SendData(BLINKM_ADDRESS, data_buffer, 4);
}

/*   BlinkM_PlayScript
     Stop any running BlinkM script
     */
void BlinkM_StopScript(void){
    uint8_t data = BLINKM_CMD_STOPSCRIPT;
    I2C_SendData(BLINKM_ADDRESS, &data, 1);
}
