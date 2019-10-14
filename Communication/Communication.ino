#define Rx 17
#define Tx 16

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(5,INPUT);
  delay(500);
}

void loop() {
  if(digitalRead(5)==HIGH) {
    char outgoing = 'a';//Serial.read();
    digitalWrite(3,HIGH);
    Serial2.print(outgoing);
    delay(1000);
    
  }
  if (Serial2.available()) {
    char incoming = Serial2.read();
    Serial.println(incoming);
    digitalWrite(7,HIGH);
    delay(1000);
  }
  digitalWrite(3,LOW);
  digitalWrite(7,LOW);
  
  
  delay(50);
}
