#include <Arduino.h>

const int motorPin = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
}

void loop() {
  digitalWrite(motorPin, HIGH); // Motoru çalıştır
  delay(3000);                 // 3 saniye bekle
  digitalWrite(motorPin, LOW);  // Motoru durdur
  delay(2000);
}
