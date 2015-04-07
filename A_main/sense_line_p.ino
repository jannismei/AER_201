
int sensing_passing_line()
{
 // Serial.print("inside sensing_passing_line function\n");
  int passed_5_lines;
  char black2, black3, black4, black5; // flags to see if black or white
  char front_just_black; // flag, the front sensors just registered black
  int passed_line = 0;

  //LDR4 always black, black always lower value than white
  if ( (LDR1  > LDR4 + threshold) && (LDR2 > LDR4 + threshold) && (black1 !=1) )
    { // LDR1 and LDR2 measure white, compared to LDR3 or LDR5
     // Serial.print("setting black1=0\n");
      black1 = 0;
      black2 = 0;
    }
   else if  ( ( (LDR1 + threshold < LDR3) && (LDR2 + threshold < LDR3) )
      || ( (LDR1 + threshold < LDR5) && (LDR2 + threshold < LDR5) ) ) 
      // If LDR1 and LDR2 are less than LDR3 or LDR5
     { // LDR1 and LDR2 measure black, LDR3, LDR5 measure white
        Serial.print("setting black1 = 1 \n");
       black1 = 1;
       black2 = 1;
       passed_line = 1;
       passed_2_lines = passed_2_lines + 1;
       delay(75);         //          neeed to get some way to get rid of this, maybe use interrupts or millis
     }
   else if (1 == passed_line)
   {
     passed_line = 0;
     black1 = 0;
     black2 = 0;
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
   return passed_line;
}
