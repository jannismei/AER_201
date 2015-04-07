// navigation_algorithm()  no delay except at turns, stop_motors()


int navigation_algorithm()
{
  
  // returns 0 if completed.
  // retursn 1 if not completed
  int delayval = 3000; // this delay value is so that robot stops after done nav
/*
  code is such that given starting coordinates and terminal coordinates,
  the algorithm determines which of severmoving_algorithmal cases the moving situation should be.
  Then you go to that case, and move accordingly.


  For a sample moving case, here is the order in which you determine what to do
   1. Choose to go across rows first
// 2. Calculate num_cols to pass
// 3. num_lines = num_cols_to_pass
// 4. Move along line until 0 lines left
// 5. Turn right
// 6. Calc. num_rows to pass
// num_lines to pass = num_cols to pass
 7. Move along line until 0 lines left
// Move aglo takes care of stopping, nav algo returns 0 when it is done 
*/
  
    // set motor direction to forward
  forwards_direction();
  

//  Serial.println("Entering Navigation_Algorithm\n");
  
  // base case
  if ( (col_S < 2 && col_T < 2 ) || (col_S > 6 && col_T > 6) )
  { // if on far left columns or far right columns
   // no turning
  //    Serial.println("Pass rows");
  
    if (row_S >= row_T)
    { // if starting closer to gameboard and going down
    // no turning
        if ( 0 == navigation_algorithm_section)
        {
          orientation = 'S';
          update_starting_position();
          Serial.print(" nav algo section = 0");                                     // 0. choose to follow rows or columns first
          num_rows_to_pass = row_S - row_T;     // 1. calculate number rows needed to go
          num_lines_to_pass = num_rows_to_pass; // 2. calculate number lines to go
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
        else if ( 0 == moving_algorithm() )                   // 3. move that number of lines
        {
          Serial.println("S, STOPPPP");                  // 4. if need to turn, then turn. 5. move number of lines. 6. turn
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
        }
        return 1;
    } // end case
    else if (row_S < row_T)
    { // if starting farther from gameboard and going up
    // no turning
       if ( 0 == navigation_algorithm_section)
        {
          orientation = 'W';
          update_starting_position();
          Serial.print(" nav algo section = 0");
          num_rows_to_pass = row_T - row_S;
          num_lines_to_pass = num_rows_to_pass;
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
        if ( 0 == moving_algorithm() ) 
        {
          Serial.println("W, STOPPPP");
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
        }
        return 1;
    } // end case
  }
  
  else if ( (row_S < 3 && row_T < 3 ) || (row_S > 6 && row_T > 6) )
  { // if on top rows or bottom rows
   // no turning
    //  Serial.println("Pass cols");
      if (col_S >= col_T)
      { // if starting closer to right and going left
        if ( 0 == navigation_algorithm_section)
          {
             orientation = 'A';
             update_starting_position();
             num_cols_to_pass = col_S - col_T; 
             num_lines_to_pass = num_cols_to_pass;
             navigation_algorithm_section = 1; // means go to next section next time you run through this code
          }
        if ( 0 == moving_algorithm() ) 
        {
           Serial.println("A,  STOPP");
           stop_motors();
           update_ending_position();
           delay(delayval);
           navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
           return 0;
        }
        return 1;
      } // end case
      else if (col_S < col_T)
      { // if starting closer to left and going right
       // no turning
        if ( 0 == navigation_algorithm_section)
          {
             orientation = 'D';
             update_starting_position();
             num_cols_to_pass = col_T - col_S;
             num_lines_to_pass = num_cols_to_pass;
             navigation_algorithm_section = 1; // means go to next section next time you run through this code
          }
         if ( 0 == moving_algorithm() ) 
          {
             Serial.println("D, STOPP");
             stop_motors();
             update_ending_position;
             delay(delayval);
             navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
             return 0;
          }
        return 1;
      } // end case
  }
  
  else if ( (row_S > 6) && (col_S < 7) && (row_T < 7) && (col_T > 6) )
  // turn right once (1)
  {                                  // 1. Choose to go across rows first
      if ( 0 == navigation_algorithm_section)
        {
          orientation = 'D';
          update_starting_position();
          Serial.print(" nav algo section = 0");
          num_cols_to_pass = 7 - col_S;    // 2. Calculate num_cols to pass
          num_lines_to_pass = num_cols_to_pass; // 3. num_lines = num_cols_to_pass
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
         // 4. Move along line until 0 lines left
      else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
         { 
          turn_right();                    // 5. Turn right
          passed_line = 0;
          navigation_algorithm_section = 2;
         }
      else if ( 2 == navigation_algorithm_section)
         {
          update_position_after_right_turn();
          num_rows_to_pass = row_S - row_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN // 6. Calc. num_rows to pass
          num_lines_to_pass = num_rows_to_pass; // 7. num_lines to pass = num_cols to pass
          navigation_algorithm_section = 3;
         }
       else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
         {      // 8. Move along line until 0 lines left
            Serial.println("S, STOPPPP");
            stop_motors();
            update_ending_position();
            delay(delayval);
            navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
            return 0;
         }
         return 1;
  } // end case
  
  else if ( (row_S > 2) && (col_S > 6) && (row_T < 3) && (col_T < 7) )
  { // turn right once (2)
  
      if ( 0 == navigation_algorithm_section)
        {
          orientation = 'S';
          update_starting_position();
          Serial.print(" nav algo section = 0");
          num_rows_to_pass = row_S - row_T;
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
       else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
       else if ( 2 == navigation_algorithm_section)
        {
          update_position_after_right_turn();
          num_cols_to_pass = col_S - col_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 3;
        }
        else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
         {        
          Serial.println("A, STOPPPP");
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
         }
         return 1;
   } // end case
  
  else if ( (row_S < 3) && (col_S > 1) && (row_T > 2) && (col_T < 2) )
  {
    // turn right once (3)
    if ( 0 == navigation_algorithm_section)
        {
          orientation = 'A';
          update_starting_position();
          Serial.print(" nav algo section = 0");
          num_cols_to_pass = col_S - col_T;
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
     else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
      { 
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 2;
      }
    else if ( 2 == navigation_algorithm_section)
      {
          update_position_after_right_turn();
          num_rows_to_pass = row_T - row_S;
          num_lines_to_pass = num_rows_to_pass - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 3;
      }
    else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
      { 
        moving_algorithm();
        Serial.println("W, STOPPPP");
        stop_motors();
        update_ending_position();
        delay(delayval);
        navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
        return 0;
       }
       return 1;
  }  // end case
  
  else if ( (row_S < 6) && (col_S < 2) && (row_T > 6) && (col_T > 1) )
  { // turn right once (4)
        if ( 0 == navigation_algorithm_section)
        {
          orientation = 'W';
          update_starting_position();
          Serial.print("navigation_algorithm_section");
          Serial.println(navigation_algorithm_section);
          num_rows_to_pass = row_T - row_S;
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
    else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
         { 
          Serial.print("navigation_algorithm_section: ");
          Serial.println(navigation_algorithm_section);
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 2;
         }
    else if ( 2 == navigation_algorithm_section)
         {
          update_position_after_right_turn();
          Serial.print("navigation_algorithm_section: ");
          Serial.println(navigation_algorithm_section);
          num_cols_to_pass = col_T - col_S - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 3;
         }
    else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
         {
            Serial.print("navigation_algorithm_section");
            Serial.println(navigation_algorithm_section); 
            moving_algorithm();
            Serial.println("D, STOPPPP");
            stop_motors();
            update_ending_position();
            delay(delayval);
            navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
            return 0;
         }
         return 1;
  }  // end case
  else if ( (row_S > 1) && (col_S < 2) && (row_T < 3) && (col_T > 1) )
  { // turn left once (1)
      if ( 0 == navigation_algorithm_section)
        {
          orientation = 'S';
          update_starting_position();
          Serial.print(" nav algo section = 0");
          num_rows_to_pass = row_S - row_T;
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
    
        else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
         { 
          turn_left();
          passed_line = 0;
          navigation_algorithm_section = 2;
         }
        else if ( 2 == navigation_algorithm_section)
         {    
          update_position_after_left_turn;
          num_cols_to_pass = col_T - col_S - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 3;
         }
    
        else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
         {    
          Serial.println("D, STOPPPP");
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
         }
         return 1;
  }  // end case
  
  else if ( (row_S < 3) && (col_S < 7) && (row_T > 1) && (col_T > 6) )
  { // turn left once (2)
        if ( 0 == navigation_algorithm_section)
        {
          orientation = 'D';
          Serial.print(" nav algo section = 0");
          num_cols_to_pass = col_T - col_S;
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
        else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_left();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
        else if ( 2 == navigation_algorithm_section)
        {
            update_position_after_left_turn;
            num_rows_to_pass = row_T - row_S - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
            num_lines_to_pass = num_rows_to_pass;
            Serial.print("Pass this many rows: ");
            Serial.println(num_rows_to_pass);
            navigation_algorithm_section = 3;
        }
        else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
         {
          Serial.println("W, STOPPPP");
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
         }
         return 1;
  
  }  // end case
  
  else if ( (row_S < 7) && (col_S > 6) && (row_T > 6) && (col_T < 7) )
  { // turn left once (3)
        if ( 0 == navigation_algorithm_section)
        {
          orientation = 'W';
          update_starting_position();
          num_rows_to_pass = row_T - row_S;
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
        else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_left();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
        else if ( 2 == navigation_algorithm_section)
        {  
          update_position_after_left_turn;
          num_cols_to_pass = col_S - col_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 3;
        }
        else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
         {  
          Serial.println("W, STOPPPP");
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
         }
         return 1;
  }
  
  else if ( (row_S > 7) && (col_S > 1) && (row_T < 8) && (col_T < 2) )
  { // turn left once (4)
    if ( 0 == navigation_algorithm_section)
        {
          orientation = 'A';
          update_starting_position();
          num_cols_to_pass = col_S - col_T;
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
       else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_left();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
       else if ( 2 == navigation_algorithm_section)
        {
         update_position_after_left_turn;
         num_rows_to_pass = row_S - row_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
         num_lines_to_pass = num_rows_to_pass;
         Serial.print("Pass this many rows: ");
         Serial.println(num_rows_to_pass);
         navigation_algorithm_section = 3;
        }
        else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
         { 
          moving_algorithm();
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
         }
         return 1;
  }  // end case
  
  else if ( (row_S > 6) && (col_S < 7) && (row_T < 3) && (col_T < 7) )
  { // turn right twice (1)
      if ( 0 == navigation_algorithm_section)
        {
          orientation = 'D';
          update_starting_position();
          num_cols_to_pass = 7 - col_S;
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
      else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
       else if ( 2 == navigation_algorithm_section)
        {
           update_position_after_right_turn;
           num_rows_to_pass = row_S - row_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
           num_lines_to_pass = num_rows_to_pass;
           Serial.print("Pass this many rows: ");
           Serial.println(num_rows_to_pass);
           navigation_algorithm_section = 3;
        }
       else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
        {  
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 4;
        }
       else if (4 == navigation_algorithm_section)
       {
          update_position_after_right_turn;
          num_cols_to_pass = 7 - col_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 5;
       }
    else if ( (5 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
       {
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
         }
         return 1;
  }  // end case

  else if ( (row_S > 2) && (col_S > 6) && (row_T > 2) && (col_T < 2) )
  { // turn right twice (2)
      if ( 0 == navigation_algorithm_section)
        {
          orientation = 'S';
          update_starting_position();
          num_rows_to_pass = row_S - 2;
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
      else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
       else if ( 2 == navigation_algorithm_section)
        {
          update_position_after_right_turn;
          num_cols_to_pass = col_S - col_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 3;
        }
       else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
        {  
           turn_right();
           passed_line = 0;
           navigation_algorithm_section = 4;
        }
       else if (4 == navigation_algorithm_section)
       {
          update_position_after_right_turn;
          num_rows_to_pass = row_T - 2 - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 5;
       }
    else if ( (5 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
       {
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
       }
       return 1;
  }  // end case


  else if ( (row_S < 3) && (col_S > 1) && (row_T > 6) && (col_T > 1) )
  { // turn right twice (3)
        if ( 0 == navigation_algorithm_section)
        {
          orientation = 'A';
          update_starting_position();
          num_cols_to_pass = 7 - col_S;  // JUST CHANGED THIS ONE??
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
      else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
       else if ( 2 == navigation_algorithm_section)
        {
          update_position_after_right_turn;
          num_rows_to_pass = row_T - row_S - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 3;
        }
       else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
        {
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 4;
        }
       else if (4 == navigation_algorithm_section)
       {
          update_position_after_right_turn;
          num_cols_to_pass = 7 - col_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 5;
       }
    else if ( (5 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
       {
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
         }
       return 1;
  }  // end case
  
  else if ( (row_S < 7) && (col_S < 2) && (row_T < 7) && (col_T > 6) )
  { // turn right twice (4)
      if ( 0 == navigation_algorithm_section)
        {
          orientation = 'W';
          update_starting_position();
          num_rows_to_pass = 7 - row_S ;
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 1; // means go to next section next time you run through this code
        }
      else if ( ( 1 == navigation_algorithm_section) && (0 == moving_algorithm() ) )
        { 
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 2;
        }
       else if ( 2 == navigation_algorithm_section)
        {
          update_position_after_right_turn;
          num_cols_to_pass = col_T - col_S - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_cols_to_pass;
          Serial.print("Pass this many cols: ");
          Serial.println(num_cols_to_pass);
          navigation_algorithm_section = 3;
        }
       else if ( (3 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
        {
          turn_right();
          passed_line = 0;
          navigation_algorithm_section = 4;
        }
       else if (4 == navigation_algorithm_section)
       {
          update_position_after_right_turn;
          num_rows_to_pass = 7 - row_T - 1; // -1 TO CORRECT FOR NOT SENSING LINE AFTER TURN
          num_lines_to_pass = num_rows_to_pass;
          Serial.print("Pass this many rows: ");
          Serial.println(num_rows_to_pass);
          navigation_algorithm_section = 5;
       }
    else if ( (5 == navigation_algorithm_section) && (0 == moving_algorithm() )  )
       {
          stop_motors();
          update_ending_position();
          delay(delayval);
          navigation_algorithm_section = 0; // reset the sections, you've run through the entire segment of code
          return 0;
       }
         return 1;
  }  // end case
  
  else
  {
    Serial.print("Invalid coordinates");
  }
  return 0;
}


int stop_motors()
{
   analogWrite(pin_speed_L, 0);
   analogWrite(pin_speed_R, 0);  
   return 0;
}
