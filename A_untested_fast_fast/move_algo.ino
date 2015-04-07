// moving_algorithm()  no delay, update_starting_position (), update_position (),
// update_position_after_right_turn(), update_position_after_left_turn()

int moving_algorithm()
{
  
    /* when integrated with main code, will want to 
    use while loop. while(num_lines_to_go != 0 and while num_turns_to_go != 0)
    
    if (1 == sensing_passing_line() )
    {
       num_lines_to_go = num_lines_to_go - 1; 
    }
    */
   if(0 != num_lines_to_pass) 
   {
     read_IR_sensors();
     
     if ( 5 == num_lines_to_pass)
     {
       Serial.println("5 lines to pass, so move slowly (in moving_algorithm)");
       variable_speed_follow_line(slowSpeed_L, slowSpeed_R);
     }
     else if ( (1 < num_lines_to_pass) || (1 == fast_moving_algo_flag) )
     {
       variable_speed_follow_line(startSpeed_L, startSpeed_R); // regular travelling speed
     }
     else if (1 >= num_lines_to_pass)
     {
       variable_speed_follow_line(slowSpeed_L, slowSpeed_R); // slow down when only 1 line left (means can stop more easily)
     }
     
     int sensing_pass_line_function_return = sensing_passing_line();
     if( 1 == sensing_pass_line_function_return  )
     {
       num_lines_to_pass = num_lines_to_pass - 1;
       Serial.println("this many lines left to go");
       Serial.println(num_lines_to_pass);
       update_position();
     }
    return 1;// Signifies that num_lines_to_pass has not reached 0.
    // delay(10); // is this really needed?
   }
   else if (0 == num_lines_to_pass)
   {
     return 0;
   }
   
}

int moving_algorithm_fast()
{
  
    /* same as moving_algorithm, but it doesn't slow down when there's one line left.
    Should take out the statement that checks rather than changing the speed, but I don't want to risk changing what works,
    with 20 hours to go before the preliminary competition.
    */
   if(0 != num_lines_to_pass) 
   {
     read_IR_sensors();
     
     if ( 5 == num_lines_to_pass)
     {
       Serial.println("5 lines to pass, so move slowly (in moving_algorithm_fast)");
       variable_speed_follow_line(slowSpeed_L, slowSpeed_R);
     }
     else if ( 1 < num_lines_to_pass )
     {
       variable_speed_follow_line(startSpeed_L, startSpeed_R);
     }
     else if (1 >= num_lines_to_pass)
     {
       variable_speed_follow_line(startSpeed_L, startSpeed_R); // slow down when only 1 line left (means can stop more easily)
     }
     
     int sensing_pass_line_function_return = sensing_passing_line();
     if( 1 == sensing_pass_line_function_return  )
     {
       num_lines_to_pass = num_lines_to_pass - 1;
       Serial.println("this many lines left to go");
       Serial.println(num_lines_to_pass);
       update_position();
     }
    return 1;// Signifies that num_lines_to_pass has not reached 0.
    // delay(10); // is this really needed?
   }
   else if (0 == num_lines_to_pass)
   {
     return 0;
   }
   
}


void update_starting_position()
{
  col_Cur = col_S;
  row_Cur = row_S;
  grid[col_Cur][row_Cur] = orientation;
  return;
}

void update_ending_position()
{
   col_S = col_T;
   row_S = row_T;
   col_Cur = col_T;
   row_Cur = row_T;
   grid[col_Cur][row_Cur] = orientation;
   return;
}


void update_position()
{
 grid[col_Cur][row_Cur] = '0';
 if ( ('N' == orientation) || ('n' == orientation))
 { // going up a row
   row_Cur = row_Cur + 1;
   grid[col_Cur][row_Cur] = 'N';
 }
 else if ( ('W' == orientation)  || ('w' == orientation) )
 { // going left a column
   col_Cur = col_Cur - 1;
   grid[col_Cur][row_Cur] = 'W';
 }
 else if ( ('S' == orientation) || ( 's' == orientation) )
 { // going down a row
   row_Cur = row_Cur - 1;
   grid[col_Cur][row_Cur] = 'S';
 }
 else if ( ('E' == orientation) || ( 'e' == orientation)  ) 
 { // going right a column
   row_Cur = row_Cur + 1;
   grid[col_Cur][row_Cur] = 'E';
 }
 Serial.print("current row: ");
 Serial.print(row_Cur);
 Serial.print(" current column: ");
 Serial.println(col_Cur);
 return;
}

void update_position_after_right_turn()
{
  grid[col_Cur][row_Cur] = '0';
 if ( ('N' == orientation) || ('n' == orientation) )
 { // going up a row
   col_Cur = col_Cur + 1;
   orientation = 'E';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ( ('W' == orientation)  || ('w' == orientation) )
 { // going left a column
   row_Cur = row_Cur + 1;
   orientation = 'N';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ( ('S' == orientation) || ( 's' == orientation) )
 { // going down a row
   col_Cur = col_Cur - 1;
   orientation = 'W';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if (  ('E' == orientation) || ( 'e' == orientation)  ) 
 { // going right a column
   row_Cur = row_Cur - 1;
   orientation = 'S';
   grid[col_Cur][row_Cur] = orientation;
 }
 Serial.print("current row: ");
 Serial.print(row_Cur);
 Serial.print(" current column: ");
 Serial.println(col_Cur);
 return;
}

void update_position_after_left_turn()
{
  grid[col_Cur][row_Cur] = '0';
 if ( ('N' == orientation) || ('n' == orientation) )
 { // going up a row
   col_Cur = col_Cur - 1;
   orientation = 'W';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ( ('W' == orientation)  || ('w' == orientation) )
 { // going left a column
   row_Cur = row_Cur - 1;
   orientation = 'S';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ( ('S' == orientation) || ( 's' == orientation) )
 { // going down a row
   col_Cur = col_Cur + 1;
   orientation = 'E';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ( ('E' == orientation) || ( 'e' == orientation)  ) 
 { // going right a column
   row_Cur = row_Cur + 1;
   orientation = 'N';
   grid[col_Cur][row_Cur] = orientation;
 }
 Serial.print("current row: ");
 Serial.print(row_Cur);
 Serial.print(" current column: ");
 Serial.println(col_Cur);
 return;
}


