#include <avr/io.h>

void setup() {

  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  TCCR1B = (TCCR1B & 0b11111000) | 0x02;
  OCR1A = 99;
  
}


void loop() {

  analogWrite(11, 0);
  analogWrite(12,100);
}
