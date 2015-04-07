#define lights 9 // LED uses 9
#include <LiquidCrystal.h>

LiquidCrystal lcd(42, 44, 46, 48, 50, 52); // Liquid Crystal uses 42, 44, 46, 48, 50, 52

int LDR1, LDR2, LDR3, LDR4, LDR5; // sensor values
// calibration offsets
int leftOffset = 0, rightOffset = 0, centre = 0;

// this version uses 2 inputs for write
// pins for motor speed and direction
int speed_L = 4, speed_R = 11, direction_L1 = 5, direction_L2 = 6, direction_R1 = 12, direction_R2 = 13;
// starting speed and rotation offset
int startSpeed = 150, rotate = 30, max_speed = 220, min_speed = 180; // need to make sure increments are right (PWM between 0 and 255)
// sensor threshold
int threshold = 100;
// initial speeds of left and right motors
int left = startSpeed, right = startSpeed;

// passing lines
//int num_lines_passed = 0;
//int passed_line = 0;
//int passed_5_lines = 0; // this needs to be a 

void setup()
{
   Serial.begin(1200);
  Serial.print("Entering Setup\n");
  // LCD setup
  lcd.begin(16, 2);
  lcd.print("Lights on");
  lcd.setCursor(0, 1);
  
  // set the motor pins to outputs
  pinMode(lights, OUTPUT); // lights
  pinMode(speed_L, OUTPUT);
  pinMode(speed_R, OUTPUT);
  pinMode(direction_L1, OUTPUT);
  pinMode(direction_L2, OUTPUT);
  pinMode(direction_R1, OUTPUT);
  pinMode(direction_R2, OUTPUT);

  // Set up sensors
  digitalWrite(lights, HIGH); // lights on
  delay(100);
  // LDR1 and LDR2 are the ones in front.
  // LDR3 is the back left, LDR4 is the centre back, LDR5 is the right back  
  LDR1 = analogRead(0); // read the 5 photosensors
  LDR2 = analogRead(1);
  LDR3 = analogRead(2);
  LDR4 = analogRead(3);
  LDR5 = analogRead(4);

//  delay(30);
  digitalWrite(lights, HIGH); // lights on
  delay(100);
  // set motor direction to forward
  digitalWrite(direction_L1, HIGH);
  digitalWrite(direction_L2, LOW);
  digitalWrite(direction_R1, HIGH);
  digitalWrite(direction_R2, LOW);
  delay(500);
  left = startSpeed;
  right = startSpeed;
  // set speed of both motors
  analogWrite(speed_L,left);
  analogWrite(speed_R,right);
  

}

void loop() {
  // make both motors same speed
  Serial.print("Entering Loop\n");
  // read the sensors and add the offsets
  LDR1 = analogRead(0); // took out offsets
  LDR2 = analogRead(1);
  LDR3 = analogRead(2);
  LDR4 = analogRead(3);
  LDR5 = analogRead(4);

  // print sensor readings onto lcd
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(LDR1);
  lcd.print("|");
  lcd.print(LDR2);
  lcd.print("|");
lcd.setCursor(0,1);  
  lcd.print(LDR3);
  lcd.print("|");
  lcd.print(LDR4);
  lcd.print("|");
  lcd.print(LDR5);
lcd.setCursor(0,1);
//  lcd.clear();
  
  Serial.print("Top of Loop in main file");
  
  
  // passing line here
//  passed_line = sensing_passing_line(num_lines_passed, LDR1, LDR2, LDR3, LDR4, LDR5, threshold);
//  turn_left(left, right, speed_L, speed_R, startSpeed, rotate, passed_5_lines, passed_line);

    // line-following
    // if LDR3 is less than the centre sensor + threshold turn right
    if (LDR2 < (LDR4+threshold))
    {
   //   lcd.clear();
 
       if ( left < max_speed )
       {
          left = left + rotate; // change relative to previous speed
          //lcd.print("LV < Max");
       }
       if ( right > min_speed )
       {
          right = right - rotate;
          //lcd.print("RV > min");
       }
      lcd.print("R");
    }
  
  // if LDR1 is less than the centre sensor + threshold turn left
    else if (LDR1 < (LDR4 +threshold))
    {
 
    //    lcd.clear();
        if (left > min_speed)
        {
          left = left - rotate; // change relative to previous speed
      //    lcd.print("LV > min");
        }
        if (right < max_speed)
        {
          right = right + rotate;
      //    lcd.print("RV < max ");
        }
    
      lcd.print(" L");
    }
        // send the speed values to the motors
    analogWrite(speed_L,left);
    analogWrite(speed_R,right);
    
//    lcd.print(" S ");
    delay(50);
     lcd.clear();

  
}
