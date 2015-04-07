#ifndef turn_left_h
#define turn_left_h
#include "Arduino.h"

// This file is meant to be included in a main file that sets up stuff
// This part should be in the loop

  // to turn left, slow down gradually
  // can change turning condition from passed_5_lines to something else
int turn_left(int left, int right, int speed1, int speed2, 
              int startSpeed, int rotate, int passed_5_lines, int passed_line)
{
  if (1 == passed_5_lines && 1 == passed_line)
  { // first check if it's time to turn, then
    while( 0 != left)
      { 
      left = left - rotate;
      //right = right ;
      analogWrite(speed1,left);
      //analogWrite(speed2,right);
      delay(50);
      }
      
    else if ( 0 == left)
      { 
      delay (500); // change this delay depending on how long it takes to turn
      }
  }
  return 0;
}

endif