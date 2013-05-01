#define HIGH 1
#define LOW  0
#define NOT_INPUT -1

#define INPUT 0
#define OUTPUT 1

#define delay(millis) chThdSleepMilliseconds(millis)

/* digital */

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
int digitalRead(uint8_t);

/* serial */

#define SERIAL_BUFFER 24*3600

class Serial
{
 public:
  Serial(void);
  void begin(unsigned long);
  void print(const char *);
  void print(int, int = 10);
  void print(unsigned long, int);
} Serial;

struct _serialMsg
{
  systime_t timestamp;
  char *msg;
};

/* i2c */

#define I2C_BUFFER 32

class Wire
{
  private:
    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;
 public:
  Wire(void);
  void begin(void);
  void beginTransmission(uint8_t);
  uint8_t endTransmission(void);
  uint8_t requestFrom(uint8_t, uint8_t);
  virtual size_t write(uint8_t);
  virtual int read(void);
} Wire;
