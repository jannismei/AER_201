// This file is meant to be included in a main file that sets up stuff
// This part should be in the loop

  // to turn left, slow down gradually
  // can change turning condition from passed_5_lines to something else
int turn_left(int left, int right, int speed1, int speed2, 
              int rotate, int passed_5_lines, int passed_line, int LDR3, int LDR4, int LDR5)
             
{
  int first_time_turn_left = 0;
  Serial.print("inside turn_left function");
  if ( 1 == passed_line)
  { // first check if it's time to turn, then


    while( 0 != left)
      { 
      LDR3 = analogRead(2);
      LDR4 = analogRead(3);
      LDR5 = analogRead(4);
      Serial.print("passed line, so turn left!--!--!--!\n");
      Serial.print("speed 1 is ");
      Serial.print(speed1);
      left = 1;
      //right = right ;
      analogWrite(speed1,left);
      //analogWrite(speed2,right);
      if (0 == first_time_turn_left)
      {
        first_time_turn_left = 1;
        delay(3000);
      }
      LDR3 = analogRead(2);
      LDR4 = analogRead(3);
      LDR5 = analogRead(4);
        if (LDR4 + 100 <= LDR3) // stop turning left when sense black
        {
          Serial.print("LDR4: ");
          Serial.print(LDR4);
          Serial.print(" LDR3: ");
          Serial.print(LDR3);
          
          Serial.print("\n stop turning left 1-1-1-1-1-1-1-1\n");
          break;
        }

      }
      Serial.print("STOP TURNING LEFT--!--!--!");
      analogWrite(speed1,230);

  }
  return 0;
}
