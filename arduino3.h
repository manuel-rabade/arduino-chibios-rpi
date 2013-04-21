namespace _arduino3 {
  gpio_port_t* digital_pin_to_port[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    GPIO25_PORT, // pin 13
    NULL, NULL, NULL, NULL, NULL, NULL, NULL
  };
  uint8_t digital_pin_to_pad[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    GPIO25_PAD, // pin 13
    0, 0, 0, 0, 0, 0, 0
  };
#include "arduino3.cpp"
}
