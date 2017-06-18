/*
    Atmega328p function library
    I2C

    by Johan Kampe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/
*/

#ifndef _LIBAVRI2C_H
#define _LIBAVRI2C_H

#define I2C_STATUS_START_TRANSMITTED 0x08
#define I2C_STATUS_SLA_W_ACK_RECIEVED 0x18
#define I2C_STATUS_DATA_SENT_ACK_RECIEVED 0x28

#define I2C_STATUS_REGISTER_PRESCALER_OFF 0x00
#define I2C_STATUS_REGISTER_MASK_PRESCALER 0xF8

#define I2C_CONTROL_REGISTER_START_CONDITION 0x20
#define I2C_CONTROL_REGISTER_STOP_CONDITION 0x10
#define I2C_CONTROL_REGISTER_INTERRUPT_FLAG 0x80
#define I2C_CONTROL_REGISTER_I2C_ENABLE 0x04

#define I2C_WRITE 0x00

#include <avr/io.h>

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;

void I2C_Init(uint32_t f_cpu, uint32_t f_scl);
uint8_t I2C_Write(uint8_t adress);
uint8_t I2C_Send_Byte(uint8_t data);
uint8_t I2C_SendData(uint8_t device_adress, uint8_t * data_buffer,
                     uint8_t data_size);
void I2C_STOP(void);

#endif
