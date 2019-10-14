
#include <Servo.h>
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(11);                
  servoRight.attach(12);
  // put your setup code here, to run once:
  Serial3.begin(9600);
  Serial3.write(12);
  Serial3.println(40);
  servoRight.write(1700); 
        servoLeft.write(1300);
        delay(1500);
        servoRight.write(1500);
      servoLeft.write(1500);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  Serial3.println(50);
}
