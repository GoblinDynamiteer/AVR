/*   Atmega328p function library

    by Johan Kï¿½mpe
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

void togglePin(uint8_t pin){
	switch(getPort(pin)){
		/* Port C */
		case 'C':
			PORTC ^= (1 << getPortPin(pin));
		/* Port D */
		case 'D':
			PORTD ^= (1 << getPortPin(pin));
		/* Port B */
		case 'B':
			PORTB ^= (1 << getPortPin(pin));
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

uint16_t ADCRead(uint8_t ADCpin){
  /*   Channel inputs 000 ADC0 -> 111 ADC7  */
  ADMUX &= (0b11111000); //Clear last three bits
  ADMUX |= ADCpin;
  _ADCStart();
  /*  ADC result register -- data sheet page 247 */
  return (ADC);
}

void _ADCStart(void){
  /*  Start conversion - data sheet page 249  */
  ADCSRA |= (1<<ADSC);
  /*  ADSC is set to 0 when conversion is complete  */
  while(ADCSRA & (1<<ADSC)){
    ;
  }
}

void ADCInit(void){
	// REFS1/REFS0 0/1 = AVcc with external capacitor at AREF pin
	ADMUX = (1<<REFS0);
	/*	 	*/
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

/*   TIMER0: 8 bit  */
void timer0init(uint8_t prescaler){
    /*  Set up Timer/Counter 0 with prescaling   */
    TCCR0B |= prescaler; //Data sheet page 141
    /*  Init Timer/Counter 0   */
    SET_COUNTER0 = 0;
}

/*   TIMER1: 16 bit  */
void timer1init(uint8_t prescaler){
    /*  Set up Timer/Counter 0 with prescaling   */
    TCCR1B |= prescaler; //Data sheet page 173
    /*  Init Timer/Counter 0   */
    SET_COUNTER1 = 0;
}

void i2cInit(void){
	/*	 TWI Status Register TWSR -- Data sheet page 231
		last two bits (TWPS0 & TWPS1) is prescaler value for clock
		0/0 = prescaler OFF
		0/1 = 4
		1/0 = 16
		1/1 = 64 */
	TWSR = 0; //set prescaler off
	/*	TWBR – TWI Bit Rate Register -- Data sheet page 230
		SCL_FREQUENCY = F_CPU/(16+2(TWBR)*Prescaler) ->
		TWBR = ((F_CPU/SCL_FREQUENCY)-16)/2 | if prescaler is 1 */
	int bitrate = (int)((F_CPU/SCL_FREQUENCY)-16)/2;
	if(bitrate < 10){
		bitrate = ((4000000/SCL_FREQUENCY)-16)/2;
	}
	TWBR = (uint8_t)bitrate;
}

uint8_t i2cWrite(uint8_t adress){
	_i2cSetStartCondition();
	return _i2cSetDeviceAdress(adress, 0x00);
}

uint8_t i2cSendByte(uint8_t data){
	/*	Code from data sheet page 270 	*/
	/*	Load DATA into TWDR Register. Clear
		TWINT bit in TWCR to start transmission of data. 	*/
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	_i2cWaitIntFlag();
	return _i2cCheckTWSR(I2C_DATA_SENT_ACK_RECIEVED);
}

void i2cStop(void){
	_i2cSetStopCondition();
}

uint8_t _i2cSetStartCondition(void){
	/*	Code from data sheet page 270 	*/
	/*	Send START condition	*/
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	_i2cWaitIntFlag();
	return _i2cCheckTWSR(I2C_START_TRANSMITTED);
}

void _i2cSetStopCondition(void){
	/*	Code from data sheet page 271 	*/
	/*	Send STOP condition	*/
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	/*	When the STOP condition is executed on the bus,
		the TWSTO bit is cleared automatically 	*/
	while(TWCR & (1<<TWSTO)){
		;
	}
}

uint8_t _i2cSetDeviceAdress(uint8_t a, uint8_t readWrite){
	/*	Code from data sheet page 270 	*/
	/* Load SLA_W into TWDR Register. Clear
	TWINT bit in TWCR to start transmission of
	address. */
	TWDR = a + readWrite;
	TWCR = (1<<TWINT) | (1<<TWEN);
	_i2cWaitIntFlag();
	return _i2cCheckTWSR(I2C_SLA_W_ACK_RECIEVED);
}

void _i2cWaitIntFlag(void){
	/*	Code from data sheet page 270 	*/
	/*	Wait for TWINT Flag set. 	*/
	while (!(TWCR & (1<<TWINT))){
		;
	}
}

uint8_t _i2cCheckTWSR(uint8_t status){
	/*	Check value of TWI Status Register. Mask
		prescaler bits. If status different from
		START go to ERROR. 	*/
	uint8_t TWSRstatus = (TWSR & (0b11111000));
	if(TWSRstatus != status){
		return 0; //ERROR
	}
	return 1;
}
