namespace _arduino1 {
  gpio_port_t* digital_pin_to_port[] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    GPIO22_PORT, // pin 13
    NULL, NULL, NULL, NULL, NULL, NULL, NULL
  };
  uint8_t digital_pin_to_pad[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    GPIO22_PAD, // pin 13
    0, 0, 0, 0, 0, 0, 0
  };
#include "arduino1.cpp"
}
