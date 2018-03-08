/* Goalie code for ASME */
#include <SPI.h>
#include <PS3BT.h>
#include <math.h>

//Defining pins for the motors
const int m1a = 22; //upper left 1st motor
const int m1b = 23;
const int m2a = 28; //upper right 2nd motor
const int m2b = 29;
const int m3a = 36; //lower left 3rd motor
const int m3b = 37;
const int m4a = 44; //lower right 4th motor
const int m4b = 45;
const int m1P = 11; //Enable PWM pin for 1st motor
const int m2P = 8;  //Enable PWM pin for 2nd motor
const int m3P = 6;  //Enable PWM pin for 3rd motor
const int m4P = 4;  //Enable PWM pin for 4th motor

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

void setup() {
  Serial.begin(9600);    //initialize serial @ 9600 baudrate
  pinMode(m1a, OUTPUT);  //defining pins
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(m3a, OUTPUT);
  pinMode(m3b, OUTPUT);
  pinMode(m4a, OUTPUT);
  pinMode(m4b, OUTPUT);
  
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  
}

bool isConnected = false;
int x;
int y;
int angle; //angle of x and y from the positive x-axis

void loop() {
  Usb.Task();
  if(PS3.getButtonPress(PS)){
    isConnected = true;
  }
  if(isConnected){
    x = PS3.getAnalogHat(LeftHatX);
    y = PS3.getAnalogHat(LeftHatY);

    if(x < 5 && y < 5){
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, LOW);
      digitalWrite(m3a, LOW);
      digitalWrite(m3b, LOW);
      digitalWrite(m4a, LOW);
      digitalWrite(m4b, LOW);
    } else if(PS3.getButtonPress(L2)){ //rotate counter-clockwise at half speed
      
      analogWrite(m1P, 150);
      analogWrite(m2P, 150);
      analogWrite(m3P, 150);
      analogWrite(m4P, 150);
      Serial.print("\nCOUNTER-CLOCKWISE");
      digitalWrite(m1a, LOW);
      digitalWrite(m1b, HIGH);
      digitalWrite(m2a, HIGH);
      digitalWrite(m2b, LOW);
      digitalWrite(m3a, LOW);
      digitalWrite(m3b, HIGH);
      digitalWrite(m4a, HIGH);
      digitalWrite(m4b, LOW);
      
    } else if( PS3.getButtonPress(R2)){ //rotate clockwise at half speed
      analogWrite(m1P, 150);
      analogWrite(m2P, 150);
      analogWrite(m3P, 150);
      analogWrite(m4P, 150);
      Serial.print("\nCLOCKWISE");
      digitalWrite(m1a, HIGH);
      digitalWrite(m1b, LOW);
      digitalWrite(m2a, LOW);
      digitalWrite(m2b, HIGH);
      digitalWrite(m3a, HIGH);
      digitalWrite(m3b, LOW);
      digitalWrite(m4a, LOW);
      digitalWrite(m4b, HIGH);
      
    } else{ //Moves Toward Desired Location
       angle = getAngle(x, y);
       
    }
  }  
}

/* Finds the quadrant in which the coordinates x and y lie in
 * returns the appropriate quadrant number
 */
int findQuadrant(int x, int y){
  if( x > 0 && y >0 ){ //checks to see if in first quadrant
    return 1;
  } else if (x < 0 && y > 0){ //checks to see if in second quadrant
    return 2;
  } else if (x < 0 && y < 0){ //checks to see if in third quadrant
    return 3;
  } else { //defaults to fourth quadrant
    return 4;
  }
}


/* converts cartesian coordinates to just the polar angle in degrees, not radians
 * Adds 0.5 to each angle so that when it is cast to int it is rounded to the right angle
 */
int getAngle(int x, int y){
  int x2 = x - 127;
  int y2 = y - 127;
  double cTheta = atan(x2 / y2) * (360 / (2 * M_PI));
  int quadrant = findQuadrant(x2, y2);
  if(quadrant == 1 || quadrant == 5){
    cTheta += 0.5;
  } else if(quadrant == 2){
    cTheta += 180.5;
  } else if (quadrant == 3){
    cTheta += 180.5;
  } else{
    cTheta += 360.5;
  }
  int degree = (int)cTheta;
  return degree;
}

int getRadius(int x, int y){
  int x2 = x - 127;
  int y2 = y - 127;
  double radiusD = sqrt(pow(x2, 2) + pow(y2, 2)); 
}





