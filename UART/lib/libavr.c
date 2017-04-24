/*   Atmega328p function library

    by Johan Kämpe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#include "libavr.h"

void pinMode(uint8_t pin, uint8_t io){
	switch(getPort(pin)){
		/* Port C */
		case 'C':
			if(io){	DDRC |= (1 << getPortPin(pin));	}
			else{		DDRC &= ~(1 << getPortPin(pin));	}
			break;
		/* Port D */
		case 'D':
			if(io){	DDRD |= (1 << getPortPin(pin));	}
			else{		DDRD &= ~(1 << getPortPin(pin));	}
			break;
		/* Port B */
		case 'B':
			if(io){	DDRB |= (1 << getPortPin(pin));	}
			else{		DDRB &= ~(1 << getPortPin(pin));	}
			break;
	}
}

void setPin(uint8_t pin, uint8_t onOff){
	switch(getPort(pin)){
		/* Port C */
		case 'C':
			if(onOff){	PORTC |= (1 << getPortPin(pin));	}
			else{				PORTC &= ~(1 << getPortPin(pin));	}
			break;
		/* Port D */
		case 'D':
			if(onOff){	PORTD |= (1 << getPortPin(pin));	}
			else{				PORTD &= ~(1 << getPortPin(pin));	}
			break;
		/* Port B */
		case 'B':
			if(onOff){	PORTB |= (1 << getPortPin(pin));	}
			else{				PORTB &= ~(1 << getPortPin(pin));	}
			break;
	}
}

uint8_t getPortPin(uint8_t pin){
	const uint8_t num[28] = {
		6,0,1,2,3,4,0,0,6,7,5,6,7,0,1,2,3,4,5,0,0,0,0,1,2,3,4,5
	};
	return num[pin-1];
}

uint8_t getPort(uint8_t pin){
	switch (pin) {
		case 1:		case 23:	case 24:	case 25:
		case 26:	case 27:	case 28:
			return 'C';
		case 2:		case 3:		case 4:		case 5:
		case 6:		case 11:	case 12:	case 13:
			return 'D';
		case 9:		case 10:	case 14:	case 15:
		case 16:	case 17:	case 18:	case 19:
			return 'B';
		}
	return '!'; //Wrong pin
}

/*
From 328p Datasheet page 176
Init USART with Baud rate --
Calculate ubrr with F_CPU/16/BAUD-1
 */
void SerialInit(uint8_t ubrr){
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
void _SerialSendData(char data){
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) )
  ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

/*  Send array of data to USART   */
void SerialSend(char * data){
  for(int i = 0; data[i] != '\0'; i++){
    _SerialSendData(data[i]);
  }
}

/*  Send array of data to USART with new line   */
void SerialSendNL(char * data){
  for(int i = 0; data[i] != '\0'; i++){
    _SerialSendData(data[i]);
  }
	_SerialNewLine();
}

/*	Send CRLF (new line) 	*/
void _SerialNewLine(void){
  while ( !( UCSR0A & (1<<UDRE0)) )
		;
  UDR0 = 0xD;
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	UDR0 = 0xA;
}
