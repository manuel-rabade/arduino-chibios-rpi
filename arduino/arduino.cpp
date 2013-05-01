#include "ch.hpp"
#include "hal.h"
#include "string.h"
#include "arduino.h"

/* digital */

void pinMode(uint8_t pin, uint8_t mode) 
{
  gpio_port_t* port = digital_pin_to_port[pin];
  uint8_t pad = digital_pin_to_pad[pin];

  if (port == NULL || pad == 0) return;

  if (mode == INPUT) palSetPadMode(port, pad, PAL_MODE_INPUT);
  else if (mode == OUTPUT) palSetPadMode(port, pad, PAL_MODE_OUTPUT);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  gpio_port_t* port = digital_pin_to_port[pin];
  uint8_t pad = digital_pin_to_pad[pin];
  
  if (port == NULL || pad == 0) return;
  
  if (val == HIGH) palSetPad(port, pad);
  else if (val == LOW) palClearPad(port, pad);
}

int digitalRead(uint8_t pin)
{
  gpio_port_t* port = digital_pin_to_port[pin];
  uint8_t pad = digital_pin_to_pad[pin];
  
  if (port == NULL || pad == 0) return NOT_INPUT;
  
  if (palReadPad(port, pad)) return HIGH;
  return LOW;
}

/* serial */

void Serial::begin(unsigned long baud)
{
  (void) baud;
  chMBInit(&mboxSerial, bufferSerial, 512);
}

void Serial::print(const char *c) 
{
  struct _serialMsg *serialMsg = (_serialMsg *) chHeapAlloc(NULL, sizeof *serialMsg);
  serialMsg->timestamp = chTimeNow();
  serialMsg->msg = (char *) c;
  chMBPost(&mboxSerial, (msg_t) serialMsg, TIME_INFINITE);
}

void Serial::print(int num, int base) 
{
  Serial::print((unsigned long) num, base);
}

void Serial::print(unsigned long num, int base) 
{
  struct _serialMsg *serialMsg = (_serialMsg *) chHeapAlloc(NULL, sizeof *serialMsg);
  char *str = (char *) chHeapAlloc(NULL, (8 * sizeof(long)));
  serialMsg->timestamp = chTimeNow();
  *str = '\0';
  if (base < 2) base = 10;
  do {
    unsigned long m = num;
    num /= base;
    char c = m - base * num;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(num);
  serialMsg->msg = str;
  chMBPost(&mboxSerial, (msg_t) serialMsg, TIME_INFINITE);
}

/* i2c */

uint8_t Wire::rxBuffer[I2C_BUFFER];
uint8_t Wire::rxBufferIndex = 0;
uint8_t Wire::rxBufferLength = 0;

uint8_t Wire::txAddress = 0;
uint8_t Wire::txBuffer[I2C_BUFFER];
uint8_t Wire::txBufferIndex = 0;
uint8_t Wire::txBufferLength = 0;

void Wire::begin(void)
{
  I2CConfig i2cConfig;
  i2cStart(&I2C0, &i2cConfig);
}

void Wire::beginTransmission(uint8_t address)
{
  txAddress = address;
  txBufferIndex = 0;
  txBufferLength = 0;
}

uint8_t Wire::endTransmission(void)
{
  msg_t status;
  i2cAcquireBus(&I2C0);
  status = i2cMasterTransmit(&I2C0, txAddress, txBuffer, txBufferLength, NULL, 0);
  i2cReleaseBus(&I2C0);
  txBufferIndex = 0;
  txBufferLength = 0;
  return (uint8_t) status;
}

uint8_t Wire::requestFrom(uint8_t address, uint8_t quantity)
{
  if(quantity > I2C_BUFFER){
    quantity = I2C_BUFFER;
  }

  i2cAcquireBus(&I2C0);
  i2cMasterReceive(&I2C0, address, rxBuffer, quantity);
  i2cReleaseBus(&I2C0);

  rxBufferIndex = 0;
  rxBufferLength = quantity;

  return quantity;
}

size_t Wire::write(uint8_t data)
{
  if(txBufferLength >= I2C_BUFFER){
    return 0;
  }
  txBuffer[txBufferIndex] = data;
  ++txBufferIndex;
  txBufferLength = txBufferIndex;

  return 1;
}

int Wire::read(void)
{
  int value = -1;  
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }
  return value;
}
