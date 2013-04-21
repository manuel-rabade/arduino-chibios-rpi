namespace _arduino2 {
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
#include "arduino2.cpp"
}
