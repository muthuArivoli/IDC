#include <Servo.h>
#include <SoftwareSerial.h>

Servo servoLeft;
Servo servoRight;
int t=500;
int qtipinL=47;
int qtipinM=51;
int qtipinR=52;

int counter=0;
void setup() {
  int QTIPinL {};
  int QTIPinM {};
  int QTIPinR {};
  servoLeft.attach(11);                
  servoRight.attach(12);
  Serial.begin(9600);
}

void loop() {
  // different if statements based on what is seen
  // compare to threshold
  // change servo speed accordingly
  int ls=rcTime(qtipinL);
  int rs=rcTime(qtipinR);
  int ms=rcTime(qtipinM);

  Serial.println(ls);
  Serial.println(rs);
  Serial.println(ms);

  if(ls>t && ms>t && rs>t){
    servoRight.write(1500);
    servoLeft.write(1500);
    delay(3000);
    counter++;
    //if(counter==7){
      //delay(10000000000);
    //}
    servoRight.write(1300); 
    servoLeft.write(1700); 
    delay(500);
  }
  if(ls>t && ms>t && rs<t){
    servoRight.write(1300); 
    servoLeft.write(1300); 
  }
  if(ls>t && ms<t && rs>t){
    servoRight.write(1300);
    servoLeft.write(1300);
  }
  if(ls>t && ms<t && rs<t){
    servoRight.write(1300); 
    servoLeft.write(1500); 
  }
  if(ls<t && ms>t && rs>t){
    servoRight.write(1700); 
    servoLeft.write(1700); 
  }
  if(ls<t && ms>t && rs<t){
    servoRight.write(1300); 
    servoLeft.write(1700); 
  }
  if(ls<t && ms<t && rs>t){
    servoRight.write(1500); 
    servoLeft.write(1700); 
  }
  if(ls<t && ms<t && rs<t){
    servoRight.write(1300);
    servoLeft.write(1300);
  }
  delay(50);
}

long rcTime(int pin) {
 pinMode(pin, OUTPUT);
 digitalWrite(pin, HIGH);
 delayMicroseconds(230);
 pinMode(pin, INPUT);
 digitalWrite(pin, LOW); long
 time = micros();
 while(digitalRead(pin)); 
 time = micros() - time; 
 return time;
} 
