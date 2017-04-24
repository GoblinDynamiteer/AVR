/*
 * UART.c
 *
 * Created: 2017-04-24
 * Author: Johan K�mpe
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
void USART_Transmit_String(uint8_t * data);
void USART_init(uint8_t ubrr);

int main(void){
	uint8_t * data = "ABC ";
	USART_init(MYUBRR);        //USART initialization
	while(1){
		//USART_Transmit(data);
    USART_Transmit_String(data);
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
  while ( !( UCSR0A & (1<<UDRE0)) )
  ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

/*  Send array of data to USART   */
void USART_Transmit_String(uint8_t * data){
  for(int i = 0; data[i] != '\0'; i++){
    USART_Transmit(data[i]);
  }
}
