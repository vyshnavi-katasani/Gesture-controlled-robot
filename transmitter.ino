#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <RF24.h>

MPU6050 mpu;
RF24 radio(9,10);    
const byte address[6]="00001";
int16_t a,b,c;
char command;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  mpu.getAcceleration(&a,&b,&c);
  if(a>15000){
    command='F';
  }
  else if(a<-15000){
    command='B';
  }
  else if(b>15000){
    command='L';
  }
  else if(b<-15000){
    command='R';
  }
  else{
    command='S';
  }
  radio.write(&command,sizeof(command));
  Serial.print("Command:");
  Serial.println(command);
  delay(100);
}
