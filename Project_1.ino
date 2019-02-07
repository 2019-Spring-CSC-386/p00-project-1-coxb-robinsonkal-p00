#include <Wire.h>
int switchstate = 0;
int count = 0;
int readcheck = 0;
int timecheck = 0;
int oldminutes = 0;
int oldseconds = 0;
void setup() {
  // put your setup code here, to run once:
Wire.begin();
Serial.begin(9600);

Wire.beginTransmission(0x68); // address DS3231
Wire.write(0x0E); // select register
Wire.write(0b00011100); // write register bitmap, bit 7 is /EOSC
Wire.endTransmission();

}

void loop() {

  Wire.beginTransmission(0x68); // 0x68 is DS3231 device address
  Wire.write((byte)0); // start at register 0
  Wire.endTransmission();
  Wire.requestFrom(0x68, 3); // request three bytes (seconds, minutes, hours)
 switchstate = digitalRead(7);
 

 
  while(Wire.available())
  { 
    if (switchstate == LOW){
    readcheck++;
    }
    int seconds = Wire.read(); // get seconds
    int minutes = Wire.read(); // get minutes
    int hours = Wire.read();   // get hours
 
    seconds = (((seconds & 0b11110000)>>4)*10 + (seconds & 0b00001111)); // convert BCD to decimal
    minutes = (((minutes & 0b11110000)>>4)*10 + (minutes & 0b00001111)); // convert BCD to decimal
    hours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); // convert BCD to decimal (assume 24 hour mode)
 
    Serial.print(hours); Serial.print(":"); Serial.print(minutes); Serial.print(":"); Serial.print(seconds);
    Serial.println("");
    delay(1000);
    timecheck++;
    if (timecheck==1){
      oldminutes = minutes;
      oldseconds = seconds;
      }
    if (minutes>=oldminutes+1 && readcheck==0){
      tone(8,1000,500);
      Serial.println("Sound");
      }
    if (minutes>=oldminutes+1 && readcheck>0){
      timecheck = 0;
      readcheck = 0;
    }

  }

    


   
  
    

    




}
