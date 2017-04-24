/*
 * UART.c
 *
 * Created: 2017-04-24
 * Author: Johan Kämpe
 *
 *  Use USART to transmit data from Atmega328p.
 *  Pins:
 *  2 RX
 *  3 TX
 *
 *  Wires on Prolific USB-to-Serial adapter
 *  White: RX (Connect to AVR TX -- pin 2)
 *  Green: TX (Connect to AVR RX -- pin 3)
 */

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

/* From 328p Datasheet page 176  */
#define BAUD 2400
#define MYUBRR F_CPU/16/BAUD-1 //calculation from data sheet page 173

/*  Function prototypes   */
void USART_Transmit(uint8_t data);
void USART_init(uint8_t ubrr);

int main(void){
	uint8_t data = 'A';
	USART_init(MYUBRR);        //USART initialization
	while(1){
		UART_send(data);
		 _delay_ms(1000);
	}
	return 0;
}

/* From 328p Datasheet page 176  */
void USART_init(uint8_t ubrr){
  /* From 328p Datasheet page 176  */
  /* Set baud rate in register UBRRn */
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr);
  /*  Enable reciever and transmitter   */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

/* From 328p Datasheet page 177  */
void USART_Transmit(uint8_t data){
  /* Wait for empty transmit buffer */
  while (!( UCSRnA & (1<<UDREn))){
    ;
  }
  /* Put data into buffer, sends the data */
  UDRn = data;
}
