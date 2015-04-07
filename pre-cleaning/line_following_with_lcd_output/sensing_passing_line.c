#ifndef sensing_passing_line_h
#define sensing_passing_line_h
#include "Arduino.h"
/*
int sensing_passing_line(int num_lines_passed, int LDR1, int LDR2, 
                        int LDR3, int LDR4, int LDR5, int threshold)
{
  int number_lines_passed;
  int passed_5_lines;
  char black1 = 0, black2 = 0, black3, black4, black5; // flags to see if black or white
  char front_just_black;
  int passed_line = 0;


// took away else from else if statement
  //LDR4 always black, black always lower value than white
  if ( (LDR1  > (LDR4 + threshold) ) && (LDR2 > (LDR4 + threshold)) && (0 = black1) )
    { // LDR1 and LDR2 measure white, compared to LDR3 or LDR5
      black1 = 0;
      black2 = 0;
    }
   if  ( ( (LDR1 + threshold < LDR3) && (LDR2 + threshold < LDR3) )
      || ( (LDR1 + threshold < LDR5) && (LDR2 + threshold < LDR5) ) )
     { // LDR1 and LDR2 measure black, LDR3, LDR5 measure white
       black1 = 1;
       black2 = 1;
     }
   if ( ( black1 = 1) && (black2 = black1) && ( ( (LDR1 > LDR3 + threshold) 
           && (LDR2 > LDR3 + threshold) ) || ( (LDR1 > LDR5 + threshold) 
           && (LDR2 > LDR5 + threshold) ) ) )
      { // also need to make sure both motors turning forward
        // LDR1 and LDR2 were both just black, and now they are both white, so
        // reset black1 and black2
        
        black1 = 0;
        black2 = 0;
        front_just_black = 1;
      }
    if ( ( (LDR3 < LDR1 + threshold) && (LDR3 < LDR1 + threshold) )
          && ( (LDR5 < LDR2 + threshold) && (LDR5 < LDR2 + threshold) ) )
     { // LDR3 and LDR5 measure black
       // LDR1 and LDR2 measure white
       // means LDR3 and LDR5 passed line
       black1 = 1;
       black2 = 1;
       number_lines_passed += 1;
       passed_line = 1;
     }
     
    if (5 == number_lines_passed)
       {
          passed_5_lines = 1; // means time to turn.
       }
   return passed_line;
}
*/
#endif;
