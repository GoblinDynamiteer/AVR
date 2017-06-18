/*
 * BLINKM_RGBLED.c
 *
 * Created: 2017-04-28
 * Author : Johan Kämpe
 */

#define F_CPU 16000000UL
#define BAUD_RATE 115200
#define F_SCL 100000
#define FADE_DELAY 5
#define PWM_MAX 128

#include <avr/io.h>
#include <util/delay.h>
#include "lib/lib_avr_i2c.h"
#include "lib/lib_avr_usart.h"
#include "lib/blinkm.h"


int main(void){
	
	USART_Init(F_CPU, BAUD_RATE);
	I2C_Init(F_CPU, F_SCL);
	
	uint8_t pwm = 0x01;
	
	while(1){
		for (; pwm < PWM_MAX; pwm++){
			BlinkM_SetColor(pwm, 0x00, 0x00);
			_delay_ms(FADE_DELAY);
		}
		for (; pwm > 0x00; pwm--){
			BlinkM_SetColor(pwm, 0x00, 0x00);
			_delay_ms(FADE_DELAY);
			}
	}

	return 0;
}
