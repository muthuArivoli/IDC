
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Servo servoLeft;
Servo servoRight;
void setup() {
  // put your setup code here, to run once:
servoLeft.attach(11);                
  servoRight.attach(12);
}

void loop() {
  // put your main code here, to run repeatedly:
servoRight.write(1500);
   servoLeft.write(1500);
}
