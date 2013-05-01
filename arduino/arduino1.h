namespace _arduino1 {  
  /* config */
  gpio_port_t* digital_pin_to_port[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    GPIO7_PORT, // pin 12
    GPIO25_PORT, // pin 13
    NULL, NULL, NULL, NULL, NULL, NULL, NULL
  };
  uint8_t digital_pin_to_pad[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    GPIO7_PAD, // pin 12
    GPIO25_PAD, // pin 13
    0, 0, 0, 0, 0, 0, 0
  };

  /* buffers */
  Mailbox mboxSerial;
  msg_t bufferSerial[SERIAL_BUFFER];

#include "arduino.cpp"
#include "arduino1.cpp"
}
