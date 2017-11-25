#include <Wire.h>

const int ledPIN = 13;
 
void setup() {
  pinMode(ledPIN , OUTPUT);  //definir pin como salida
}
 
void loop(){
  digitalWrite(ledPIN , HIGH);   // poner el Pin en HIGH
}
