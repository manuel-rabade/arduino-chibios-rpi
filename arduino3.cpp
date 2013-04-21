#include "arduino.cpp"

int led = 13;
int status = 0;

void setup() {
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
  delay(100);
}
