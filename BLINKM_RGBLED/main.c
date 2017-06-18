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
	
	BlinkM_SetFadeSpeed(20);
	
	BlinkM_StopScript();
		
	BlinkM_SetColor(0x00,0x00,0x80);

	while(1){
		BlinkM_FadeToColor(0xFF, 0x00, 0x00);
		_delay_ms(2000);
		BlinkM_FadeToColor(0xFF, 0xFF, 0x00);
		_delay_ms(2000);
		BlinkM_FadeToColor(0x00, 0xFF, 0xFF);
		_delay_ms(2000);
		BlinkM_FadeToColor(0xFF, 0x00, 0xFF);
		_delay_ms(2000);
	}
	
	


	
	return 0;
}
