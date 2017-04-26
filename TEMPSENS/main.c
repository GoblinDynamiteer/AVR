/*
 * TEMPSENS.c
 *
 * Created: 2017-04-26
 * Author : Johan K�mpe
 */

#include <avr/io.h>
#include "lib/libavr.h"

#define LED_PIN 14

int main(void){
    pinMode(LED_PIN, ON);
    ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
    ADCSRA |= _BV(ADEN);  // enable the ADC
    unsigned int wADC;
    double t;
    sleep(20);
    while(1){
        ADCSRA |= _BV(ADSC);  // Start the ADC
        // Detect end-of-conversion
        while (bit_is_set(ADCSRA,ADSC));
        // Reading register "ADCW" takes care of how to read ADCL and ADCH.
        wADC = ADCW;
        // The offset of 324.31 could be wrong. It is just an indication.
        t = (wADC - 324.31 ) / 1.22;
		if(t >= 18.0){
			setPin(LED_PIN, ON);
		}
        else{
            setPin(LED_PIN, OFF);
        }
        sleep(200);
    }
}
