#include "arduino.cpp"

int led = 13;
int status = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  if (status) {
    status = 0;
    digitalWrite(led, HIGH);
  } else {
    status = 1;
    digitalWrite(led, LOW);
  }
  //Serial.print("arduino2!\n\r");
  delay(1000);
}
