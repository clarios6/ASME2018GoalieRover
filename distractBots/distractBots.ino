#include <Servo.h>

// =====DEFINE SERVO SETTINGS=====
Servo leftServo;
Servo rightServo;
int lServPin = 8;
int rServPin = 9;
int leftPos = 90;
int rightPos = 90;
int servSpeed = 10;

//=====DATA READ BY BLUTOOTH
int i = 0;
char data;

void setup() {
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  leftServo.attach(lServPin);
  rightServo.attach(lServPin);
}
void loop() {
  
  while(Serial.available() > 0){
    data = Serial.read();
    if (data == 'F' && i != 1){           //Forward
      leftPos = incServo(leftPos);
      rightPos = incServo(rightPos);
    } else if (data == 'B' && i != 1){    //Backward
      leftPos = decServo(leftPos);
      rightPos = decServo(rightPos);
    } else if (data == 'R' && i != 1){    //Right
      leftPos = decServo(leftPos);
      rightPos = incServo(rightPos);
    } else if (data == 'L' && i != 1){     //Left
      leftPos = incServo(leftPos);
      rightPos = decServo(rightPos);
    }
    
    leftServo.write(leftPos);
    rightServo.write(rightPos);
  }
}

//=====SERVO MOVEMENT CALC=====

int incServo(int pos){ //Forward
  pos += servSpeed;
  if(pos > 180){
    pos = 180;
  } else if (pos < 0){
    pos = 0;
  }
  return pos;
}

int decServo(int pos){ //Backward
  pos -= servSpeed;
  if(pos > 180){
    pos = 180;
  } else if (pos < 0){
    pos = 0;
  }
  return pos;
}
