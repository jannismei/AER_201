// This file is meant to be included in a main file that sets up stuff
// This part should be in the loop

  // to turn right, slow down gradually
  // can change turning condition from passed_5_lines to something else
int turn_right()
             
{
  int first_time_turn_right = 0;
  Serial.print("inside turn_right function");



    while( 0 != right)
      { 
      read_IR_sensors();
      Serial.print("passed line, so turn right!--!--!--!\n");
      Serial.print("speed L is ");
      Serial.print(pin_speed_R);
      right = 1;
      //right = right ;
      analogWrite(pin_speed_R , right);
      //analogWrite(speed2,right);
      
      if (0 == first_time_turn_right)
      { // If it is the first run-through of while loop while turning right
      // then wait a little before checking the IR sensors
        first_time_turn_right = 1;
        delay(3000);
      }
      
      read_IR_sensors(); // may need to change to LDR4
        if (LDR5 + threshold <= LDR3) // stop turning right when sense black
        {
          Serial.print("LDR5: ");
          Serial.print(LDR5);
          Serial.print(" LDR3: ");
          Serial.print(LDR3);
          Serial.print("\n stop turning right 1-1-1-1-1-1-1-1\n");
          break;
        }

      
      Serial.print("STOP TURNING right--!--!--!");
      analogWrite(pin_speed_R, startSpeed_R);

  }
  return 0;
}
