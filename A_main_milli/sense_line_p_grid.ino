// sensing_passing_line() small delay (no delay), print_grid()

int sensing_passing_line()
{
  
   // Serial.print("inside sensing_passing_line function\n");
 if ((time - pass_line_time) < 300)
 {
   Serial.println("Inside the safety loop");
   return 0;
 }
 
  int passed_5_lines;
  char black2, black3, black4, black5; // flags to see if black or white
  char front_just_black; // flag, the front sensors just registered black
//  Serial.println(" sensing passing line ");
  //LDR4 always black, black always lower value than white
  if ( (LDR1  > LDR4 + threshold) && (LDR2 > LDR4 + threshold) && (1 != passed_line) )
    { // LDR1 and LDR2 measure white, compared to LDR3 or LDR5. This code does not reset black1.
    // This code will be bypassed if (1 == black1) OR (0 == black1 && LDR1 sense black && LDR2 sense black)
    
     // Serial.print("setting black1=0\n");
      black1 = 0;
      black2 = 0;
    }
   else if  ( ( (LDR1 + threshold < LDR3) && (LDR2 + threshold < LDR3) )
      || ( (LDR1 + threshold < LDR5) && (LDR2 + threshold < LDR5) ) ) 
      // If LDR1 and LDR2 are less than LDR3 or LDR5
     { // LDR1 and LDR2 measure black, LDR3, LDR5 measure white
       
       if (1 == black1) // if currently measuring black, and black1 has already been set to 1
       {// return 0, so passed line is not triggered again
         Serial.println(" leaving sensing_passing_line early ");
         return 0;
       }
       
       Serial.print("setting black1 = 1 \n");
       black1 = 1;
       black2 = black2 + 1;
       passed_line = 1;
       Serial.print("black2: ");
       Serial.println(black2);
       pass_line_time = millis();         //          neeed to get some way to get rid of this, maybe use interrupts or millis
     Serial.print("pass_line_time is "); // maybe don't need time anymore
     Serial.println(pass_line_time);
     }
     
     
   else if (  ( (LDR1  > 500) || (LDR2 > 500) ) && (1 == passed_line)  ) 
   // use LDR1 || LDR2 because the sensors often pass a line lopsided, so they may not
   // read white at the same time
   {// if not measuring black anymore, and 1 == passed_line, and time > 100      &&   ( (time - pass_line_time) > 100 ) 
   // reset black1 to 0
     Serial.println("resetting passed_line and black1");
     Serial.print("pass_line_time is ");
     Serial.print(pass_line_time);
     passed_line = 0;
     black1 = 0;
     black2 = 0;
// should not need this:     return 1; // Need to figure out how to put this return 1 in earlier section of code, i.e. when LDR1 first measures black
   }
   else 
   {
     passed_line = 0;
     black1 = 0;
     black2 = 0;
   }
      return passed_line; // only gets here if bypassed everything above
}
  /* else if ( ( black1 = 1) && (black2 = black1) && ( ( (LDR1 > LDR3 + threshold) 
           && (LDR2 > LDR3 + threshold) ) || ( (LDR1 > LDR5 + threshold) 
           && (LDR2 > LDR5 + threshold) ) ) )
      { // also need to make sure both motors turning forward
        // LDR1 and LDR2 were both just black, and now they are both white, so
        // reset black1 and black2
        
        black1 = 0;
        black2 = 0;
        front_just_black = 1;
  //    }
    else if ( ( (LDR3 < LDR1 + threshold) && (LDR3 < LDR1 + threshold) )
          && ( (LDR5 < LDR2 + threshold) && (LDR5 < LDR2 + threshold) ) )
     { // LDR3 and LDR5 measure black
       // LDR1 and LDR2 measure white
       // means LDR3 and LDR5 passed line
       black1 = 1;
       black2 = 1;
       num_lines_passed += 1;
       passed_line = 1;
     }
     */
 /*   else if (5 == num_lines_passed)
       {
          passed_5_lines = 1; // means time to turn.
       }*/








  // grid is bigger than it needs to be (needs to be 8x9)
/* this means that if we accidentally rewrite beyond the bounds,
there will be no effect on the grid */ 

int print_grid()
{

  Serial.print("\n");
  Serial.print("grid vals \n");
//  Serial.print(grid);
//  Serial.print(grid[0][1]);
//  Serial.print(grid[0][0]);
//  Serial.print(grid[1][2]);
  Serial.print("\n");  
  for (int j = 9; j >=0; j--)
  {
    Serial.print(" j ");
    Serial.print(j);
    Serial.print(" ");
    for (int i = 0; i <= 8; i ++)
    {
      Serial.print(grid[i][j]);
      Serial.print("|");
    }
    Serial.print("\n");
  }
  
}
