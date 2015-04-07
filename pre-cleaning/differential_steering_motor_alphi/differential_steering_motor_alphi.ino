
// from alphi document
int E1 = 5; //M1 Speed Control
int E2 = 7; //M2 Speed Control
int M1 = 4; //M1 Direction Control
int M2 = 6; //M2 Direction Control
void motor(int leftSpeed, int rightSpeed) {
char lSpeed, rSpeed;
char lDir, rDir;
if (leftSpeed < 0) {
lSpeed = (char)
-
leftSpeed;
lDir = LOW;
}
else {
lSpeed = (char) leftSpeed;
lDir = HIGH;
}
if (rightSpeed < 0) {
rSpeed = (char)
-
rightSpeed;
rDir = LOW;
}
else {
rSpeed = (char) rightSpeed;
rDir = HIGH;
}
analogWrite (E1,lSpeed); //PWM Speed Control.
digitalWrite(M1,lDir);
analogWrite (E2,rSpeed);
digitalWrite(M2,rDir);
}
void setup(void)
{
int i;
for(i=4;i<=7;i++) {
pinMode(i, OUTPUT); //Set motor pin as output.
}
motor(0,0); //Stop both motors.
//Flash LED on Romeoboard to indicate start of program.
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);
delay(500);
digitalWrite(13, LOW);
delay(500); 
}

void loop(){
int motorSpeedLeft = 100;
int motorSpeedRight = 100;
int reverseDelay = 100;
int delayTime = 400;

}
