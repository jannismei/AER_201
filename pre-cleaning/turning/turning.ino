// pins for motor speed and direction
// pin 345, and 789
int speed1 = 3, speed2 = 9, direction1 = 5, direction2 = 7;
int direction1_1 = 4, direction2_1 = 8;
// starting speed
int startSpeed = 255;

// initial speeds of left and right motors
int left = startSpeed, right = startSpeed;

void setup()
{
// set the motor pins to outputs
pinMode(speed1, OUTPUT);
pinMode(speed2, OUTPUT);
pinMode(direction1, OUTPUT);
pinMode(direction2, OUTPUT);

// set motor direction to forward
digitalWrite(direction1, HIGH);
digitalWrite(direction1_1, LOW); // apparently need two inputs to direction

digitalWrite(direction2, HIGH);
digitalWrite(direction2_1, LOW); // apparently need two inputs to direction
// set speed of both motors
analogWrite(speed1,left);
analogWrite(speed2,right);
left = startSpeed;
right = startSpeed;
delay(750);
//going forward for delay time set below

}
void loop() {
// make both motors same speed

digitalWrite(direction2, LOW); // change so direction2 goes low
digitalWrite(direction2_1, HIGH); // apparently need two inputs to direction
//delay(160000);
digitalWrite(direction1, LOW); // change so direction2 goes low
digitalWrite(direction1_1, HIGH); // apparently need two inputs to direction
//going backward for delay time set below
delay(750);

digitalWrite(direction2, HIGH);
digitalWrite(direction2_1, LOW); // apparently need two inputs to direction
// turn for 3 seconds
delay(3000);

digitalWrite(direction1, HIGH); // change so direction2 goes low
digitalWrite(direction1_1, LOW); // apparently need two inputs to direction

digitalWrite(direction2, LOW);
digitalWrite(direction2_1, HIGH); // apparently need two inputs to direction

// turn for 3 seconds
delay(3000);
digitalWrite(direction1, HIGH);
digitalWrite(direction1_1, LOW); // apparently need two inputs to direction

digitalWrite(direction2, LOW);
digitalWrite(direction2_1, HIGH); // apparently need two inputs to direction
delay(750);

}
