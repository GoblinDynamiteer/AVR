/*   BlinkM on Atmega328p function library

    by Johan Kämpe
    https://www.linkedin.com/in/johankampe/
    https://github.com/GoblinDynamiteer/

*/

#include "blinkm.h"

uint8_t blinkM_stopScript(void){
  return _blinkM_sendCommand0arg(BLINKM_CMD_STOPSCRIPT);
}

uint8_t blinkM_setRGB(uint8_t r, uint8_t g, uint8_t b){
  return _blinkM_sendCommand3arg(BLINKM_CMD_SETCOLOR, r, g, b);
}

uint8_t blinkM_fadeToRGB(uint8_t r, uint8_t g, uint8_t b){
  return _blinkM_sendCommand3arg(BLINKM_CMD_SETCOLORWITHFADE, r, g, b);
}

/*   Set fade speed. 0 is reserved, 255 is instant, lower is slower  */
uint8_t blinkM_setFadeSpeed(uint8_t n){
  return _blinkM_sendCommand1arg(BLINKM_CMD_SETFADESPEED, n);
}

uint8_t _blinkM_startI2C(void){
  uint8_t success = i2cWrite(BLINKM_ADDRESS);
  //uint8_t success = i2c_start(BLINKM_ADDRESS|I2C_WRITE);
  _delay_us(10);
  return success;
}

/*  Send command without arguments to blinkM   */
uint8_t _blinkM_sendCommand0arg(uint8_t c){
  uint8_t success = _blinkM_startI2C();
  i2cSendByte(c);
  i2cStop();
  return success;
}

/*  Send command with one argument to blinkM   */
uint8_t _blinkM_sendCommand1arg(uint8_t c, uint8_t a1){
  uint8_t success = _blinkM_startI2C();
  i2cSendByte(c);
  i2cSendByte(a1);
  i2cStop();
  return success;
}

/*  Send command with three arguments to blinkM   */
uint8_t _blinkM_sendCommand3arg(uint8_t c, uint8_t a1, uint8_t a2, uint8_t a3){
  uint8_t success = _blinkM_startI2C();
  i2cSendByte(c);
  i2cSendByte(a1);
  i2cSendByte(a2);
  i2cSendByte(a3);
  i2cStop();
  return success;
}
