#define Rx 17
#define Tx 16
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"



int score=0;
Servo servoLeft;
Servo servoRight;
int t=500;
int qtipinL=47;
int qtipinM=51;
int qtipinR=52;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
int red=7;
int green=3;
int button=5;
int threshold;
int counter=0;
int coonter=0;
char ary[5]={'e','e','e','e','e'};
int lineFollow(){
  while(1){
  int ls=rcTime(qtipinL);
  int rs=rcTime(qtipinR);
  int ms=rcTime(qtipinM);
   if(ls>t && ms>t && rs>t){
    servoRight.write(1500);
    servoLeft.write(1500);
    delay(500);
    servoRight.write(1300); 
    servoLeft.write(1700);
    delay(400);
    servoRight.write(1500);
    servoLeft.write(1500);
    
    
    counter++;
    if(counter==6){
      
      servoRight.write(1700); 
      servoLeft.write(1300);
      delay(1500);
      servoRight.write(1500);
      servoLeft.write(1500);
      for(int i=0;i<5;i++){
        char outgoing=ary[i];
        Serial2.println(outgoing);
      }
      while(1);
    }
    return 0;
    servoRight.write(1300); 
    servoLeft.write(1700); 
    delay(300);
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
  return 0;
}
void sensing(){
  delay(3000);
  uint16_t r, g, b, c, colorTemp, lux;
    tcs.getRawData(&r, &g, &b, &c);
    // colorTemp = tcs.calculateColorTemperature(r, g, b);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);
    bool done=false;
    //Serial.println(r-g);
    //Serial.println(colorTemp);
      if(r-g>threshold){
        digitalWrite(red,HIGH);
        delay(100);
        ary[coonter]='E';
        coonter++;
        delay(1000);
        /*while(1){
          if(Serial2.available()){
            char incoming = Serial2.read();
            if(incoming=='D'){
              Serial2.println("!");
              score+=10;
              break;
            }
            else if(incoming=='d'){
              Serial2.println("%");
              break;
            }
            else if((incoming=='#')||(incoming=='%')||(incoming=='$')||(incoming=='!')){
                if(incoming=='!'){
                  score+=10;
                }
                break;
            }
          }
       */ 
        digitalWrite(red,LOW);
      }
      else{
        digitalWrite(green,HIGH);
        delay(100);
        ary[coonter]='e';
        coonter++;
        delay(1000);
        /*while(1){
          if(Serial2.available()){
            char incoming = Serial2.read();
            if(incoming=='D'){
              Serial2.println("$");
              break;
            }
            else if(incoming=='d'){
              Serial2.println("#");
              break;
            }
            else if((incoming=='#')||(incoming=='%')||(incoming=='$')||(incoming=='!')){
              if(incoming=='!'){
                  score+=10;
                }
                break;
            }
          }*/
        
        digitalWrite(green,LOW);
      }
      if(coonter==5){
        //delay(5000);
        servoRight.write(1700); 
        servoLeft.write(1300);
        delay(1500);
        servoRight.write(1500);
      servoLeft.write(1500);
      delay(2000);
      for(int i=0;i<5;i++){
        char outgoing=ary[i];
        Serial2.println(outgoing);
        Serial2.println(i);
        delay(2000);
      }
      while(1){
        if(Serial2.available()){
          char incoming=Serial2.read();
          if(incoming>='0' && incoming <='5'){
            Serial2.println('z');
            delay(2000);
            Serial2.println(incoming);
            delay(2000);
            int x=(int(incoming)-48)*10;
            //Serial3.println("             ");
            Serial2.println(x);
            delay(2000);
            Serial3.begin(9600);
            Serial3.write(12);       // ESC command
            Serial3.write(12); 
            Serial3.write("z");
            break;
          }
        }
      }
      while(1){
        }
      
      //Serial2.println(score);
      while(1);
      }
      
}

void setup() {
  int QTIPinL {};
  int QTIPinM {};
  int QTIPinR {};
  servoLeft.attach(11);                
  servoRight.attach(12);
  servoRight.write(1500);
   servoLeft.write(1500);
  Serial.begin(9600);
  Serial2.begin(9600);
  
  Serial2.println("Q");
  //Serial3.write("                                   ");
  //Serial3.write(12);       // ESC command
  //Serial3.write(12); 
  //Serial3.write("Score");
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(button,INPUT);
  while(digitalRead(button)!=HIGH);
  delay(1000);
  uint16_t r, g, b,c;
  tcs.getRawData(&r,&g,&b,&c);
  threshold=r-g;
  delay(500);
}

void loop() {
  
  // different if statements based on what is seen
  // compare to threshold
  // change servo speed accordingly
  lineFollow();
  
  sensing();


  
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
