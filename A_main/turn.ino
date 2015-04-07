// This code has a long while loop, which means that nothing can be done while turning left

  // to turn left, slow down gradually
  // can change turning condition from passed_5_lines to something else
int turn_left()
             
{
  int first_time_turn_left = 0;
  Serial.print("inside turn_left function");



    while( 0 != left)
      { 
      read_IR_sensors();
      Serial.print("passed line, so turn left!--!--!--!\n");
      Serial.print("speed L is ");
      Serial.print(pin_speed_L);
      left = 1;
      //right = right ;
      analogWrite(pin_speed_L , left);
      //analogWrite(speed2,right);
      
      if (0 == first_time_turn_left)
      { // If it is the first run-through of while loop while turning left
      // then wait a little before checking the IR sensors
        first_time_turn_left = 1;
        delay(1500);
      }
      
      read_IR_sensors();
        if (LDR1 + threshold <= LDR3) // stop turning left when sense black
        {
          Serial.print("LDR1: ");
          Serial.print(LDR1);
          Serial.print(" LDR3: ");
          Serial.print(LDR3);
          Serial.print("\n stop turning left 1-1-1-1-1-1-1-1\n");
          break;
        }
     }
      
      Serial.print("STOP TURNING LEFT--!--!--!");
      analogWrite(pin_speed_L, startSpeed_L);

  
  return 0;
}

// This code has a long while loop, which means that nothing can be done while turning left

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
        delay(150); //changed to 150 from 1500
      }
      
      read_IR_sensors(); // may need to change to LDR4
        if (LDR2 + threshold <= LDR3) // stop turning right when sense black
        {
          Serial.print("LDR2: ");
          Serial.print(LDR2);
          Serial.print(" LDR3: ");
          Serial.print(LDR3);
          Serial.print("\n stop turning right 1-1-1-1-1-1-1-1\n");
          break;
        }
      }
      
      Serial.print("STOP TURNING right--!--!--!");
      analogWrite(pin_speed_R, startSpeed_R);

  
  return 0;
}
