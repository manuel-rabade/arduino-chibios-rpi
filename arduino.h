#include <stdint.h>

#define HIGH 1
#define LOW  0

#define INPUT 0
#define OUTPUT 1

#define delay(millis) chThdSleepMilliseconds(millis)

/* digital */

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);

/* serial */

class Serial
{
 public:
  Serial(void);
  void begin(unsigned long);
} Serial;
