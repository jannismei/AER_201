// turn_left(), turn_right(), stationary_turn_left(), stationary_turn_right()

// delay changed to 150
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
        delay(150);// changed
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
      pass_line_time = millis();
      Serial.println("Passed Line Time: ");
      Serial.println(pass_line_time);
  
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
        delay(1500);
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
      pass_line_time = millis();
      Serial.println("Passed Line Time: ");
      Serial.println(pass_line_time);

  
  return 0;
}
































// currently using threshold, when any sensor hits threshold

// delay changed to 150, also has temporary delay for testing after turn
// This code has a long while loop, which means that nothing can be done while turning left

  /* this turns both motors at the same time, to try to ensure that the COM does not move
    However, the COM actually moves, because the speed of each motor is not perfectly calibrated
  */
  // can change turning condition from passed_5_lines to something else
int stationary_turn_left()
             
{
  int first_time_turn_left = 0;
  Serial.print("inside stationary turn_left function");

    while( 0 != left)
      { 
      read_IR_sensors();
      Serial.print("passed line, so turn left!--!--!--!\n");
      //Serial.print("speed L is ");
      //Serial.print(pin_speed_L);      
  digitalWrite(pin_direction_L1, LOW);
  digitalWrite(pin_direction_L2, HIGH);
  digitalWrite(pin_direction_R1, HIGH);
  digitalWrite(pin_direction_R2, LOW);

      analogWrite(pin_speed_L, startSpeed_L);
      analogWrite(pin_speed_R, startSpeed_R);
      
      if (0 == first_time_turn_left)
      { // If it is the first run-through of while loop while turning left
      // then wait a little before checking the IR sensors
        first_time_turn_left = 1;
        delay(150);
      }
      
      read_IR_sensors();
        if (LDRC1<=500 || LDRC3 <= 500) // stop turning left when sense black
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
      
      delay(100000);// temporary delay
  return 0;
}




// This code has a long while loop, which means that nothing can be done while turning left

  // to turn right, slow down gradually
  // can change turning condition from passed_5_lines to something else
int stationary_turn_right()
             
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
        delay(150);
      }
      
      read_IR_sensors(); // may need to change to LDR4
        if (LDRC1<=500 || LDRC3 <= 500) // stop turning right when sense black
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

    delay(100000);// temporary delay  
  return 0;
}
