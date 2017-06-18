/*
 * I2C_ADDRESS_SCAN.c
 *
 * Scan I2C bus for devices, prints out addresses to USART
 *
 * Created: 2017-06-18
 * Author : Johan Kampe
 */ 

#define F_CPU 16000000UL
#define BAUD_RATE 115200
#define F_SCL 100000

#include <avr/io.h>
#include <util/delay.h>
#include "lib/lib_avr_i2c.h"
#include "lib/lib_avr_usart.h"

uint8_t _I2C_SetStartCondition(void);
uint8_t _i2cSetDeviceAdress(uint8_t adress, uint8_t read_write);

int main(void){
	
	USART_Init(F_CPU, BAUD_RATE);
	I2C_Init(F_CPU, F_SCL);
	
	for(uint8_t i = 0x01; i < 0x7F; i++){
		_I2C_SetStartCondition();
		if(_i2cSetDeviceAdress(i, 0x00)){
			USART_Send("Found I2C device with Adress: 0x");
			USART_Send_Num_NewLine(i, 16);
		}
		I2C_STOP();
		_delay_ms(1);
	}
	
	return 0;
}

