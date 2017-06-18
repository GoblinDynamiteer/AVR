/*
    Atmega328p function library
    I2C

    by Johan Kampe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/
*/

#include "lib_avr_i2c.h"

void _i2cWaitIntFlag(void){
	while (!(TWCR & I2C_CONTROL_REGISTER_INTERRUPT_FLAG));
}

uint8_t _i2cCheckTWSR(uint8_t status){
	return ((TWSR & I2C_STATUS_REGISTER_MASK_PRESCALER) == status);
}

uint8_t _I2C_SetStartCondition(void){
	TWCR = I2C_CONTROL_REGISTER_INTERRUPT_FLAG |
        I2C_CONTROL_REGISTER_START_CONDITION | I2C_CONTROL_REGISTER_I2C_ENABLE;
	_i2cWaitIntFlag();
	return _i2cCheckTWSR(I2C_STATUS_START_TRANSMITTED);
}

void _i2cSetStopCondition(void){
	TWCR = I2C_CONTROL_REGISTER_INTERRUPT_FLAG |
        I2C_CONTROL_REGISTER_I2C_ENABLE | I2C_CONTROL_REGISTER_STOP_CONDITION;
	while(TWCR & I2C_CONTROL_REGISTER_STOP_CONDITION);
}

uint8_t _i2cSetDeviceAdress(uint8_t adress, uint8_t read_write){
	TWDR = ((adress << 1) | read_write);
	TWCR = I2C_CONTROL_REGISTER_INTERRUPT_FLAG |
        I2C_CONTROL_REGISTER_I2C_ENABLE;
	_i2cWaitIntFlag();
	return _i2cCheckTWSR(I2C_STATUS_SLA_W_ACK_RECIEVED);
}

void I2C_Init(uint32_t f_cpu, uint32_t f_scl){
	TWSR = I2C_STATUS_REGISTER_PRESCALER_OFF;
	int bitrate = (int)((f_cpu/f_scl)-16)/2;
    TWBR = (bitrate < 10) ? (uint8_t)((4000000/f_scl)-16)/2 : (uint8_t)bitrate;
}

uint8_t I2C_Write(uint8_t adress){
	_I2C_SetStartCondition();
	return _i2cSetDeviceAdress(adress, I2C_WRITE);
}

uint8_t I2C_Send_Byte(uint8_t data){
	TWDR = data;
    TWCR = I2C_CONTROL_REGISTER_INTERRUPT_FLAG |
        I2C_CONTROL_REGISTER_I2C_ENABLE;
	_i2cWaitIntFlag();
	return _i2cCheckTWSR(I2C_STATUS_DATA_SENT_ACK_RECIEVED);
}

void I2C_STOP(void){
	_i2cSetStopCondition();
}
