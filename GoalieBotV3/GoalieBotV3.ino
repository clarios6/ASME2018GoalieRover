/* Goalie code for ASME*/
#include <SPI.h>
#include <PS3BT.h>
#include <math.h>



//=====PIN DEFINING=====
const int m1a = 22; //upper left 1st motor
const int m1b = 23;
const int m2a = 28; //upper right 2nd motor
const int m2b = 29;
const int m3a = 36; //lower left 3rd motor
const int m3b = 37;
const int m4a = 44; //lower right 4th motor
const int m4b = 45;
const int m1P = 10; //Enable PWM pin for 1st motor
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
  Serial.print("Started");
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  
}

bool isConnected = false;
//int x;
//int y;
int octodrant; //angle of x and y from the positive x-axis

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
    
    if(PS3.getButtonPress()){
      
    } else if(PS3.getButtonPress()){
      
    } else if(PS3.getButtonPress()){
      
    } else
    */
    /*
     * =====ROTATIONAL / NO MOVEMENT=====
     */
      
    if (PS3.getButtonPress(L2)){ //rotate counter-clockwise at half speed
      rotateCounter();
      
    } else if (PS3.getButtonPress(R2)){ //rotate clockwise at half speed
      rotateClockwise();
      
    } else{
      /*
       * =====REGULAR MOVEMENT=====
       */
      if (PS3.getButtonPress(RIGHT)){         //right movement
        right();
        
      } else if (PS3.getButtonPress(UP)){     //forward movement
        forward();
        
      } else if (PS3.getButtonPress(LEFT)){  //Left Movement
        left();
  
      } else if (PS3.getButtonPress(DOWN)){  //Backwards Movement
        backwards();
      } 
       /*
       * =====OMNIDIRECTIONAL MOVEMENT=====
       */
        else if (PS3.getButtonPress(TRIANGLE)){ // Forward Right Movement
        forwardRight();
        
      } else if (PS3.getButtonPress(CIRCLE)){ // Forward Left Movement
        forwardLeft();
        
      } else if (PS3.getButtonPress(SQUARE)){ // Backward Left Movement
        backLeft();
        
      } else if (PS3.getButtonPress(TRIANGLE)){ // Backward Right Movement
        backRight();
      } else {
        neutral();
      }
      
    }
  }  
}

//=====MOTOR MOVEMENT FUNCTIONS=====
void neutral () {
  Serial.print("\nNeutral");
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, LOW);
}

void stopAll() {
  Serial.print("\nStop All");
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, LOW);
}

void backwards() {
  Serial.print("\nBackwards");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, HIGH);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, HIGH);
}

void forward() {
  Serial.print("\nForward");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, HIGH);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, HIGH);
  digitalWrite(m4b, LOW);
}

void left(){
  Serial.print("\nLeft");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, HIGH);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, HIGH);
}

void right(){
  Serial.print("\nRight");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, HIGH);
  digitalWrite(m4a, HIGH);
  digitalWrite(m4b, LOW);
}

void backRight(){
  Serial.print("\nBack Right");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, HIGH);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, LOW);
}

void backLeft() {
  Serial.print("\nBack Left");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, HIGH);
}

void forwardLeft() {
  Serial.print("\nForward Left");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, HIGH);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, LOW);
}

void forwardRight() {
  Serial.print("\nForward Right");
  analogWrite(m1P, 255);
  analogWrite(m2P, 255);
  analogWrite(m3P, 255);
  analogWrite(m4P, 255);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, HIGH);
  digitalWrite(m4b, LOW);
}

void rotateClockwise() {
  Serial.print("\nClockwise");
  analogWrite(m1P, 150);
  analogWrite(m2P, 150);
  analogWrite(m3P, 150);
  analogWrite(m4P, 150);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  digitalWrite(m3a, HIGH);
  digitalWrite(m3b, LOW);
  digitalWrite(m4a, LOW);
  digitalWrite(m4b, HIGH);
}

void rotateCounter() {
  Serial.print("\nCounter Clockwise");
  analogWrite(m1P, 150);
  analogWrite(m2P, 150);
  analogWrite(m3P, 150);
  analogWrite(m4P, 150);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  digitalWrite(m3a, LOW);
  digitalWrite(m3b, HIGH);
  digitalWrite(m4a, HIGH);
  digitalWrite(m4b, LOW);
}





