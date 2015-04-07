Differential steering with continuous rotation servos and Arduino Uno
Version: 1.0
Date: January 2014
Author: Stan
Web-Site: http://42bots.com/
********************************************************************/
#include <Servo.h>

Servo LeftServo;
Servo RightServo;

// the control signal for the left servo
const int leftServoPin = 2;

// the control signal for the right servo
const int rightServoPin = 4;

void setup()
{
   LeftServo.attach(leftServoPin);
   RightServo.attach(rightServoPin);
}

void loop()
{
   //Drive forward for 3 seconds
   Drive(180, 0);
   delay(3000);

   //Drive in reverse for 3 seconds
   Drive(0, 180);
   delay(3000);

   //Rotate counterclockwise for 3 seconds
   Drive(0, 0);
   delay(3000);

   //Rotate clockwise for 3 seconds
   Drive(180, 180);
   delay(3000);
}
/*
Drive function. Sample calls:
 - (180, 0) for full forward
 - (0,180) for full reverse
 - (90, 90) for stop

Servos are mirrored on the chassis.
*/
void Drive(int leftServoSpeed, int rightServoSpeed) {

  if (leftServoSpeed < 0) {leftServoSpeed = 0;}     
  else if (leftServoSpeed > 180) {leftServoSpeed = 180;}

  if (rightServoSpeed < 0) {rightServoSpeed = 0;}     
  else if (rightServoSpeed > 180) {rightServoSpeed = 180;}

  //Send the command to the servos
  LeftServo.write(leftServoSpeed);
  RightServo.write(rightServoSpeed);
}
