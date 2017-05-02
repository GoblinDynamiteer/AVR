/*
 * RESISTOR_LADDER_DAC.c
 *
 * Created: 2017-05-02
 * Author : Johan Kämpe
 */

#include <avr/io.h>
#include "lib/libavr.h"

#define NUM_BASE 10

int main(void){
  SerialInit(BAUD_VAL);
  while (1){
      for(int i = 0; i < 100; i++){
        SerialSendNumNL(i, NUM_BASE);
        sleep(1000);
    }
  }
}
