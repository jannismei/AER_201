// center_hopper(), left_corner(), right_corner(), turn_to_face_hopper()

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
  if ('D' == orientation_A)
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
      if ( 0 == uS_logic)
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
      if ( 0 == uS_logic)
      { // this means we have finished approaching the hopper
        center_hopper_section = 0;
        return 0;
      }
    }
    
  }
  return 1;
}







int hopper_navigation_section = 0;
int left_corner() // Mar. 23, should be complete, just need to test this and right_corner()
{
  if (0 == hopper_navigation_section)
  {
    if ( (2 > col_Cur ) && ('W' == orientation) )
    {
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 7; // want this to be last column
      row_T = 5; // random number
      hopper_navigation_section = 1;
    }
    else
    {
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
    if ( (4 > row_Cur ) && ('A' == orientation) )
    {
      col_S = col_Cur;
      row_S = row_Cur;
      col_T = 5; // want this to be last column
      row_T = 7; // random number
      hopper_navigation_section = 1;
    }
    else
    {
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
  // can change turning condition from passed_5_lines to something else
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

// START TURNING

      analogWrite(pin_speed_L, 1);
      analogWrite(pin_speed_R, slowSpeed_R);
      
      if (0 == first_time_turn_left)
      { // If it is the first run-through of while loop while turning left
      // then wait a little before checking the IR sensors
        first_time_turn_left = 1;
        delay(1500);
      }
      
      read_IR_sensors();
      if ( (LDR5 + threshold <= LDR2) && (LDR3 + threshold <= LDR1) )// stop turning left when sense black
        {
          Serial.print("LDRC1: ");
          Serial.print(LDRC1);
          Serial.print(" LDRC3: ");
          Serial.print(LDRC3);
          Serial.print("\n stop turning left 1-1-1-1-1-1-1-1\n");
          break;
        }
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
