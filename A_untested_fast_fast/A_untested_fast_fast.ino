#include <LiquidCrystal.h>
#include <NewPing.h>
#include <Keypad.h>

LiquidCrystal lcd(42, 44, 46, 48, 50, 52); // Liquid Crystal uses 42, 44, 46, 48, 50, 52

int LDR1, LDR2, LDR3, LDR4, LDR5, LDRC1, LDRC2, LDRC3; // sensor values
// sensor threshold
int threshold = 100;
int stat_threshold = 20;

// MOTOR SPEED AND DIRECTION PINS
unsigned int pin_speed_L = 5, pin_speed_R = 8, pin_direction_L1 = 6, pin_direction_L2 = 7, pin_direction_R1 = 9, pin_direction_R2 = 10;
// starting speed and rotation offset
unsigned int travelSpeed_L = 157, travelSpeed_R = 150, startSpeed_L = 105, startSpeed_R = 100, max_speed = 255, min_speed = 20, rotate = 10; // need to make sure increments are right (PWM between 0 and 255) // 105 and 65
unsigned int slowSpeed_L = 65, slowSpeed_R = 63, mediumSpeed_L = 103, mediumSpeed_R= 100, highSpeed_L = 220; // Mar 24, changed to make corner_hopper work (was originally 103/103)
/* 255, 253---240, 230---215, 200---187, 170
152, 140---103, 100---75, 70---
*/
// need to figure out what combos of start speeds are right  // 100, 85 // 125, 110 // 145 and 105 not working anymore

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


// KEYPAD Pins
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
byte rowPins[ROWS] = { 47, 49, 51, 53 };  // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 39,41, 43, 45 };  // Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.
// keypad pin 1 to arduino pin 9, keypad pin 2 to arduino pin 8, ... keypad pin 8 to arduino pin 2


// Ultrasonic and Sensing Hopper
int us_state = 0;
#define TRIGGER_PIN  30  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     32  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 130 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define US_ROUNDTRIP_MM 578      // Microseconds (uS) it takes sound to travel round-trip 100mm (200mm total), uses integer to save compiled code space.
#define offset 5 // distance from sensor to outside of casing
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned int uS = 0, uS_1 = 0, uS_2 = 0, uS_3 = 0, uS_state = 0;
unsigned int first_leg = 70, mid_leg = 80;

#define TRIGGER_PIN_FRONT  31  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FRONT     33  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE_FRONT 80 
NewPing sonar2(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE_FRONT); // NewPing setup of pins and maximum distance.
unsigned int uS_front = 0, uS_1f = 0, uS_2f = 0, uS_3f = 0, uS_4f = 0, uS_5f = 0, uS_6f = 0;
unsigned int first_leg_corner = 60, mid_leg_corner = 80;


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
unsigned long find_line_time, time, time2, time3, start_time, uS_time, uS_logic_time, uS_front_time, pass_line_time;

// navigation
char orientation;
int nav_completion = 0;
int board_navigation_algorithm_section = 0;
int navigation_algorithm_section = 0;

int deposit_ball_section = 0;
int find_line_return = 0;

int loop_section = 0;

int went_to_left_corner = 0, went_to_right_corner = 0;
int returning_to_start_flag = 0;
int fast_moving_algo_flag = 0;
int sensing_passing_line_flag = 0;
int balls_in_left_corner = 4;
int balls_in_right_corner = 4;
int go_to_left_corner, go_to_right_corner;

int first_time_through_loop = 1;

void setup()
{
  grid[0][0] = 4; // set the # of balls in the corner hoppers
  grid[8][0] = 4; // corner hoppers have 4 balls each
  

  // testing reversing (board_nav
  col_S = 4; // for some reason, col_S = 3, row_S = 1, col_T = 2, row_T = 7 doesn't work, says fisrt should go 4 lines in 'A'
  row_S = 1; // row 7, col_4 not coded in
  col_Cur = 4;
  row_Cur = 1; // row 7, col_4 not coded in
  orientation = 'W';
  
  
  //orientation = 'A';
  
  //orientation_A = 'C';
  //col_A = 1, row_A = 6;
  
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

  //input_key(); // this function gets locations of hoppers

  start_time = millis();
  uS_time = millis();
  uS_front_time = millis();
  uS_logic_time = millis();
  pass_line_time = millis();
  go_to_left_corner = 1;


  fast_moving_algo_flag = 0;
/*  //special-- enables testing return circuit
  went_to_left_corner = 1;
  loop_section = 5;
  num_lines_to_pass = 1;
  */
  
}

void loop() 
{
  time = millis();
 
//Serial.print("loop_section: ");
//Serial.println(loop_section);
  if (0 == loop_section)
  {
     went_to_right_corner = 0;
     went_to_left_corner = 0;
     returning_to_start_flag = 0;
     sensing_passing_line_flag = 0;
     ///
     ///
     //
     
     if ( (balls_in_left_corner > 0) && (1 == go_to_left_corner) ) // go_to_left_corner is for testing only!
      {
          if (0 == left_corner_V2() ) // gets to left_corner and gets ball
          {
             //if the function returns 0, then the robot is in position to grab the ball, so also subtract 1 
            loop_section = 1;
            balls_in_left_corner = balls_in_left_corner - 1;
            went_to_left_corner = 1;

          }
      }
      
      else if ( (balls_in_right_corner > 0) && (1 == go_to_right_corner) )
      {
          if (0 == right_corner_V2() ) // gets to right_corner and gets ball
           {
              // if the function returns 0, then the robot is in position to grab the ball, so also subtract 1 
              loop_section = 1;
              balls_in_right_corner = balls_in_right_corner - 1;
              went_to_right_corner = 1;
              fast_moving_algo_flag = 0;
           }
           if ( 0 == balls_in_right_corner)
           {
              go_to_right_corner = 0; // if out of balls here, then go to left corner
              go_to_left_corner = 1;
              fast_moving_algo_flag = 0;
           }
      }

  }
  else if (1 == loop_section)
  {
    Serial.println("loop section 1");
      if ( 1 == find_line() ) // find the line and reset the starting and current coordinates
      {
        // left hopper
        loop_section = 2;
          if (1 == went_to_left_corner)
          {
                num_lines_to_pass = 1;
                print_grid();
          }
      }
  }
  else if (2 == loop_section)
  {

        if ( 1 == went_to_left_corner)
        {
        /*
        loop_section = 2; // actually does get us to 2, 2. Board nav code would get us to go up along col 2, as seen in video_76
        col_Cur = 2;      // thus we added turn_left and turn_right
        col_S = 2;        // when going to left hopper, is 2, 2
        row_Cur = 2;// when going to right hopper, gets us to col 7, row 2
        row_S = 2;    */
        
        /*
        forwards_direction();
        follow_line();
        delay(500);
        stop_motors(); */
           
            // all of this is a correction to get the robot to turn onto column 1
            if (0 == moving_algorithm() )
            {
             // delays here are just to stop

              Serial.println(" done finding line, so turn left first, then turn right");
              turn_left();
              update_position_after_left_turn();
              stop_motors();

              delay(1000);

              num_lines_to_pass = 1;
             //      turn_right();
        //      update_position_after_right_turn();  // might not need to turn right (board_nav may handle this)
              stop_motors();
              delay(500);
              col_Cur = 1;
              col_S = 1;
              row_Cur = 2;
              row_S = 2;

              loop_section = 3;
              lift_ball();
              lift_ball();
            }
            
      }
      else if ( 1 == went_to_right_corner)
      {
              loop_section = 3;
      }
      else
      {
            loop_section = 3;
      }

  }
  
  else if (3 == loop_section)
  {

        Serial.println(" in loop section 3, next loop section is depositing ball");
      if ( 1 == went_to_left_corner)
      {
//         if ( 0 == moving_algorithm_fast() ) //----                                                                 Took this out
        {
            analogWrite(pin_speed_L, 105); // bad stuff (because of delays and stuff, but it works, so leave it?
            analogWrite(pin_speed_R, 103);
            delay(700);                // 500 for 15 volts
            stop_motors();
            startSpeed_L = 200;
            startSpeed_R = 200;
            loop_section = 4;
        } 
      }
      else if ( 1 == went_to_right_corner)
      {
        // for right corner
        // actually does get us to 2, 2. Board nav code would get us to go up along col 2, as seen in video_76
        col_Cur = 7;      // thus we added turn_left and turn_right
        col_S = 7;        // when going to left hopper, is 2, 2
        row_Cur = 2;// when going to right hopper, gets us to col 7, row 2
        row_S = 2;  

        loop_section = 4;
        lift_ball();
        lift_ball();
      }
      else
      {
        loop_section = 4; 
      }

  }

else if (4 == loop_section)
{
       startSpeed_L = 103;       startSpeed_R = 100;
       if ( 0 == deposit_ball() ) // lift arm slightly, and go to board, and drop off ball
      // arm might be lifted too high
      {
        Serial.println("Just dropped the ball");
        loop_section = 5;  // reset loop_section here. may need to reset coordinates
        num_lines_to_pass = 1;
      } // something wrong with right corner_V2. The robot gets to 1, 1, and doesn't turn enough. Then, it starts driving off of the line, and never corrects itself. Could this be because the photosensors are broken?
 
}
  
  else if (5 == loop_section)
  {
       //  Serial.println("loop section  is 5 ");
      if ( 0 == moving_algorithm() )
      {
         Serial.println("moving algo is 0 ");
         loop_section = 6; // reset loop and coordinates now.
         row_Cur = 8;
         row_S = 8;
         col_Cur = 6;
         col_S = 6;
         print_grid();
         read_IR_sensors();
         startSpeed_L = 200;
         startSpeed_R = 200;
         if (0 == balls_in_right_corner) //--------------------April 6, changed so if done in right corner, then go to left corner
         {
           went_to_left_corner = 1;
           went_to_right_corner = 0;
         }
         if (1 == went_to_left_corner )
         {
           Serial.println("setting col_T and row_T to 7 and 1");
         // Maybe this is the problem?-----------------------------//April 6, set row_Cur and col_Cur to 8, 
         col_T = 7;
         row_T = 2;
         }
      }
  }
  // I think the function goes to section 6, then goes to section 0, then finds out that there's no balls left in right corner,
  // so calls left corner function, but hasn't reset properly
  
  
  else if ( (6 == loop_section ) && ( 1 == first_time_through_loop )  )
  {
      // if first time through, then will have gone to left corner hopper, so we want to go to right corner hopper
      // the next couple times until we run out of balls there.
       go_to_left_corner = 0;
       go_to_right_corner = 1; // go to right corner for 4 times.
       loop_section = 0;
       first_time_through_loop = 0;
       fast_moving_algo_flag = 1;
  }
  else if ( 6 == loop_section )
  {
    //Serial.println("loop section 6");

    returning_to_start_flag = 1;
    fast_moving_algo_flag = 1;
    if (1 == went_to_left_corner )
    {
       if ( 0 == navigation_algorithm() ) // get to col 7, row 2
       {
          loop_section = 7;
          print_grid(); 
       }  
    }
    else if ( 1 == went_to_right_corner )
    {
        loop_section = 7;
    }
    else
    {
        loop_section = 7; 
    }
  }
  else if (7 == loop_section)
  {
      if (1 == went_to_left_corner) 
      //April 6: This weird stuff was created a while ago and was used to handle some weird turning to get us to the left corner
      // is this why we get stuck?
      {
        turn_right();
        stop_motors();
        delay(500);
        follow_line();
        num_lines_to_pass = 1;
        read_IR_sensors();
      }
      loop_section = 8; 
  }
  else if (8 == loop_section)
  {
    Serial.println("moving algo is 8 ");
    if (1 == went_to_left_corner)
    {
//       if (0 == moving_algorithm_fast() ) // don't seem to need this
       {
          Serial.println("moving algo is 8 ");
          sensing_passing_line_flag = 1;
          Serial.println("sensing_passing_line_flag is 1");
          turn_left();
          stop_motors();
          delay(500);
          num_lines_to_pass = 1;
          loop_section = 9;
          row_S = 2;              // Put this here April 6 to better reflect its actual position
          row_Cur = 2;
          col_S = 6;
          col_Cur = 6;
       }
    }
    else if (1 == went_to_right_corner)
    {
      
          loop_section = 9;
    }
    else
    {
          loop_section = 9;
    }
  }
  else if (9 == loop_section)
  {
     if (1 == went_to_left_corner)
     {
         if (0 == moving_algorithm() )
         {
           Serial.println("loop_section9");
            stop_motors();
            turn_right();
            row_S = 1;
            col_S = 4;
            row_Cur = 1;
            col_Cur = 4;
            loop_section = 0;
         }
  
     }
     else if (1 == went_to_right_corner)
     {
          loop_section = 0;
     }
     else
     {
          loop_section = 0;
     }
  }
}



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
//  ultrasonic();
  //uS_logic();
  
  //turn_to_face_hopper();
  //stationary_turn_left();
  // Call passing line here
//  passed_line = sensing_passing_line();
//  follow_line();
//  reverse_follow_line();
//Serial.println("turning left in 2 seconds");
//delay(2000);



// PE3
// deposit_ball();
// get_ball();
//right_corner();
//uS_logic_corner();
/*
if (0 == nav_completion)
  {
      if (0 == navigation_algorithm())
      {
         nav_completion = 1;
         Serial.println("done navigating");
      }
      ; // will need to take out follow_line when using this (nav_algo calls follow_line)  
  }
  */

//center_hopper();

/*
if (find_line_return == 0){
  find_line_return = find_line();
}
else{
  follow_line();
}
*/


/*  // this is for the central hopper in d postion
if (0 == nav_completion)
  {
      if (0 == navigation_algorithm())
      {
         nav_completion = 1; 
      }
      ; // will need to take out follow_line when using this (nav_algo calls follow_line)  
  }
  
  else if (1 == nav_completion)
  {
    follow_line();
    uS_logic();
  }*/

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
