/*
 * SSD1306.c
 *
 * Created: 2017-04-29
 * Author : Johan Kampe
 */

#define F_CPU 1000000UL
#define BAUD_RATE 2400
#define SSD1306_ADDRESS 0x3c
#define DISPLAY_ON 0xAF

#define SERIAL_OUT

#include <avr/io.h>
#include "lib/libavr.h"
#include "lib/blinkm.h"

void SSD1306Init(void);
void SSD1306Start(void);
void SSD1306Draw(uint8_t Drawbyte);

 int main(void){
   i2cInit();
	 SerialInit(BAUD_VAL);
   _delay_us(10);
   blinkM_stopScript();
   blinkM_setFadeSpeed(13);
	 SSD1306Start();
	 int i = 0xA;
  	SSD1306Draw(i);
		SerialSend("Testing drawbyte: ");
		SerialSendNumNL(i, 16);


   while(1){
     blinkM_fadeToRGB(0x7D,0x7D,0x0);
     sleep(1000);
     blinkM_fadeToRGB(0x0,0x7D,0x7D);
     sleep(1000);
     blinkM_fadeToRGB(0x7D,0x0,0x7D);
     sleep(1000);
   }
   return 0;
 }

void SSD1306Init(void){
	int success = i2cWrite(SSD1306_ADDRESS);
	#ifdef SERIAL_OUT
	if(success){
		SerialSendNL("Display Found");
	}
	else{
		SerialSendNL("Display not Found!");
	}
	#endif
}

void SSD1306Start(void){
SSD1306Init();
i2cSendByte(0xAE);                    // Display Off

i2cSendByte(0x00 | 0x0);            // low col = 0
i2cSendByte(0x10 | 0x0);           // hi col = 0
i2cSendByte(0x40 | 0x0);            // line #0

i2cSendByte(0x81);                   // Set Contrast 0x81
i2cSendByte(0xCF);										// flips display
i2cSendByte(0xA1);                    // Segremap - 0xA1
i2cSendByte(0xC8);                    // COMSCAN DEC 0xC8 C0
i2cSendByte(0xA6);                    // Normal Display 0xA6 (Invert A7)

i2cSendByte(0xA4);                // DISPLAY ALL ON RESUME - 0xA4
i2cSendByte(0xA8);                    // Set Multiplex 0xA8
i2cSendByte(0x3F);                    // 1/64 Duty Cycle

i2cSendByte(0xD3);                    // Set Display Offset 0xD3
i2cSendByte(0x0);                     // no offset

i2cSendByte(0xD5);                    // Set Display Clk Div 0xD5
i2cSendByte(0x80);                    // Recommneded resistor ratio 0x80

i2cSendByte(0xD9);                  // Set Precharge 0xd9
i2cSendByte(0xF1);

i2cSendByte(0xDA);                    // Set COM Pins0xDA
i2cSendByte(0x12);

i2cSendByte(0xDB);                 // Set VCOM Detect - 0xDB
i2cSendByte(0x40);

i2cSendByte(0x20);                    // Set Memory Addressing Mode
i2cSendByte(0x01);                    // 0x00 - Horizontal

i2cSendByte(0x40 | 0x0);              // Set start line at line 0 - 0x40

i2cSendByte(0x8D);                    // Charge Pump -0x8D
i2cSendByte(0x14);


i2cSendByte(0xA4);              //--turn on all pixels - A5. Regular mode A4
i2cSendByte(0xAF);                //--turn on oled panel - AF
i2cStop();
}

void SSD1306Draw(uint8_t Drawbyte){
	i2cWrite(SSD1306_ADDRESS);
	i2cSendByte(0x21);        // column address
	i2cSendByte(0);           // column start address (0 = reset)
	i2cSendByte(127);         // column end addres (127 = reset)

	i2cSendByte(0x22);        // page address
	i2cSendByte(0);           // page start address (0 = reset);
	i2cSendByte(7);           // page end address
	i2cSendByte(0x40);
	for (uint16_t i=0; i<((128*64)/8); i++){
		i2cWrite(SSD1306_ADDRESS);   // set device address and write mode
		i2cSendByte(0x40);                        // set display RAM display start line register
		for (uint8_t x=0; x<16; x++){
			i2cSendByte(Drawbyte);
			i++;
		}
		i--;
		i2cStop();
	}
}
