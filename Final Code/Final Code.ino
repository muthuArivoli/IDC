//Import modules
#define Rx 17
#define Tx 16
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

Servo servoLeft;
Servo servoRight;
int t=500; //QTI threshold between white and black
int qtipinL=47;
int qtipinM=51;
int qtipinR=52;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
int red=7;
int green=3;
int button=5; //pins for LEDs and button
int threshold; //red minus green light
int counter=0; //number of hashes sensed
int coonter=0; //number of signs sensed
int objects = 0; //count number of red objects
int x = 0; //calculates score
char ary[5]={'e','e','e','e','e'}; //record colors in order

int lineFollow(){
  while(1){
  int ls=rcTime(qtipinL);
  int rs=rcTime(qtipinR);
  int ms=rcTime(qtipinM);
   if(ls>t && ms>t && rs>t){ //detect hash
    servoRight.write(1500);
    servoLeft.write(1500);
    delay(500);
    if (counter == 4){
      return 0; //don't move forward for the last hash
      }
    servoRight.write(1300); 
    servoLeft.write(1700);
    delay(400);
    servoRight.write(1500);
    servoLeft.write(1500);
    
    
    counter++;
    return 0;
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
}
void sensing(){
  delay(3000); //delay in order to read color sign
  uint16_t r, g, b, c, colorTemp, lux;
    tcs.getRawData(&r, &g, &b, &c);
    // colorTemp = tcs.calculateColorTemperature(r, g, b);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);
      if(r-g>threshold){ //sense red
        digitalWrite(red,HIGH);
        delay(100);
        ary[coonter]='E';
        coonter++;
        objects++;
        delay(1000);
        digitalWrite(red,LOW);
      }
      else{ //sense green
        digitalWrite(green,HIGH);
        delay(100);
        ary[coonter]='e';
        coonter++;
        delay(1000);
        digitalWrite(green,LOW);
      }
      if(coonter==5){ //after reading all signs
        servoRight.write(1700); 
        servoLeft.write(1300);
        delay(1500);
        servoRight.write(1500);
      servoLeft.write(1500);
      delay(4000);
      for(int i=0;i<5;i++){ //Begin sending out sign colors to Donald and Mindy
        char outgoing=ary[i];
        delay(1000);
        Serial2.println(outgoing);
        delay(2000);
      }
      while(1){
        if(Serial2.available()){
          char incoming=Serial2.read();
          if(incoming>='!' && incoming <='&'){ //Recieve score, 0-50 from D+M
            Serial2.println('z'); //score has been recieved
            delay(2000);
            x +=(int(incoming)-int('!'))*10; //deocde score
            Serial3.println(x); //print score
            break;
          }
        }
      }
            delay(3000); //get ready to recieve scores of Chaser + Beater 1, Seeker
            Serial2.println('@');
            int s = 0; //counts the number of people that have sent to us
            while(s < 2){
              if(Serial2.available()){
                char incoming = Serial2.read();
                //recieve score from Seeker
                //greater than sign catch Snitch, less than sign didn't catch Snitch
                if(incoming >= '<' && incoming <= '>'){
                  x += (int(incoming)-int('<'))*75;
                  s++;
                  }
                //recieve score from Chaser/Beater 1
                //decode message 
                else if(incoming>='!' && incoming <='&'){
                  x += (int(incoming) - int('!'))*10;
                  s++;
                }
                }
              }
              delay(3000);
              char finalscore = (char)((x/10)+65); //convert final score into char, A-Z
              Serial2.println(finalscore);
              Serial3.write(12);
              Serial3.write(12);
              Serial3.print(x);
              Serial3.write(" Score");
              Serial3.write(13);
              Serial3.print(objects);
              Serial3.write(" Red");
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
  Serial3.begin(9600);
  Serial2.println("Q");
  Serial3.write(12);
  Serial3.write(12);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(button,INPUT);
  while(digitalRead(button)!=HIGH); //do not start program until button is pushed
  delay(10000);
  uint16_t r, g, b,c;
  tcs.getRawData(&r,&g,&b,&c);
  threshold=r-g; //baseline for red - green color light in room
  delay(500);
}

void loop() {
  
  lineFollow(); //Let robot follow straight line until it hits a hash
  sensing(); //Sense object
  
  //After last object is sensed, send sensed colors to Chaser 2
  //Recieve scores from Chaser 2, Chaser/Beater 1, and Seeker, totals those scores up
  //Send score to all other bots


  
}

long rcTime(int pin) {
 pinMode(pin, OUTPUT);
 digitalWrite(pin, HIGH);
 delayMicroseconds(230);
 pinMode(pin, INPUT);
 digitalWrite(pin, LOW);
 long time = micros();
 while(digitalRead(pin)); 
 time = micros() - time; 
 return time;
} 
