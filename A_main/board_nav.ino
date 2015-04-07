// delays here

int board_navigation_algorithm()
{
  int propagation_delay = 0;
  int delayval = 30000; // this delay value is so that robot stops after done nav
  
   Serial.println("Entering Gameboard Navigation Algorithm\n");
  
  forwards_direction();
  
  if ( (col_S > 4) && (row_S > 6) ) // case 1
  { 
    forwards_direction();
    delay(propagation_delay);
    num_cols_to_pass = 7 - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many lines: ");
    Serial.println(num_lines_to_pass);
    moving_algorithm();  
    turn_right();
    num_rows_to_pass = row_S - 2 - 1; // extra -1 for manual correction
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many lines: ");
    Serial.println(num_lines_to_pass);  
    moving_algorithm();
    turn_right();
    num_cols_to_pass = 7- 1 - 1; // exxtra -1 for manual correction
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many lines: ");
    Serial.println(num_lines_to_pass);
    moving_algorithm();  
    turn_right();
    num_rows_to_pass = 8 - 2 - 1; // extra -1 for manual correction    
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many lines: ");
    Serial.println(num_lines_to_pass);  
    turn_right();
    num_cols_to_pass = 4 -1 - 1;    // -1 is manual correction
    num_lines_to_pass = num_cols_to_pass;
    moving_algorithm();        
    Serial.println("S, STOPPPP");
    stop_motors();
    delay(delayval);
    
    
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
  if ( (col_S > 4) && (row_S > 6) )
  {
    
  forwards_direction();
  delay(propagation_delay); // time for signals to propagate
        Serial.println("Pass COLS, going forward");
                                        
       num_cols_to_pass = col_S - 3;    // not right?
       num_lines_to_pass = num_cols_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);  
       moving_algorithm();                  
       Serial.println("S, STOPPPP");
       stop_motors();
       delay(delayval); 
  }
  
  if ( (col_S > 6) && (row_S > 2) && (row_S < 7) ) 
  { // case 4
    
      forwards_direction();
      delay(propagation_delay);
      num_rows_to_pass = row_S - 2;
      num_lines_to_pass = num_rows_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);  
      moving_algorithm();
      turn_right();
      num_cols_to_pass = 7 - 1 - 1; // extra -1 for manual correction
      num_lines_to_pass = num_cols_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);  
      moving_algorithm();
      turn_right();
      num_rows_to_pass = 8 - 2 - 1; // extra -1 for manual correction
      num_lines_to_pass = num_rows_to_pass;
      moving_algorithm();
      turn_right();
      num_cols_to_pass = 4 - 1 - 1; // extra -1 for manual correction
      num_lines_to_pass = num_cols_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);  
      moving_algorithm();
      Serial.println("S, STOPPPP");
      stop_motors();
      delay(delayval); 
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
    }
    
  if ( (col_S < 2) && (row_S < 7) && (row_S > 2) ) // case 3
  {
   forwards_direction();
   delay(propagation_delay);
   
       num_rows_to_pass = 8 - row_S;
       num_lines_to_pass = num_rows_to_pass;
       Serial.println("Pass this many lines: ");
       Serial.println(num_lines_to_pass);
       moving_algorithm();        
       turn_right();       
       num_cols_to_pass = 4 - 1 - 1;    // -1 is manual correction
       num_lines_to_pass = num_cols_to_pass;
       moving_algorithm();        
       Serial.println("S, STOPPPP");
       stop_motors();
       delay(delayval);
  }
  
  if ( (col_S < 5) && (row_S < 3) ) // can make col_S < 6 // case 5
  {
    forwards_direction();
    delay(propagation_delay);
    num_cols_to_pass = col_S - 1;
    num_lines_to_pass = num_cols_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);    
    moving_algorithm();
    turn_right();
    num_rows_to_pass = 8 - row_S - 1; // -1 is manual correction
    num_lines_to_pass = num_rows_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);
    moving_algorithm();        
    turn_right();       
    num_cols_to_pass = 4 - 1 - 1;    // -1 is manual correction
    num_lines_to_pass = num_cols_to_pass;
    moving_algorithm();        
    Serial.println("S, STOPPPP");
    stop_motors();
    delay(delayval);
  }
  
  if ( (col_S > 4) && (row_S < 3) ) // case 6
  {
    
    forwards_direction();
    delay(propagation_delay);
    num_cols_to_pass = col_S - 1;
    num_lines_to_pass = num_cols_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);    
    moving_algorithm();
    turn_right();
    num_rows_to_pass = 8 - row_S - 1; // -1 is manual correction
    num_lines_to_pass = num_rows_to_pass;
    Serial.println("Pass this many lines: ");
    Serial.println(num_lines_to_pass);
    moving_algorithm();        
    turn_right();       
    num_cols_to_pass = 4 -1 - 1;    // -1 is manual correction
    num_lines_to_pass = num_cols_to_pass;
    moving_algorithm();        
    Serial.println("S, STOPPPP");
    stop_motors();
    delay(delayval);
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
