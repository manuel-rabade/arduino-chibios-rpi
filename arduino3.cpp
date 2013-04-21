#include "arduino.cpp"

int led = 13;
int button = 12;

void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  int i;
  if (digitalRead(button) == LOW) {
    for (i = 0; i < 3; i++) {
      digitalWrite(led, HIGH);
      delay(250);
      digitalWrite(led, LOW);
      delay(250);
    }
  }
  delay(100);
}
