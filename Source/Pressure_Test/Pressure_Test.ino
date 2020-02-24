#include<SoftwareSerial.h>
SoftwareSerial mySerial(8, 9); // RX, TX

int SensorPin1 = A0; //analog pin 0
int SensorPin2 = A1;
int SensorPin3 = A2;
int SensorPin4 = A3;
 
void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);

   pinMode(SensorPin1, INPUT);
   pinMode(SensorPin2, INPUT);
   pinMode(SensorPin3, INPUT);
   pinMode(SensorPin4, INPUT);
}
 
void loop(){
 int SensorReading1 = analogRead(SensorPin1); 
 int SensorReading2 = analogRead(SensorPin2); 
 int SensorReading3 = analogRead(SensorPin3); 
 int SensorReading4 = analogRead(SensorPin4);
  
  //int mfsr_r18 = map(SensorReading, 0, 1024, 0, 255);
  Serial.println(SensorReading1);
  Serial.println(SensorReading2);
  Serial.println(SensorReading3);
  Serial.println(SensorReading4);
  Serial.println(" ");

  mySerial.println(SensorReading1);
  mySerial.println(SensorReading2);
  mySerial.println(SensorReading3);
  mySerial.println(SensorReading4);
  mySerial.println(" ");

 
  delay(300); 
}
