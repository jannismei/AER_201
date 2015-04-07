// sense_board_column(),  board_navigation_algorithm(), forwards_direction(), backwards_direction()
// these have delays: deposit_ball, 
//



// many delays here
void sense_board_column()
{
  board_sensor = digitalRead(board_pin);
  Serial.print(" board approach sensor ");
  Serial.println(board_sensor);

  if ( (0 == bs_prev) && (1 == board_sensor) )
  {
  /* only gets into loop if previous value of board sensor was 0
  AND current value of board sensor is 1 */
    num_clicks = num_clicks + 1; 
  }
    bs_prev = board_sensor; //update value of bs_prev with board sensor
  Serial.print("num_clicks: ");
  Serial.print(num_clicks);
}

// March 17th, doesn't control which column of the board to drop the ball in
// Have multiple delays in here
long unsigned int deposit_ball_time;


int deposit_ball()
{
  /* This code requires the robot to have 
  acquired the ball and gotten onto a grid point.
  This code returns 0 if it is complete, and returns 1 otherwise.
  */
  if (0 == deposit_ball_section)
  { 
    // lift the arm slightly so that when the robot 
    // reaches row 8 and turns, the arm does not hit the
    // wall at the edge of the playing area.
    //drop_arm();
//    lift_ball();
//    lift_ball(); //----------------------------------------took out these 2 lift_balls
//    lift_ball();
    deposit_ball_section = 1;
  }
  else if ( (1 == deposit_ball_section) && (0 == board_navigation_algorithm() ) )
  {
    // if 0 = board_nav_algo, then completed the board navigation
    // so go to next state
    deposit_ball_section = 2;
    deposit_ball_time = millis();
  }
  else if (2 == deposit_ball_section )
  {
    // now the robot is at the board, so can deposit the ball
    // 1. go further along the game board
    // 2. stop
    // 3. lift the arm
    // 4. drop the arm
    Serial.println(" despoit_Ball section 2");
    if (deposit_ball_time - time > 1000)
    {
       Serial.println(" despoit_Ball section 3");
       deposit_ball_section = 3; 
    }
    else
    {
       variable_speed_follow_line(startSpeed_L, startSpeed_R);
    }
  }
  else if (3 == deposit_ball_section)
  {
    analogWrite(pin_speed_L, 0);
    analogWrite(pin_speed_R, 0);
    arm_up();  
    delay(1000);
    drop_arm();
    deposit_ball_section = 0;
    return 0;
  }
  
  return 1;
}


int board_navigation_algorithm()
{
  int propagation_delay = 0;
  int delayval = 2000;//30000; // this delay value is so that robot stops after done nav
  
  // return 0 if complete
  // return 1 if not complete
  
  // Serial.println("Entering Gameboard Navigation Algorithm\n");
  
  forwards_direction();
  
  if ( (col_S > 4) && (row_S > 6) ) // case 1
  { 
      if ( 0 == board_navigation_algorithm_section)
      {
        orientation = 'E';
        update_starting_position();
        forwards_direction();
        delay(propagation_delay); // might be 0
        num_cols_to_pass = 7 - col_S; // don't need extra - 1 for red line 
        num_lines_to_pass = num_cols_to_pass;
        Serial.print("Pass this many lines: ");
        Serial.println(num_lines_to_pass);
        board_navigation_algorithm_section = 1; // means go to next section next time you run through this code
      }
    
    else if ( ( 1 == board_navigation_algorithm_section) && (0 == moving_algorithm() ) )
      { 
        turn_right();
        passed_line = 0;
        board_navigation_algorithm_section = 2;
      }
    else if ( 2 == board_navigation_algorithm_section)
      { // can actually include this with the section above
        update_position_after_right_turn();
        num_rows_to_pass = row_S - 2 - 1; // extra -1 for manual correction
        num_lines_to_pass = num_rows_to_pass;
        Serial.print("Pass this many lines: ");
        Serial.println(num_lines_to_pass);  
        board_navigation_algorithm_section = 3;
      }
    else if ( (3 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )
     { 
        turn_right();
        passed_line = 0;
        board_navigation_algorithm_section = 4;
     }
    else if ( 4 == board_navigation_algorithm_section)
     {
        update_position_after_right_turn();
        num_cols_to_pass = 7- 1 - 1 - 1; // exxtra -1 for manual correction, extra -1 for red line
        num_lines_to_pass = num_cols_to_pass;
        Serial.print("Pass this many lines: ");
        Serial.println(num_lines_to_pass);
        board_navigation_algorithm_section = 5;
     }
    else if ( (5 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )    
    {
        turn_right();
        passed_line = 0;
        board_navigation_algorithm_section = 6;
    }
    else if ( 6 == board_navigation_algorithm_section)
    {
        update_position_after_right_turn();
        num_rows_to_pass = 8 - 2 - 1; // extra -1 for manual correction    
        num_lines_to_pass = num_rows_to_pass;
        Serial.print("Pass this many lines: ");
        Serial.println(num_lines_to_pass);
        board_navigation_algorithm_section = 7;  
    }
    else if ( (7 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )    
    {
      turn_right();
      passed_line = 0;
      board_navigation_algorithm_section = 8;  
    }
    else if ( 8 == board_navigation_algorithm_section)
    {
      update_position_after_right_turn();
      num_cols_to_pass = 4 -1 - 1 - 1;    // -1 is manual correction, extra -1 for red line
      num_lines_to_pass = num_cols_to_pass;
      Serial.print("Pass this many lines: ");
      Serial.println(num_lines_to_pass);
      board_navigation_algorithm_section = 9;  
    }
    else if ( (9 == board_navigation_algorithm_section) && (0 == moving_algorithm_fast() )  )        
    {    
      Serial.println("S, STOPPPP");
      stop_motors();
      update_ending_position();
      delay(delayval);
      board_navigation_algorithm_section = 0;  
      return 0;
    }
    return 1; // end this case
    /*
    // set motor direction to backwards
    backwards_direction();
    delay(propagation_delay);  
    Serial.println("Pass COLS, going backwards");
                                               // 0. choose to follow rows or columns first
    num_cols_to_pass = col_S - 3;     // 1. calculate number rows needed to go
    num_lines_to_pass = num_cols_to_pass; // 2. calculate number lines to go
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);  
    moving_algorithm();                   // 3. move that number of lines
    Serial.println("S, STOPPPP");                  // 4. if need to turn, then turn. 5. move number of lines. 6. turn
    stop_motors();
    delay(delayval); */
  }
  else if ( (col_S < 4) && (row_S > 6) )  // THIS CONDITION maybe right?
  {    // case 2
    if ( 0 == board_navigation_algorithm_section)
      {
        orientation = 'E';
        update_starting_position();
        forwards_direction();
        delay(propagation_delay); // time for signals to propagate
        Serial.println("Pass COLS, going forward");                  
        num_cols_to_pass = 3 - col_S;    // not right?
        num_lines_to_pass = num_cols_to_pass;
        Serial.println("Pass this many lines: ");
        Serial.println(num_lines_to_pass);  
        board_navigation_algorithm_section = 1; // means go to next section next time you run through this code
      }
     else if ( ( 1 == board_navigation_algorithm_section) && (0 == moving_algorithm() ) )
      { 
       Serial.println("S, STOPPPP");
       stop_motors();
       update_ending_position();
       delay(delayval); 
       board_navigation_algorithm_section = 0;  
       return 0;
    }
    return 1;
  }// end case
  
 else if ( (col_S > 6) && (row_S > 2) && (row_S < 7) ) 
  { // case 4
    
    if ( 0 == board_navigation_algorithm_section)
    {
      forwards_direction();
      orientation = 'S';
      update_starting_position();
      delay(propagation_delay);
      num_rows_to_pass = row_S - 2;
      num_lines_to_pass = num_rows_to_pass;
      Serial.println("Pass this many lines: ");
      Serial.println(num_lines_to_pass);  
      board_navigation_algorithm_section = 1; // means go to next section next time you run through this code
    }
    
    else if ( ( 1 == board_navigation_algorithm_section) && (0 == moving_algorithm() ) )
    { 
      turn_right();
      passed_line = 0;
      board_navigation_algorithm_section = 2;
     }
    else if ( 2 == board_navigation_algorithm_section)
     {
      update_position_after_right_turn();
      num_cols_to_pass = 7 - 1 - 1 - 1; // extra -1 for manual correction, extra -1 for red line
      num_lines_to_pass = num_cols_to_pass;
      Serial.println("Pass this many lines: ");
      Serial.println(num_lines_to_pass);  
      board_navigation_algorithm_section = 3;
     }
    else if ( (3 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )
     { 
      turn_right();
      passed_line = 0;
      board_navigation_algorithm_section = 4;
     }
    else if ( 4 == board_navigation_algorithm_section)
     {
      update_position_after_right_turn();
      num_rows_to_pass = 8 - 2 - 1; // extra -1 for manual correction
      num_lines_to_pass = num_rows_to_pass;
      Serial.print("Pass this many lines: ");
      Serial.println(num_lines_to_pass);
      board_navigation_algorithm_section = 5;
     }
    else if ( (5 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )    
    {
      turn_right();
      passed_line = 0;
      board_navigation_algorithm_section = 6;
    }
    else if ( 6 == board_navigation_algorithm_section)
    {
      update_position_after_right_turn();
      num_cols_to_pass = 4 - 1 - 1 - 1; // extra -1 for manual correction, extra -1 for red line
      num_lines_to_pass = num_cols_to_pass;
      Serial.println("Pass this many lines: ");
      Serial.println(num_lines_to_pass);  
      board_navigation_algorithm_section = 7;  
    }
    else if ( (7 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )    
    {
      Serial.println("S, STOPPPP");
      stop_motors();
      update_ending_position();
      delay(delayval); 
      board_navigation_algorithm_section = 0;  
      return 0;
    }
    return 1;
 }// end case
    // last line that is passed in first part of reversing is messed. line following after turn is messsed. consider utilizing center sensors for line following?   
      // set motor direction to backwards
      /* Serial.println("reverse, turn, reverse");
       backwards_direction();
       delay(propagation_delay);
       num_rows_to_pass = 9 - row_S;
       num_lines_to_pass = num_rows_to_pass;
       Serial.println("Pass this many lines: ");
       Serial.println(num_lines_to_pass);
       moving_algorithm();        
       turn_right();       
       num_cols_to_pass = col_S - 4 - 1;    // -1 is manual correction
       num_lines_to_pass = num_cols_to_pass;
       Serial.println("Pass this many lines: ");
       Serial.println(num_lines_to_pass);
       moving_algorithm();        
       Serial.println("S, STOPPPP");
       stop_motors();
       delay(delayval); 
  */
    
 else if ( (col_S < 2) && (row_S < 7) && (row_S > 2) ) // case 3
  {
    if ( 0 == board_navigation_algorithm_section)
      {
       orientation = 'N';
       update_starting_position();
       forwards_direction();
       delay(propagation_delay);
       num_rows_to_pass = 8 - row_S;
       num_lines_to_pass = num_rows_to_pass;
       Serial.println("Pass this many lines: ");
       Serial.println(num_lines_to_pass);
       board_navigation_algorithm_section = 1; // means go to next section next time you run through this code
      }
     else if ( ( 1 == board_navigation_algorithm_section) && (0 == moving_algorithm() ) )
      {    
       turn_right();       
       passed_line = 0;
       board_navigation_algorithm_section = 2;
      }
      else if ( 2 == board_navigation_algorithm_section)
      {
       update_position_after_right_turn();
       num_cols_to_pass = 4 - 1 - 1 - 1;    // -1 is manual correction ////////////////////////////////EXTRA -1 for red line
       num_lines_to_pass = num_cols_to_pass;
       Serial.print("Pass this many lines: ");
       Serial.println(num_lines_to_pass);
       board_navigation_algorithm_section = 3;
      }
      else if ( (3 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )
      {     
       Serial.println("S, STOPPPP");
       stop_motors();
       update_ending_position();
       delay(delayval);
       board_navigation_algorithm_section = 0;  
       return 0;
    }
    return 1;
  } // end case
  
 else if ( (col_S < 5) && (row_S < 3) ) // can make col_S < 6 // case 5
  {
    if ( 0 == board_navigation_algorithm_section)
    {
      orientation = 'W';
      update_starting_position();
      forwards_direction();
      delay(propagation_delay);
      num_cols_to_pass = col_S - 1; // don't need extra - 1 for red line -------------------------------IT SEEMS LIKE WE NEED TO REMOVE THIS -1
      num_lines_to_pass = num_cols_to_pass;
      Serial.println("Pass this many lines: ");
      Serial.println(num_lines_to_pass);    
      board_navigation_algorithm_section = 1; // means go to next section next time you run through this code
    }
    else if ( ( 1 == board_navigation_algorithm_section) && (0 == moving_algorithm() ) )
    {
      turn_right();
      passed_line = 0;
      board_navigation_algorithm_section = 2;
     }
    else if ( 2 == board_navigation_algorithm_section)
     {
      update_position_after_right_turn();
      num_rows_to_pass = 8 - row_S -1; // -1 is manual correction ---------------
      num_lines_to_pass = num_rows_to_pass;
      Serial.println("Pass this many lines: ");
      Serial.println(num_lines_to_pass);
      board_navigation_algorithm_section = 3;
     }
    else if ( (3 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )
     {   
      turn_right();       
      passed_line = 0;
      board_navigation_algorithm_section = 4;
     }
    else if ( 4 == board_navigation_algorithm_section)
     {
      update_position_after_right_turn();
      num_cols_to_pass = 4 - 1 - 1;    // -1 is manual correction, extra -1 for red line ---- took out -1
      num_lines_to_pass = num_cols_to_pass;
      Serial.print("Pass this many lines: ");
      Serial.println(num_lines_to_pass);
      board_navigation_algorithm_section = 5;
     }
    else if ( (5 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )    // NOTE, using MOVING ALGORITHM FAST
     {   
      Serial.println("S, STOPPPP");
      stop_motors();
      update_ending_position();
      delay(delayval);
      board_navigation_algorithm_section = 0;  
      return 0;
    }
    return 1;
  }  // end board navigation case
  
  else if ( (col_S > 4) && (row_S < 3) ) // case 6
  {
    if ( 0 == board_navigation_algorithm_section)
    {
      orientation = 'W';
      update_starting_position();
      forwards_direction();
      delay(propagation_delay);
      num_cols_to_pass = col_S - 1 - 1; // SECOND -1 FOR RED LINE
      num_lines_to_pass = num_cols_to_pass;
      Serial.println("Pass this many lines: ");
      Serial.println(num_lines_to_pass);   
      board_navigation_algorithm_section = 1; // means go to next section next time you run through this code
    }
    else if ( ( 1 == board_navigation_algorithm_section) && (0 == moving_algorithm_fast() ) )
    {
      turn_right();
      passed_line = 0; // NOT SURE WHY THIS IS HERE?  -- WAS MISSING TURN_RIGHT
      board_navigation_algorithm_section = 2;
    }
    else if ( 2 == board_navigation_algorithm_section)
    { 
      update_position_after_right_turn();
      num_rows_to_pass = 8 - row_S - 1; // -1 is manual correction  --------------------------------
      num_lines_to_pass = num_rows_to_pass;
      Serial.println("Pass this many lines: ");
      Serial.println(num_lines_to_pass);
      board_navigation_algorithm_section = 3;
     }
    else if ( (3 == board_navigation_algorithm_section) && (0 == moving_algorithm_fast() )  )
    {
      turn_right();
      passed_line = 0;
      board_navigation_algorithm_section = 4;
     }
    else if ( 4 == board_navigation_algorithm_section)
     {
      update_position_after_right_turn();
      num_cols_to_pass = 4 - 1 - 1;    // -1 is manual correction, extra -1 for red line
      num_lines_to_pass = num_cols_to_pass;
      Serial.print("Pass this many lines: ");
      Serial.println(num_lines_to_pass);
      board_navigation_algorithm_section = 5;
     }
     
    else if ( (5 == board_navigation_algorithm_section) && (0 == moving_algorithm() )  )    
     {
      Serial.println("S, STOPPPP");
      stop_motors();
      update_ending_position();
      delay(delayval);
      board_navigation_algorithm_section = 0;  
      return 0;
    }
    return 1;
  }// end board navigation case
    /*backwards_direction();
    delay(propagation_delay); 
    num_cols_to_pass = 7 - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);    
    moving_algorithm();
    turn_right(); // reverse turn righ
    
    num_rows_to_pass = 8 - row_S - 1; // -1 is manual correction
    num_lines_to_pass = num_rows_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);
    moving_algorithm();
    */    
  
  
}






void backwards_direction()
{
  digitalWrite(pin_direction_L1, LOW);
  digitalWrite(pin_direction_L2, HIGH);
  digitalWrite(pin_direction_R1, LOW);
  digitalWrite(pin_direction_R2, HIGH);
}

void forwards_direction()
{
  digitalWrite(pin_direction_L1, HIGH);
  digitalWrite(pin_direction_L2, LOW);
  digitalWrite(pin_direction_R1, HIGH);
  digitalWrite(pin_direction_R2, LOW);
}
