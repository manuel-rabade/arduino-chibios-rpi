#include "adafruit_ads1015.cpp"

int led = 13;
Adafruit_ADS1115 ads1115(0x48);

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  ads1115.begin();
}

void loop() {
  int i, adc0, adc1, adc2, adc3;

  for (i = 0; i < 2; i++) {
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(led, LOW);
    delay(250);
  }

  // TODO: Fix I2C
  adc0 = 1;
  adc1 = 2;
  adc2 = 3;
  adc3 = 4;
  //adc0 = ads1115.readADC_SingleEnded(0);
  //adc1 = ads1115.readADC_SingleEnded(1);
  //adc2 = ads1115.readADC_SingleEnded(2);
  //adc3 = ads1115.readADC_SingleEnded(3);

  Serial.print("AIN0");
  Serial.print(adc0);
  Serial.print("AIN1");
  Serial.print(adc1);
  Serial.print("AIN2");
  Serial.print(adc2);
  Serial.print("AIN3");
  Serial.print(adc3);

  delay(20000);
}
