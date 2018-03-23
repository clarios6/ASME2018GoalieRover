/*
 * =====GOALIE CODE FOR CSULA ASME=====
 * Made by Carlos Larios-Solis with the
 * guidance of Adryel Arizaga
 */
#include <SPI.h>
#include <PS3BT.h>
#include <math.h>
#include <Servo.h>


/*
 * =====MOTOR SETUP INFO=====
 */
const byte mtrRF [3] = {22,23,10}; // Right-Front Motor pins
const byte mtrRB [3] = {29,28,8};  // Right Back Motor pins
const byte mtrLF [3] = {36,37,6};  // Left Front Motor pins
const byte mtrLB [3] = {44,45,4};  // Left Back Motor pinsmotor

/*
 * =====SERVO SETUP INFO=====
 */
const int leftServoPin = 3; //Left Servo Pin
const int rightServoPin = 2; //Right Servo Pin
int lServPos = 90;
int rServPos = 90;
int servSpeed = 10; //Servo speed
Servo leftServo;
Servo rightServo;

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

void setup() {
  Serial.begin(9600);    //initialize serial @ 9600 baudrate
  pinMode(mtrRF[0], OUTPUT); //Defining motor Pins
  pinMode(mtrRF[1], OUTPUT);
  
  pinMode(mtrRB[0], OUTPUT);
  pinMode(mtrRB[1], OUTPUT);
  
  pinMode(mtrLF[0], OUTPUT);
  pinMode(mtrLF[1], OUTPUT);

  pinMode(mtrLB[0], OUTPUT);
  pinMode(mtrLB[1], OUTPUT);

  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print("Started");
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  
}

bool isConnected = false;
//int x;
//int y;
//int octodrant; //angle of x and y from the positive x-axis

void loop() {
  Usb.Task();
  if(PS3.getButtonPress(PS)){
    isConnected = true;
  }
  if(isConnected){
    //x = PS3.getAnalogHat(LeftHatX) - 127;
    //y = PS3.getAnalogHat(LeftHatY) - 127;
    //octodrant = getOctodrant(x, y);


   /*
    * =====SERVO MOVEMENT=====
    */
    if(PS3.getButtonPress(TRIANGLE)){
      servoUp();
    } else if(PS3.getButtonPress(CROSS)){
      servoDown();
    }
    
    /*
     * =====ROTATIONALMOVEMENT=====
     */
      
    if (PS3.getButtonPress(L2)){ //rotate counter-clockwise at half speed
      rotateCounter();
      
    } else if (PS3.getButtonPress(R2)){ //rotate clockwise at half speed
      rotateClockwise();
      
    } else{
      /*
       * =====REGULAR MOVEMENT=====
       */
      if (PS3.getButtonPress(UP)){            //Forward movement

        if(PS3.getButtonPress(LEFT)){         //Forward Left Movement
          forwardLeft();
        } else if(PS3.getButtonPress(RIGHT)){ //Forward Right Movement
          forwardRight();
        } else {
          forward();
        }
      } else if (PS3.getButtonPress(DOWN)){   //Backward movement

        if(PS3.getButtonPress(LEFT)){         //Backward Left Movement
          backRight();
        } else if(PS3.getButtonPress(RIGHT)){ //Backward Right Movement
          backLeft();
        } else{
          backwards();
        }
      } else if (PS3.getButtonPress(LEFT)){   //Left Movement
        left();
  
      } else if (PS3.getButtonPress(RIGHT)){  //Right Movement
        right();
      }  else {
        stopAll();
      }
    }
  }  
}


/*
 * =====SERVO MOVEMENT FUNCTIONS=====
 */

void servoUp(){
  lServPos = incServo(lServPos);
  rServPos = lServPos;
  leftServo.write(lServPos);
  rightServo.write(rServPos);
}

void servoDown(){
  lServPos = decServo(lServPos);
  rServPos = lServPos;
  leftServo.write(lServPos);
  rightServo.write(rServPos);
}

int incServo(int pos){
  pos += servSpeed;
  if(pos > 180){
    pos = 180;
  }
  return pos;
}

int decServo(int pos){
  pos -= servSpeed;
  if(pos < 0){
    pos = 0;
  }
  return pos;
}

/*
 * =====MOTOR MOVEMENT FUNCTIONS=====
 */
void neutral () {
  Serial.print("\nNeutral");
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void stopAll() {
  Serial.print("\nStop All");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void backwards() {
  Serial.print("\nBackwards");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void forward() {
  Serial.print("\nForward");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

void left(){
  Serial.print("\nLeft");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void right(){
  Serial.print("\nRight");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

void backRight(){
  Serial.print("\nBack Right");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void backLeft() {
  Serial.print("\nBack Left");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void forwardLeft() {
  Serial.print("\nForward Left");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], LOW);
}

void forwardRight() {
  Serial.print("\nForward Right");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

void rotateClockwise() {
  Serial.print("\nClockwise");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], HIGH);
  digitalWrite(mtrRF[1], LOW);
  digitalWrite(mtrRB[0], HIGH);
  digitalWrite(mtrRB[1], LOW);
  digitalWrite(mtrLF[0], HIGH);
  digitalWrite(mtrLF[1], LOW);
  digitalWrite(mtrLB[0], HIGH);
  digitalWrite(mtrLB[1], LOW);
}

void rotateCounter() {
  Serial.print("\nCounter Clockwise");
  analogWrite(mtrRF[2], 255);
  analogWrite(mtrRB[2], 255);
  analogWrite(mtrLF[2], 255);
  analogWrite(mtrLB[2], 255);
  digitalWrite(mtrRF[0], LOW);
  digitalWrite(mtrRF[1], HIGH);
  digitalWrite(mtrRB[0], LOW);
  digitalWrite(mtrRB[1], HIGH);
  digitalWrite(mtrLF[0], LOW);
  digitalWrite(mtrLF[1], HIGH);
  digitalWrite(mtrLB[0], LOW);
  digitalWrite(mtrLB[1], HIGH);
}

/*
 * =====DEPRECIATED CODE=====
 */

int getOctodrant(int x, int y){
  int theta = getAngle(x, y);
  int oct = 0;
  if(theta >= 345 && theta <= 15){
    oct= 1;
  } else if(theta > 15 && theta < 75){
    oct = 2;
  } else if(theta >= 75 && theta <= 105){
    oct = 3;
  } else if(theta > 105 && theta < 165){
    oct = 4;
  } else if(theta >= 165 && theta <= 195){
    oct = 5;
  } else if(theta > 195 && theta < 255){
    oct = 6;
  } else if(theta >= 255 && theta <= 285){
    oct = 7;
  } else if(theta > 285 && theta < 345){
    oct = 8;
  }

  return oct;  
}


/* converts cartesian coordinates to just the polar angle in degrees, not radians
 * Adds 0.5 to each angle so that when it is cast to int it is rounded to the right angle
 */
int getAngle(int x, int y){
  double cTheta = atan(2 / 2) * (360 / (2 * M_PI));
  int quadrant = findQuadrant(x, y);
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

/* Finds the quadrant in which the coordinates x and y lie in
 *returns appropriate quadrant
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

int getRadius(int x, int y){
  double radiusD = sqrt(pow(x, 2) + pow(y, 2)); 
}



