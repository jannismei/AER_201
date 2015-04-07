// center_hopper(), left_corner()_V2, right_corner()_V2, find_line();
// delays: turn_to_face_hopper()

// corner_hopper() runs through only once (using delays), and handles getting a ball out of the corner hopper, given 
// that the robot is in the right position (7, 1 for right corner, and 1, 1 for left corner)



// Many delays in turn_to_face hopper
int center_hopper_section = 0;

int center_hopper() // assume there is only 1 hopper (hopper A)
{
/*  1. Check if D orientation or C orientation (D means two legs on upper row, C means 2 legs on lower row)
    2. Check what section of board the robot is in
    3. If the robot would need 3 turns to get to the optimal location, then set up a temporary terminal location
        Then navigate there, and set the optimal location = to the terminal location
    4. Else if the robot will need 2 or fewer turns, then go straight to the optimal location
  */
  if ('E' == orientation_A)
  {
    if ( (0 == center_hopper_section) && (col_Cur > 6) && (row_Cur > 2) )
    {// need to set temporary terminal location
      col_T = 1;
      row_T = 4;
      center_hopper_section = 1;
    }
    else if (0 == center_hopper_section)
    { // this means we can directly go to the coordinates 2 rows above, and 1 column to left
    // of the hopper
      col_T = col_A - 1;
      row_T = row_A + 2;
      center_hopper_section = 5;
      // when done call uS_logic; When done, set center_hopper_section = 0;
    }
    else if ( 1 == center_hopper_section)
    {
       if ( 0 == navigation_algorithm() )
       {
         center_hopper_section = 2; // this means we've reached our temporary destination
       }// the next step is to set the coordinates 2 rows above, and 1 column to left
    // of the hopper
    }
    else if ( 2 == center_hopper_section )
    {
      // set the coordinates 2 rows above, and 1 column to left
    // of the hopper
      col_T = col_A - 1;
      row_T = row_A + 2;
      center_hopper_section = 5;
    }
    
    else if (5 == center_hopper_section)
    {  // this means navigate to final destination
       if ( 0 == navigation_algorithm() )
       {
         center_hopper_section = 10; // this means we've reached our final destination
       }
    }
  
    else if (10 == center_hopper_section)
    { // this means we've reached our final destination and can call uS_logic
      if ( 0 == uS_logic() )
      { // this means we have finished approaching the hopper
        center_hopper_section = 0;
        return 0;
      }
    }
    
  }
  else if ('C' == orientation_A)
  {
    if ( (0 == center_hopper_section) && (col_Cur < 3) && (row_Cur < 7) )
    {
      col_T = 7;
      row_T = 5;
      center_hopper_section = 1;
    }
    else if (0 == center_hopper_section)
    { // this means we can directly go to the coordinates 2 rows above, and 1 column to left
    // of the hopper
      col_T = col_A + 1;
      row_T = row_A - 2;
      center_hopper_section = 5;
      // when done call uS_logic; When done, set center_hopper_section = 0;
    }
    else if ( 1 == center_hopper_section)
    {
       if ( 0 == navigation_algorithm() )
       {
         center_hopper_section = 2; // this means we've reached our temporary destination
       }// the next step is to set the coordinates 2 rows above, and 1 column to left
    // of the hopper
    }
    else if ( 2 == center_hopper_section )
    {
      // set the coordinates 2 rows above, and 1 column to left
    // of the hopper
      col_T = col_A + 1;
      row_T = row_A - 2;
      center_hopper_section = 5;
    }
    else if (5 == center_hopper_section)
    {  // this means navigate to final destination
       if ( 0 == navigation_algorithm() )
       {
         center_hopper_section = 10; // this means we've reached our final destination
       }
    }
    else if (10 == center_hopper_section)
    { // this means we've reached our final destination and can call uS_logic
      if ( 0 == uS_logic () )
      { // this means we have finished approaching the hopper
        center_hopper_section = 0;
        return 0;
      }
    }
    
  }
  return 1;
}

void corner_hopper()
{
    Serial.println("In Corner_hopper, turning left");
    turn_left_no_delay();
    delay(2500); // turn left for this amount of time
    stop_motors();
    Serial.println("stop turning left");
    delay(250);  // there should not be any delay here
    Serial.println("entering hopper");
    hopper_enter(); // this only sets motor values
    delay(500); // this is how long the robot goes in for.
    stop_motors();
    Serial.println("STOP_MOTORS, call get_ball next, almost done corner_hopper");
    get_ball();
    return;
}

int hopper_navigation_section = 0;


int left_corner_V2()
{
  // call this infinitely many times
  // returns 0 when done, returns 1 when not done
//  Serial.print("\n calling left_corner_V2\n");
  if (0 == hopper_navigation_section)
  {
    if ( (2 > col_Cur ) && ('N' == orientation) )
    {
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 7; // want this to be last column
      row_T = 5; // random number
      hopper_navigation_section = 1;
    }
    else
    {
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 1; // just set the end coordinates where
      row_T = 1; // we want to go, and go to the navigation algorithm
      hopper_navigation_section = 1;
    }
  }
  else if ( 1 == hopper_navigation_section )
  {
    if ( 0 == navigation_algorithm() ) 
    { // this means done navigating, so go to next section
      hopper_navigation_section = 2;
    }
  }
  else if ( 2 == hopper_navigation_section )
  {
    if ( (1 == col_T) && (1 == row_T) )
    { // if reached left corner, call corner_hopper, which gets the ball
        drop_arm();
        corner_hopper();
        hopper_navigation_section = 0;
        Serial.print("returning 0 !!__11");
        return 0;
    }
   else if ( (1 != col_T) || (1 != row_T) )
   { // if done navigating, but not at left corner, then set
    // new ending coordinates at col_T = 2, then go to section 1
      col_T = 1;
      row_T = 1;
      hopper_navigation_section = 1;
    }
  }  
//  Serial.println("\n returning 1");
 return 1;   
}

int right_corner_V2()
{
//  Serial.println("right_corner funtion is called");
  if (0 == hopper_navigation_section)
  {
    if ( (3 > row_Cur ) && ('W' == orientation) )
    {
      Serial.println("setting interim terminal coordinates");
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 5; // want this to be last column
      row_T = 7; // random number
      hopper_navigation_section = 1;
    }
    else
    {
      Serial.println("setting final terminal coordinates");
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 7; // just set the end coordinates where
      row_T = 1; // we want to go, and go to the navigation algorithm
      hopper_navigation_section = 1;
    }
  }
  else if ( 1 == hopper_navigation_section )
  {
    if ( 0 == navigation_algorithm() ) 
    { // this means done navigating, so go to next section
      hopper_navigation_section = 2;
      Serial.println("done navigating in corner function");
    }
  }
  else if ( 2 == hopper_navigation_section )
  {
    if ( (7 == col_T) && (1 == row_T) )
    { // if reached right corner, then call corner_hopper()
    // which gets the ball from the corner hopper, and reset everything, and return
        drop_arm();
        corner_hopper();
        hopper_navigation_section = 0;
        Serial.println("Right_Corner_V2 returning 0 next");
        return 0;
    }
   else if ( (7 != col_T) || (1 != row_T) )
   { // if done navigating, but not at left corner, then set
    // new ending coordinates at col_T = 2, then go to section 1
      col_T = 7;
      row_T = 1;
      hopper_navigation_section = 1;
    }
  }  
 return 1; 
  
  
}



int left_corner() // Mar. 23, should be complete, just need to test this and right_corner()
{
  if (0 == hopper_navigation_section)
  {
    if ( (2 > col_Cur ) && ('N' == orientation) )
    {
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 7; // want this to be last column
      row_T = 5; // random number
      hopper_navigation_section = 1;
    }
    else
    {
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 2; // just set the end coordinates where
      row_T = 1; // we want to go, and go to the navigation algorithm
      hopper_navigation_section = 1;
    }
  }
  else if ( 1 == hopper_navigation_section )
  {
    if ( 0 == navigation_algorithm() ) 
    { // this means done navigating, so go to next section
      hopper_navigation_section = 2;
    }
  }
  else if ( 2 == hopper_navigation_section )
  {
    if ( (2 == col_T) && (1 == row_T) )
    { // if reached left corner, call approach_left_corner()
      if(0 ==  uS_logic_corner() )
      { // uS_logic_corner() returns 0, then it is done, so this function is also done
        hopper_navigation_section = 0;
        return 0;
      }
    }
   else if ( (2 != col_T) || (1 != row_T) )
   { // if done navigating, but not at left corner, then set
    // new ending coordinates at col_T = 2, then go to section 1
      col_T = 2;
      row_T = 1;
      hopper_navigation_section = 1;
    }
  }  
 return 1; 
}

int right_corner()
{
  if (0 == hopper_navigation_section)
  {
    if ( (3 > row_Cur ) && ('W' == orientation) )
    {
      Serial.println("setting interim terminal coordinates");
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 5; // want this to be last column
      row_T = 7; // random number
      hopper_navigation_section = 1;
    }
    else
    {
      Serial.println("setting final terminal coordinates");
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 7; // just set the end coordinates where
      row_T = 2; // we want to go, and go to the navigation algorithm
      hopper_navigation_section = 1;
    }
  }
  else if ( 1 == hopper_navigation_section )
  {
    if ( 0 == navigation_algorithm() ) 
    { // this means done navigating, so go to next section
      hopper_navigation_section = 2;
      Serial.println("done navigating in corner function");
    }
  }
  else if ( 2 == hopper_navigation_section )
  {
    if ( (7 == col_T) && (2 == row_T) )
    { // if reached left corner, then finish, and call approach_left_corner()
      if(0 ==  uS_logic_corner() )
      { // uS_logic_corner() returns 0, then it is done, so this function is also done
        hopper_navigation_section = 0;
        return 0;
      }
    }
   else if ( (7 != col_T) || (2 != row_T) )
   { // if done navigating, but not at left corner, then set
    // new ending coordinates at col_T = 2, then go to section 1
      col_T = 7;
      row_T = 2;
      hopper_navigation_section = 1;
    }
  }  
 return 1; 
}


//March 16
// custom threshold here

//left motor stay still, right motor go backwards

// This code has a long while loop, which means that nothing can be done while turning left

  // to turn left, slow down gradually
  // can change turning condition from passed_5_lines to something else // DELETE this line
int turn_to_face_hopper()
{
  int end_delay = 1000;
  int startSpeed_L = 145, startSpeed_R = 105;
  int threshold = 200; // custom threshold here
  int first_time_turn_left = 0;
  Serial.print("inside stationary turn_left function");

  while( 0 != left)
    { 
      read_IR_sensors();
      Serial.print("passed line, so turn left!--!--!--!\n");
      Serial.print("speed L is ");
      Serial.print(pin_speed_L);      
      digitalWrite(pin_direction_L1, HIGH);
      digitalWrite(pin_direction_L2, LOW);
      digitalWrite(pin_direction_R1, LOW);
      digitalWrite(pin_direction_R2, HIGH);

      forwards_direction();
// START TURNING

      analogWrite(pin_speed_R, 1);
      analogWrite(pin_speed_L, slowSpeed_L);
      //analogWrite(pin_speed_L, 1);
      //analogWrite(pin_speed_R, slowSpeed_R);
      
      if (0 == first_time_turn_left)
      { // If it is the first run-through of while loop while turning left
      // then wait a little before checking the IR sensors
        first_time_turn_left = 1;
        delay(1500);
      }
      
      read_IR_sensors();
      ultrasonic_front();
      if ( (uS_front < 15 ) && (uS_front != 0) )
      {
          Serial.print("us_front measures ");
          Serial.println(uS_front);
          Serial.print("\n stop turning left 1-1-1-1-1-1-1-1\n");
          break; 
      }
     /* if ( (LDR5 + threshold <= LDR2) && (LDR3 + threshold <= LDR1) )// stop turning left when sense black
        {
          Serial.print("LDRC1: ");
          Serial.print(LDRC1);
          Serial.print(" LDRC3: ");
          Serial.print(LDRC3);
          Serial.print("\n stop turning left 1-1-1-1-1-1-1-1\n");
          break;
        }*/
   }
      
    Serial.print("STOP TURNING LEFT--!--!--!");
    stop_motors();
      
    forwards_direction();
    while (ultrasonic_front() > 13)
    {
      //ultrasonic_front(); unnecessary, because already called in while statement
      analogWrite(pin_speed_L, startSpeed_L);
      analogWrite(pin_speed_R, startSpeed_R);
    }
    stop_motors();
    delay(end_delay);
    return 0;
}


int find_line_state = 0;
int positioning_delay = 500; // if motors get slower (less voltage, these delays should all increase)
int sensor_delay = 1000;
int clear_delay = 500;

int find_line(){
  //4 states
  //0: Time delay
  //1: Drive backwards with sensors OFF
  //2: Read center sensors wait for black
  //3: Rotate robot
  //4: 
  if (find_line_state == 0){ //determine timestamp for when the function enters
    Serial.println("State 0");
    find_line_time = 0;
    find_line_time = millis();
    Serial.println("find_line_time: ");
    Serial.println(find_line_time);
    Serial.println("millis: ");
    Serial.println(millis());
    stop_motors();
    find_line_state = 1;
  }
  
  else if (find_line_state == 1){ //delay for a time of time_delay before the motors stop moving back
    Serial.println(millis() - find_line_time);
    analogWrite(pin_speed_L, 255);
    analogWrite(pin_speed_R, 50);
    if ((millis() - find_line_time) > sensor_delay){ ///////Is this sensor delay? was previously time_delay
      find_line_state = 2;
      
    }
    Serial.println("State 1");
  }  
  else if (find_line_state == 2){ //move back
    backwards_direction();
    analogWrite(pin_speed_L, 103);
    analogWrite(pin_speed_R, 80);
    
    Serial.println("State 2");
    
    if ((millis() - find_line_time) > positioning_delay){
      find_line_state = 3;
    }
  }  
  else if (find_line_state == 3){ //read sensors
     read_IR_sensors();
     Serial.println("State 3");
     if (LDRC2 < (LDR1 - threshold) || LDRC2 < (LDR2 - threshold)){
       stop_motors();
       find_line_state = 4;
     }
  }   
  else if (find_line_state == 4){
    //stationary turn right
    Serial.println("State 4");
    digitalWrite(pin_direction_L1, HIGH);
    digitalWrite(pin_direction_L2, LOW);
    digitalWrite(pin_direction_R1, LOW);
    digitalWrite(pin_direction_R2, HIGH);
    
    analogWrite(pin_speed_L, 103);
    analogWrite(pin_speed_R, 100);
    
    read_IR_sensors();
    
    if ((LDR4 < ( LDR3 - threshold ) && LDR4 < (LDR5 - threshold)) || (LDR4 < ( LDR3 - threshold ) && LDR4 < (LDR5 - threshold))){
      find_line_state = 5;
      find_line_time = millis();
      Serial.println("Going to State 5");
    }
  }
  else if (find_line_state == 5){
    analogWrite(pin_speed_L, 103);
    analogWrite(pin_speed_R, 100);
    if (millis() - find_line_time > clear_delay){
      find_line_state = 6;
      Serial.print("Going to state 6\n");
    }
  } 
  else if (find_line_state == 6){
    analogWrite(pin_speed_L, 75);
    analogWrite(pin_speed_R, 70);
    
    read_IR_sensors();
    
    if ((LDR4 < ( LDR3 - threshold ) && LDR4 < (LDR5 - threshold)) || (LDR4 < ( LDR3 - threshold ) && LDR4 < (LDR5 - threshold))){
      delay(400);
      stop_motors();
      forwards_direction();      // MAY NEED TO TAKE THIS OUT
      find_line_state = 0;
      Serial.println("done finding line");
      return 1;
      
    }
  }
  
  return 0;
  Serial.println("Function exit");
}
  



// This code has a long while loop, which means that nothing can be done while turning left

  // to turn right, slow down gradually
  // can change turning condition from passed_5_lines to something else
/*int stationary_turn_right()
             
{
  int first_time_turn_right = 0;
  Serial.print("inside turn_right function");



    while( 0 != right)
      { 
      read_IR_sensors();
      Serial.print("passed line, so turn right!--!--!--!\n");
      Serial.print("speed L is ");
      Serial.print(pin_speed_R);
  digitalWrite(pin_direction_L1, HIGH);
  digitalWrite(pin_direction_L2, LOW);
  digitalWrite(pin_direction_R1, LOW);
  digitalWrite(pin_direction_R2, HIGH);
      analogWrite(pin_speed_R , startSpeed_R);
      //analogWrite(speed2,right);
      
      if (0 == first_time_turn_right)
      { // If it is the first run-through of while loop while turning right
      // then wait a little before checking the IR sensors
        first_time_turn_right = 1;
        delay(1500);
      }
      
      read_IR_sensors(); // may need to change to LDR4
        if (LDRC2 + threshold <= LDRC3) // stop turning right when sense black
        {
          Serial.print("LDRC2: ");
          Serial.print(LDRC2);
          Serial.print(" LDRC3: ");
          Serial.print(LDRC3);
          Serial.print("\n stop turning right 1-1-1-1-1-1-1-1\n");
          break;
        }
      }
      
      Serial.print("STOP TURNING right--!--!--!");
      analogWrite(pin_speed_R, startSpeed_R);
      stop_motors();
  return 0;
}*/
