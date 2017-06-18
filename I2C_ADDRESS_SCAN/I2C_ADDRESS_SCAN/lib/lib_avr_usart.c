/*
    AVR Atmega328p function library

    by Johan Kampe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#include "lib_avr_usart.h"

void USART_Init(uint32_t f_cpu, uint32_t baud_rate){
    uint16_t ubrr = USART_BaudToBrr(f_cpu, baud_rate);
    /* Set baud rate in register UBRRn */
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)(ubrr);
    /*  Enable reciever and transmitter   */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Send_Byte(uint8_t data){
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

/*  Send array of data to USART   */
void USART_Send(char * data){
    for(int i = 0; data[i] != '\0'; i++){
        USART_Send_Byte((uint8_t)data[i]);
    }
}

/*  Send integer as string to USART   */
void USART_Send_Num(int n, uint8_t base){
    char string[10];
    itoa(n, string, base);
    for(int i = 0; string[i] != '\0'; i++){
        USART_Send_Byte((uint8_t)string[i]);
    }
}

/*  Send integer as string to USART with new line   */
void USART_Send_Num_NewLine(int n, uint8_t base){
    USART_Send_Num(n, base);
    USART_Send_CRLF();
}

/*  Send array of data to USART with new line   */
void USART_Send_NewLine(char * data){
    for(int i = 0; data[i] != '\0'; i++){
        USART_Send_Byte((uint8_t)data[i]);
    }
    USART_Send_CRLF();
}

/*	Send CRLF (new line) 	*/
void USART_Send_CRLF(void){
    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = 0xD;
    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = 0xA;
}

uint16_t USART_BaudToBrr(uint32_t f_cpu, uint32_t baud_rate){
    return (uint16_t)round(f_cpu / 16.0 / baud_rate - 1);
}
