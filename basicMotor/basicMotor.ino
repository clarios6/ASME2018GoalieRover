//Includes the libraries you need
#include <Servo.h>
#include <math.h>



Servo servMain;
int pos = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //apparently every file needs this
  Serial.print("Got past setup"); //prints out in console
  
}


int x;
int y;

double theta;

void loop() {
  delay(1000);
  x  = 5;
  y = 5;
  int angle = getAngle(x, y);
  Serial.print(angle);
  Serial.print("\n");
}

/*
 * Finds the quadrant in which the coordinates x and y lie in
 * returns the appropriate quadrant number
 */
int findQuadrant(int x, int y){
  if( x > 0 && y >0 ){ //checks to see if in first quadrant
    return 1;
  } else if (x < 0 && y > 0){ //checks to see if in second quadrant
    return 2;
  } else if (x < 0 && y < 0){ //checks to see if in third quadrant
    return 3;
  } else if (x > 0 && y < 0){ //checks to see if in fourth quadrant
    return 4;
  } else {
    return 5; // point lies on the origin
  }
}


/*
 * converts cartesian coordinates to just the polar angle in degrees, not radians
 * Adds 0.5 to each angle so that when it is cast to int it is rounded to the right angle
 */

int getAngle(int &x, int &y){
  int x2 = x - 127;
  int y2 = y - 127;
  theta = atan(x2 / y2) * (360 / (2 *M_PI));
  int quadrant = findQuadrant(x2, y2);
  if(quadrant == 1 || quadrant == 5){
    theta += 0.5;
  } else if(quadrant == 2){
    theta += 180.5;
  } else if (quadrant == 3){
    theta += 180.5;
  } else{
    theta += 360.5;
  }
  int degree = (int)theta;
  return degree;


}



