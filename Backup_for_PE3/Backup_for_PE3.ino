#include <LiquidCrystal.h>
#include <NewPing.h>
#include <Keypad.h>

LiquidCrystal lcd(42, 44, 46, 48, 50, 52); // Liquid Crystal uses 42, 44, 46, 48, 50, 52

int LDR1, LDR2, LDR3, LDR4, LDR5, LDRC1, LDRC2, LDRC3; // sensor values
// sensor threshold
int threshold = 300;
int stat_threshold = 20;
// this version uses 2 inputs for write
// pins for motor speed and direction
unsigned int pin_speed_L = 5, pin_speed_R = 8, pin_direction_L1 = 6, pin_direction_L2 = 7, pin_direction_R1 = 9, pin_direction_R2 = 10;
// starting speed and rotation offset
unsigned int startSpeed_L = 127, startSpeed_R = 120, max_speed = 255, min_speed = 20, rotate = 10; // need to make sure increments are right (PWM between 0 and 255) // 105 and 65
unsigned int slowSpeed_L = 103, slowSpeed_R = 103;
/* 255, 253---240, 230---215, 200---187, 170
152, 140---103, 100---75, 70---
*/
// need to figure out what combos of start speeds are right
// 100, 85
// 125, 110
// 145 and 105 not working anymore

int speed_diff; // for differential function

// initial speeds of left and right motors
int left = startSpeed_L, right = startSpeed_R;
int angle = LDR1 - LDR2; // calculating for differential function
int L_R_POS = LDR3 - LDR5;
int speed_Increment = angle/20 + L_R_POS/30;

// passing lines
char black1 = 0;
int num_lines_passed = 0;
int passed_line = 0;
int passed_2_lines = 0;
int num_lines_to_pass;

// grid values
int grid[10][11] = {0}; // [10] cols, [11] rows
int col_A, row_A, col_B, row_B;
char orientation_A, orientation_B;
int col_S, row_S, col_T, row_T, col_Cur, row_Cur, num_rows_to_pass, num_cols_to_pass;

// Ultrasonic and Sensing Hopper
int us_state = 0;
#define TRIGGER_PIN  30  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     32  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define US_ROUNDTRIP_MM 578      // Microseconds (uS) it takes sound to travel round-trip 100mm (200mm total), uses integer to save compiled code space.
#define offset 5 // distance from sensor to outside of casing
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int uS = 0, uS_1 = 0, uS_2 = 0, uS_3 = 0, uS_state = 0, first_leg = 70, mid_leg = 80;

#define TRIGGER_PIN_FRONT  33  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FRONT     35  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_FRONT 200 
NewPing sonar2(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE_FRONT); // NewPing setup of pins and maximum distance.
unsigned int uS_front = 0;

// KEYPAD Pins
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
byte rowPins[ROWS] = { 47, 49, 51, 53 };  // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 39,41, 43, 45 };  // Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.
// keypad pin 1 to arduino pin 9, keypad pin 2 to arduino pin 8, ... keypad pin 8 to arduino pin 2


// ARM/pullley stuff, need to check pins
unsigned int pin_speed_pulley = 2, pin_direction_pulley1 = 3, pin_direction_pulley2 = 4;
unsigned int pin_pulley_top = 24, pin_pulley_bottom = 26, sensor, mode, switch_up;
// pin 24 reads 1 if shovel is at bottom.
// pin 26 reads 1 if shovel at top
// pin 22 controls whether that circuit is on or off.

//Arm
unsigned int arm_high_pin = 24, arm_low_pin = 26;
unsigned int arm_on = 22;
unsigned int pin_speed_arm = 2, arm_D1 = 3, arm_D2 = 4;
int arm_high, arm_low, bottom, top;

//Board
unsigned int board_pin = 34;
unsigned int board_sensor, bs_prev, num_clicks = 0;

// timing
unsigned long time, time2, time3, start_time, uS_time, uS_logic_time, uS_front_time, pass_line_time;

// navigation
char orientation;
int nav_completion = 0;
int board_navigation_algorithm_section = 0;
int navigation_algorithm_section = 0;

void setup()
{
  grid[0][0] = 4; // set the # of balls in the corner hoppers
  grid[8][0] = 4; // corner hoppers have 4 balls each
  
/* call keypad function to get location of hoppers
maybe can use while loop (while row_A OR row_B, OR col_A, OR col_B ==0)
or use switch/button to choose when to start/stop
*/
/*
grid[row_A][col_A] = 7;
grid[row_B][col_B] = 7;
grid[row_S][col_S] = W;
*/
/*  col_S = 5; // testing cols and rows, testing 2 right turns

  row_S = 8;

*/
  // testing reversing (board_nav
  col_S = 3;
  row_S = 1; // row 7, col_4 not coded in
  col_Cur = 7;
  col_Cur = 2;
  col_T = 1;
  row_T = 4;
  
  Serial.begin(115200);
  Serial.print("Entering Setup\n");
  // LCD setup
  lcd.begin(16, 2);
  lcd.print("Lights on");
  lcd.setCursor(0, 1);
  
  // set the motor pins to outputs
  pinMode(pin_speed_L, OUTPUT);
  pinMode(pin_speed_R, OUTPUT);
  pinMode(pin_direction_L1, OUTPUT);
  pinMode(pin_direction_L2, OUTPUT);
  pinMode(pin_direction_R1, OUTPUT);
  pinMode(pin_direction_R2, OUTPUT);
  stop_motors();
  // Reading IR Sensors
  digitalWrite(38, HIGH);
  delay(10);
  // LDR1 and LDR2 are the ones in front.
  // LDR3 is the back left, LDR4 is the centre back, LDR5 is the right back  
  read_IR_sensors();
  
  //pulley
  pinMode(22, OUTPUT);
  pinMode(pin_pulley_top, INPUT);
  pinMode(pin_pulley_bottom, INPUT);
  pinMode(pin_speed_pulley, OUTPUT);
  pinMode(pin_direction_pulley1, OUTPUT);
  pinMode(pin_direction_pulley2, OUTPUT);
  digitalWrite(22, HIGH);
  
  // set motor direction to forward
  forwards_direction();
  stop_motors();
  delay(50);
 
  // Turn Motors On
  left = startSpeed_L;
  right = startSpeed_R;
  stop_motors();
  lcd.print("about to start");
  delay(500);
//  analogWrite(pin_speed_L,200);   
//  analogWrite(pin_speed_R,200);
  lcd.print("ready to go");
  delay(50);
//  analogWrite(pin_speed_L,left);   
//  analogWrite(pin_speed_R,right);
  // up to here is checking motors
  lcd.print("going at regular speed");
   
  // set pulley motors
 
  pinMode(pin_speed_pulley, OUTPUT);
  pinMode(pin_direction_pulley1, OUTPUT);
  pinMode(pin_direction_pulley2, OUTPUT);
  digitalWrite(pin_direction_pulley1, HIGH);
  digitalWrite(pin_direction_pulley2, LOW); 

  input_key(); // this function gets locations of hoppers

  start_time = millis();
  uS_time = millis();
  uS_logic_time = millis();
  pass_line_time = millis();
}

void loop() {

//testing timing
 time = millis();
/*  if ( (time - start_time) > 998)
  {
  start_time = millis();
    Serial.print("Time: "); 
     //prints time since program started
  Serial.println(time);
  
  }*/


  // make both motors same speed
 // Serial.println("Entering Loop\n");
//  Serial.print("Delay 5 seconds");
//delay(2000);
  // read the sensors and add the offsets
// read_IR_sensors();
//  board_navigation_algorithm();
//  follow_line();
//  sense_board_column();
 // ultrasonic();

 
  // This code (especially uS_logic) uses ultrasonic sensors to sense when you are passing
  //different legs of the hopper and determines when to call a certain turn function and
  //when to turn 
 // follow_line();
 // ultrasonic();
  //uS_logic();
  
  //turn_to_face_hopper();
  //stationary_turn_left();
  // Call passing line here
//  passed_line = sensing_passing_line();
    navigation_algorithm();
//  follow_line();
//  reverse_follow_line();
//if (0 == nav_completion)
//  {
//      if (0 == navigation_algorithm())
//      {
//         nav_completion = 1; 
//      }
//      ; // will need to take out follow_line when using this (nav_algo calls follow_line)  
//  }
 
//  else if (1 == nav_completion)
//  {
//    follow_line();
//    uS_logic();
//  }

//ultrasonic();
//  print_grid();

  // these functions all have some delays in them, but they stop on their own
 /* hopper_enter();
  delay(1500);
  
  delay(1500);
 // analogWrite(pin_speed_L,0);   
 // analogWrite(pin_speed_R,0);
 // delay(3000); */
  //   bottom = digitalRead(pin_pulley_bottom);
   //  Serial.print(" pin pulley bottom reading " );
   //  Serial.println(bottom);

// get_ball();

  
}
