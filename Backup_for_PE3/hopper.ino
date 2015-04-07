// left_corner(), right_corner(), turn_to_face_hopper()

// Many delays in turn_to_face hopper

int left_corner()
{
  col_T = 2;
  row_T = 1;
  navigation_algorithm();
  
 return 0; 
}

int right_corner()
{
  col_T = 7;
  row_T = 2;
  navigation_algorithm();
  
 return 0; 
}


//March 16
// custom threshold here

//left motor stay still, right motor go backwards

// This code has a long while loop, which means that nothing can be done while turning left

  // to turn left, slow down gradually
  // can change turning condition from passed_5_lines to something else
int turn_to_face_hopper()
{
  int end_delay = 1000;
  int startSpeed_L = 145, startSpeed_R = 105;
  int threshold = 200; // custom threshold here
  int first_time_turn_left = 0;
  Serial.print("inside stationary turn_left function");

  while( 0 != left)
    { 
      read_IR_sensors();
      Serial.print("passed line, so turn left!--!--!--!\n");
      Serial.print("speed L is ");
      Serial.print(pin_speed_L);      
      digitalWrite(pin_direction_L1, HIGH);
      digitalWrite(pin_direction_L2, LOW);
      digitalWrite(pin_direction_R1, LOW);
      digitalWrite(pin_direction_R2, HIGH);

      analogWrite(pin_speed_L, 1);
      analogWrite(pin_speed_R, startSpeed_R);
      
      if (0 == first_time_turn_left)
      { // If it is the first run-through of while loop while turning left
      // then wait a little before checking the IR sensors
        first_time_turn_left = 1;
        delay(1500);
      }
      
      read_IR_sensors();
      if ( (LDR5 + threshold <= LDR2) && (LDR3 + threshold <= LDR1) )// stop turning left when sense black
        {
          Serial.print("LDRC1: ");
          Serial.print(LDRC1);
          Serial.print(" LDRC3: ");
          Serial.print(LDRC3);
          Serial.print("\n stop turning left 1-1-1-1-1-1-1-1\n");
          break;
        }
   }
      
    Serial.print("STOP TURNING LEFT--!--!--!");
    stop_motors();
      
    forwards_direction();
    while (ultrasonic_front() > 13)
    {
      //ultrasonic_front(); unnecessary, because already called in while statement
      analogWrite(pin_speed_L, startSpeed_L);
      analogWrite(pin_speed_R, startSpeed_R);
    }
    stop_motors();
    delay(end_delay);
    return 0;
}




// This code has a long while loop, which means that nothing can be done while turning left

  // to turn right, slow down gradually
  // can change turning condition from passed_5_lines to something else
/*int stationary_turn_right()
             
{
  int first_time_turn_right = 0;
  Serial.print("inside turn_right function");



    while( 0 != right)
      { 
      read_IR_sensors();
      Serial.print("passed line, so turn right!--!--!--!\n");
      Serial.print("speed L is ");
      Serial.print(pin_speed_R);
  digitalWrite(pin_direction_L1, HIGH);
  digitalWrite(pin_direction_L2, LOW);
  digitalWrite(pin_direction_R1, LOW);
  digitalWrite(pin_direction_R2, HIGH);
      analogWrite(pin_speed_R , startSpeed_R);
      //analogWrite(speed2,right);
      
      if (0 == first_time_turn_right)
      { // If it is the first run-through of while loop while turning right
      // then wait a little before checking the IR sensors
        first_time_turn_right = 1;
        delay(1500);
      }
      
      read_IR_sensors(); // may need to change to LDR4
        if (LDRC2 + threshold <= LDRC3) // stop turning right when sense black
        {
          Serial.print("LDRC2: ");
          Serial.print(LDRC2);
          Serial.print(" LDRC3: ");
          Serial.print(LDRC3);
          Serial.print("\n stop turning right 1-1-1-1-1-1-1-1\n");
          break;
        }
      }
      
      Serial.print("STOP TURNING right--!--!--!");
      analogWrite(pin_speed_R, startSpeed_R);
      stop_motors();
  return 0;
}*/
