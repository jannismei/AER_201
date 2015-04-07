
int grid[10][11] = {0};
int col_S, row_S, col_T, row_T, num_rows_to_pass, num_cols_to_pass;
int num_lines_to_pass;


void setup()
{
/*
  code is such that given starting coordinates and terminal coordinates,
  the algorithm determines which of several cases the moving situation should be.
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
 
 need to tell robot to stop moving
*/
  
  
  
  grid[0][0] = 4; // set the # of balls in the corner hoppers
  grid[8][0] = 4; // corner hoppers have 4 balls each
  grid[5][3] = 7;
  col_S = 7; // testing cols and rows
  col_T = 5;
  row_S = 5;
  row_T = 2;
  Serial.begin(4800);
  Serial.println("Entering Setup\n");
  
    if ( (col_S < 2 && col_T < 2 ) || (col_S > 6 && col_T > 6) )
  { // if on far left columns or far right columns
   // no turning
  
    Serial.println("Pass rows");
    if (row_S >= row_T)
    { // if starting closer to gameboard and going other way
    // no turning
                                             // 0. choose to follow rows or columns first
       num_rows_to_pass = row_S - row_T;     // 1. calculate number rows needed to go
       num_lines_to_pass = num_rows_to_pass; // 2. calculate number lines to go
       moving_algorithm();                   // 3. move that number of lines
       Serial.println("S");                  // 4. if need to turn, then turn. 5. move number of lines. 6. turn
    }
    else if (row_S < row_T)
    { // if starting farther from gameboard and going other way
    // no turning
       num_rows_to_pass = row_T - row_S;
       num_lines_to_pass = num_rows_to_pass;
       moving_algorithm();
        Serial.println("W");
    }
  }
  
  else if ( (row_S < 3 && row_T < 3 ) || (row_S > 6 && row_T > 6) )
  { // if on top rows or bottom rows
   // no turning
    Serial.println("Pass cols");
    if (col_S >= col_T)
    { // if starting closer to right and going left
       num_cols_to_pass = col_S - col_T; 
       num_lines_to_pass = num_cols_to_pass;
       moving_algorithm();
       Serial.println("A");
    }
    else if (col_S < col_T)
    { // if starting closer to left and going right
     // no turning
       num_cols_to_pass = col_T - col_S;
       num_lines_to_pass = num_cols_to_pass;
       moving_algorithm();
       Serial.println("D");
    }
  }
  
  else if ( (row_S > 6) && (col_S < 7) && (row_T < 7) && (col_T > 6) )
  // turn right once
  {                                  // 1. Choose to go across rows first
    num_cols_to_pass = 7 - col_S;    // 2. Calculate num_cols to pass
    num_lines_to_pass = num_cols_to_pass; // 3. num_lines = num_cols_to_pass
    moving_algorithm();              // 4. Move along line until 0 lines left
    turn_right();                    // 5. Turn right
    num_rows_to_pass = row_S - row_T; // 6. Calc. num_rows to pass
    num_lines_to_pass = num_rows_to_pass; // 7. num_lines to pass = num_cols to pass
    moving_algorithm();              // 8. Move along line until 0 lines left
  }
  
  else if ( (row_S > 2) && (col_S > 6) && (row_T < 3) && (col_T < 7) )
  { // turn right once
    num_rows_to_pass = row_S - row_T;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_right();
    num_cols_to_pass = col_S - col_T;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
  }
  
  else if ( (row_S < 3) && (col_S > 1) && (row_T > 2) && (col_T < 2) )
  {
    // turn right once
    num_cols_to_pass = col_S - col_T;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
    turn_right();
    num_rows_to_pass = row_T - row_S;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
  }
  else if ( (row_S < 6) && (col_S < 2) && (row_T > 6) && (col_T > 1) )
  { // turn right once
    num_rows_to_pass = row_T - row_S;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_right();
    num_cols_to_pass = col_T - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
  }
  else if ( (row_S > 1) && (col_S < 2) && (row_T < 3) && (col_T > 1) )
  { // turn left once (1)
    num_rows_to_pass = row_S - row_T;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_left();
    num_cols_to_pass = col_T - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
  }
  else if ( (row_S < 3) && (col_S < 7) && (row_T > 1) && (col_T > 6) )
  { // turn left once (2)
    num_cols_to_pass = col_T - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
    turn_left();
    num_rows_to_pass = row_T - row_S;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
  }  
  else if ( (row_S < 7) && (col_S > 6) && (row_T > 6) && (col_T < 7) )
  { // turn left once (3)
    num_rows_to_pass = row_T - row_S;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_left();
    num_cols_to_pass = col_S - col_T;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
  }
  
  else if ( (row_S > 7) && (col_S > 1) && (row_T < 8) && (col_T < 2) )
  { // turn left once (4)
    num_cols_to_pass = col_T - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
    turn_left();
    num_rows_to_pass = row_S - row_T;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
  }
  
    
  else if ( (row_S > 6) && (col_S < 7) && (row_T < 3) && (col_T < 7) )
  { // turn right twice (1)
    num_cols_to_pass = 7 - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
    turn_right();
    num_rows_to_pass = row_S - row_T;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_right();
    num_cols_to_pass = 7 - col_T;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
  }

  else if ( (row_S > 2) && (col_S > 6) && (row_T > 2) && (col_T < 2) )
  { // turn right twice (2)
    num_rows_to_pass = row_S - 2;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_right();
    num_cols_to_pass = col_S - col_T;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
    turn_right();
    num_rows_to_pass = row_T - 2;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
  }


  else if ( (row_S < 3) && (col_S > 1) && (row_T > 6) && (col_T > 1) )
  { // turn right twice (3)
    num_cols_to_pass = col_S - 1;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
    turn_right();
    num_rows_to_pass = row_T - row_S;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_right();
    num_cols_to_pass = col_T - 1;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
  }
  
  else if ( (row_S < 7) && (col_S < 2) && (row_T < 7) && (col_T > 6) )
  { // turn right twice (4)
    num_rows_to_pass = 7 - row_S ;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
    turn_right();
    num_cols_to_pass = col_T - col_S;
    num_lines_to_pass = num_cols_to_pass;
    Serial.print("Pass this many cols: ");
    Serial.println(num_cols_to_pass);
    moving_algorithm();
    turn_right();
    num_rows_to_pass = 7 - row_T;
    num_lines_to_pass = num_rows_to_pass;
    Serial.print("Pass this many rows: ");
    Serial.println(num_rows_to_pass);
    moving_algorithm();
  }
  
  else
  {
    Serial.print("Invalid coordinates");
  }
}

void loop()
{
  Serial.println("in loop now");
  delay(10000);
}
