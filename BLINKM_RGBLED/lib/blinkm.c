/*   BlinkM on Atmega328p function library

    by Johan Kämpe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#include "blinkm.h"

uint8_t BlinkM_SetColor(uint8_t pwm_red, uint8_t pwm_green, uint8_t pwm_blue){
    uint8_t data_buffer[4] = {
        BLINKM_CMD_SETCOLOR,
        pwm_red,
        pwm_green,
        pwm_blue
	};
    I2C_SendData(BLINKM_ADDRESS, data_buffer, 4);
}
