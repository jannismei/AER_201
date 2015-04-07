#include <LiquidCrystal.h>

//LiquidCrystal lcd(42, 44, 46, 48, 50, 52); // Liquid Crystal uses 42, 44, 46, 48, 50, 52
// seems to have some internal compiling problem (with this computer) for
int LDR1, LDR2, LDR3, LDR4, LDR5; // sensor values
// sensor threshold
int threshold = 100;

// this version uses 2 inputs for write
// pins for motor speed and direction
int pin_speed_L = 4, pin_speed_R = 8, pin_direction_L1 = 5, pin_direction_L2 = 6, pin_direction_R1 = 9, pin_direction_R2 = 10;
// starting speed and rotation offset
int startSpeed_L = 160, startSpeed_R = 120, max_speed = 255, min_speed = 130, rotate = 30; // need to make sure increments are right (PWM between 0 and 255)
int speed_diff; // for differential function
// initial speeds of left and right motors
int left = startSpeed_L, right = startSpeed_R;
int angle = LDR1 - LDR2; // for differential function
int L_R_POS = LDR3 - LDR4;
int speed_Increment = -25*angle - L_R_POS;  
void setup()
{

/* call keypad function to get location of hoppers
maybe can use while loop (while row_A OR row_B, OR col_A, OR col_B ==0)
or use switch/button to choose when to start/stop
*/
/*
grid[row_A][col_A] = 7;
grid[row_B][col_B] = 7;
grid[row_S][col_S] = W;
*/


  Serial.begin(14400);
  Serial.print("Entering Setup\n");
  // LCD setup
//  lcd.begin(16, 2);
//  lcd.print("Lights on");
 // lcd.setCursor(0, 1);
  
  // set the motor pins to outputs
  pinMode(pin_speed_L, OUTPUT);
  pinMode(pin_speed_R, OUTPUT);
  pinMode(pin_direction_L1, OUTPUT);
  pinMode(pin_direction_L2, OUTPUT);
  pinMode(pin_direction_R1, OUTPUT);
  pinMode(pin_direction_R2, OUTPUT);

  // Reading IR Sensors
  delay(10);
  // LDR1 and LDR2 are the ones in front.
  // LDR3 is the back left, LDR4 is the centre back, LDR5 is the right back  
//  read_IR_sensors();
  
  // set motor direction to forward
  digitalWrite(pin_direction_L1, HIGH);
  digitalWrite(pin_direction_L2, LOW);
  digitalWrite(pin_direction_R1, HIGH);
  digitalWrite(pin_direction_R2, LOW);
  delay(50);
 
  // Turn Motors On
  left = startSpeed_L;
  right = startSpeed_R;
  analogWrite(pin_speed_L,left);   
  analogWrite(pin_speed_R,right);
//  delay(100);
  // up to here is checking motors
 
}

void loop() {
  // make both motors same speed
  Serial.print("Entering Loop\n");
 
  // read the sensors and add the offsets
 // read_IR_sensors();
  
 // left = 0;
 // right = 0;
 // analogWrite(pin_speed_L,left);   
 // analogWrite(pin_speed_R,right);
 // delay(5000);
 //lcd.print("GO");
    left = startSpeed_L;
  right = startSpeed_R;
  digitalWrite(pin_direction_L1, HIGH);
  digitalWrite(pin_direction_L2, LOW);
  digitalWrite(pin_direction_R1, HIGH);
  digitalWrite(pin_direction_R2, LOW);
  delay(50);
  analogWrite(pin_speed_L,left);   
 analogWrite(pin_speed_R,right);

  delay(50000);
 //  follow_line();

}
