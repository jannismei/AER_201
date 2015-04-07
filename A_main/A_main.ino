#include <LiquidCrystal.h>

LiquidCrystal lcd(42, 44, 46, 48, 50, 52); // Liquid Crystal uses 42, 44, 46, 48, 50, 52

int LDR1, LDR2, LDR3, LDR4, LDR5, LDRC1, LDRC2, LDRC3; // sensor values
// sensor threshold
int threshold = 100;

// this version uses 2 inputs for write
// pins for motor speed and direction
int pin_speed_L = 4, pin_speed_R = 8, pin_direction_L1 = 5, pin_direction_L2 = 6, pin_direction_R1 = 9, pin_direction_R2 = 10;
// starting speed and rotation offset
int startSpeed_L = 160, startSpeed_R = 120, max_speed = 255, min_speed = 20, rotate = 10; // need to make sure increments are right (PWM between 0 and 255)
int speed_diff; // for differential function
// initial speeds of left and right motors
int left = startSpeed_L, right = startSpeed_R;


// passing lines
char black1 = 0;
int num_lines_passed = 0;
int passed_line = 0;
int passed_2_lines = 0;
int num_lines_to_pass;

// grid values
int grid[10][11] = {0}; // [10] cols, [11] rows
int col_A, row_A, col_B, row_B;
int col_S, row_S, col_T, row_T, num_rows_to_pass, num_cols_to_pass;

// pullley stuff, need to check pins
int pin_speed_pulley = 13, pin_direction_pulley1 = 12, pin_direction_pulley2 = 11;
int pin_sensor = 22, sensor, mode, switch_up;
// pin 24 reads 1 if shovel is at bottom.
// pin 26 reads 1 if shovel at top
// pin 22 controls whether that circuit is on or off.

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
*
/*  col_S = 5; // testing cols and rows, testing 2 right turns
  col_T = 5;
  row_S = 8;
  row_T = 2;
*/
  // testing reversing (board_nav
  col_S = 1;
  row_S = 4;


  Serial.begin(4800);
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
  analogWrite(pin_speed_L,0);   
  analogWrite(pin_speed_R,0);
  // Reading IR Sensors
  delay(10);
  // LDR1 and LDR2 are the ones in front.
  // LDR3 is the back left, LDR4 is the centre back, LDR5 is the right back  
  read_IR_sensors();
  
  // set motor direction to forward
  forwards_direction();
  analogWrite(pin_speed_L,0);   
  analogWrite(pin_speed_R,0);
  delay(50);
 
  // Turn Motors On
  left = startSpeed_L;
  right = startSpeed_R;
  analogWrite(pin_speed_L,0);   
  analogWrite(pin_speed_R,0);
  lcd.print("about to start");
  delay(500);
  analogWrite(pin_speed_L,200);   
  analogWrite(pin_speed_R,200);
  lcd.print("ready to go");
  delay(50);
  analogWrite(pin_speed_L,left);   
  analogWrite(pin_speed_R,right);
  // up to here is checking motors
   lcd.print("going at regular speed");
   
   
  // set pulley motors
 
    pinMode(pin_speed_pulley, OUTPUT);
    pinMode(pin_direction_pulley1, OUTPUT);
    pinMode(pin_direction_pulley2, OUTPUT);
    digitalWrite(pin_direction_pulley1, HIGH);
    digitalWrite(pin_direction_pulley2, LOW); 
    //input_key(); // this function gets locations of hoppers
}

void loop() {
  // make both motors same speed
  Serial.print("Entering Loop\n");
 
  // read the sensors and add the offsets
  read_IR_sensors();
  
  // Call passing line here
  //passed_line = sensing_passing_line();
  
  //follow_line();
  //reverse_follow_line();
  board_navigation_algorithm();
  
 // navigation_algorithm(); // will need to take out follow_line when using this (nav_algo calls follow_line)  
//  print_grid();
  
  
  // these functions all have some delays in them, but they stop on their own
 /* hopper_enter();
  delay(1500);
  hopper_exit();
  delay(1500);
 // analogWrite(pin_speed_L,0);   
 // analogWrite(pin_speed_R,0);
 // delay(3000); */
  //lift_ball();
 // delay(5000);
 // arm_up();
 // drop_arm();
  
  
}
