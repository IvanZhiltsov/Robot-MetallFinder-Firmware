#include <Arduino.h>

const int LED = 2;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);  
}

void loop() {  
  delay(1000);  
  Serial.println("1");
  digitalWrite(LED, HIGH);  
  delay(1000);
  Serial.println("0");
  digitalWrite(LED, LOW);  
}  
