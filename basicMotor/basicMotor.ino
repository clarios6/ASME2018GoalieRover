//Includes the libraries you need
#include <Servo.h>

Servo main;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //apparently every file needs this
  Serial.print("Got past setup"); //prints out in console
  main.attach(10);
}




void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Loop");
  main.write(map(255, 0, 1023, 0, 180));
  delay(1000);  
  
}
