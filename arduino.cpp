#include "arduino.h"
#include "ch.hpp"
#include "hal.h"
#include "chprintf.h"

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

/* serial */

void Serial::begin(unsigned long baud)
{
  (void) baud;
}
