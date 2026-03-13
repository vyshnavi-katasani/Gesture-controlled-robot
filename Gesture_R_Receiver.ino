#include <SPI.h>
#include <RF24.h>

RF24 radio(9,10);
const byte address[6]="00001";
char command;

int IN1 = 3;
int IN2 = 4;
int IN3 = 5;
int IN4 = 6;

void setup(){
  Serial.begin(9600);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
}

void loop() {
  if(radio.available()){
    radio.read(&command,sizeof(command));
    Serial.print("Received: ");
    Serial.println(command);

    if(command=='F'){
      forward();
    }
    else if(command=='B'){
      backward();
    }
    else if(command=='L'){
      left();
    }
    else if(command=='R'){
      right();
    }
    else if(command=='S'){
      stop();
    }
  }
}
void forward(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void backward(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void left(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void right(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}
void stop(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
