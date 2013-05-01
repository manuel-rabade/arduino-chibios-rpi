namespace _arduino3 {

  /* config */
  gpio_port_t* digital_pin_to_port[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    GPIO24_PORT, // pin 13
    NULL, NULL, NULL, NULL, NULL, NULL, NULL
  };
  uint8_t digital_pin_to_pad[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    GPIO24_PAD, // pin 13
    0, 0, 0, 0, 0, 0, 0
  };

  /* buffers */
  Mailbox mboxSerial;
  msg_t bufferSerial[SERIAL_BUFFER];

#include "arduino.cpp"
#include "arduino3.cpp"
}
