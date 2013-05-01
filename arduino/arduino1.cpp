int led = 13;
int button = 12;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  if (digitalRead(button) == LOW) {
    Serial.print("button");
    digitalWrite(led, HIGH);
    delay(250);
    digitalWrite(led, LOW);
    delay(150);
  }
  delay(100);
}
