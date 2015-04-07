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
     
     if ( 1 < num_lines_to_pass )
     {
       follow_line(); // regular travelling speed
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
 if ('W' == orientation)
 { // going up a row
   row_Cur = row_Cur + 1;
   grid[col_Cur][row_Cur] = 'W';
 }
 else if ('A' == orientation)  
 { // going left a column
   col_Cur = col_Cur - 1;
   grid[col_Cur][row_Cur] = 'A';
 }
 else if ('S' == orientation)
 { // going down a row
   row_Cur = row_Cur - 1;
   grid[col_Cur][row_Cur] = 'S';
 }
 else if ('D' == orientation)
 { // going right a column
   row_Cur = row_Cur + 1;
   grid[col_Cur][row_Cur] = 'D';
 }
 return;
}

void update_position_after_right_turn()
{
  grid[col_Cur][row_Cur] = '0';
 if ('W' == orientation)
 { // going up a row
   col_Cur = col_Cur + 1;
   orientation = 'D';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ('A' == orientation)  
 { // going left a column
   row_Cur = row_Cur + 1;
   orientation = 'W';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ('S' == orientation)
 { // going down a row
   col_Cur = col_Cur - 1;
   orientation = 'A';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ('D' == orientation)
 { // going right a column
   row_Cur = row_Cur - 1;
   orientation = 'S';
   grid[col_Cur][row_Cur] = orientation;
 }
 return;
}

void update_position_after_left_turn()
{
  grid[col_Cur][row_Cur] = '0';
 if ('W' == orientation)
 { // going up a row
   col_Cur = col_Cur - 1;
   orientation = 'A';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ('A' == orientation)  
 { // going left a column
   row_Cur = row_Cur - 1;
   orientation = 'S';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ('S' == orientation)
 { // going down a row
   col_Cur = col_Cur + 1;
   orientation = 'D';
   grid[col_Cur][row_Cur] = orientation;
 }
 else if ('D' == orientation)
 { // going right a column
   row_Cur = row_Cur + 1;
   orientation = 'W';
   grid[col_Cur][row_Cur] = orientation;
 }
 return;
}


