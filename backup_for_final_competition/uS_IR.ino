// read_IR_sensors(), ultrasonic() no delay, uS_logic() big delay


/* This code reads the IR sensors
currently serial printing LDRC1-LDRC3 readings
*/
void read_IR_sensors()
{
  LDR1 = analogRead(0); // read the 5 photosensors
  LDR2 = analogRead(1);
  LDR3 = analogRead(2);
  LDR4 = analogRead(3);
  LDR5 = analogRead(4);
  LDRC1 = analogRead(5);
  LDRC2 = analogRead(6);
  LDRC3 = analogRead(7);  
  // Everything below here is printing onto serial monitor or LCD
  
  // Print IR readings onto LCD
/*  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(LDR1);
  lcd.print("|");
  lcd.print(LDR2);

  // Print speed_Increment onto LCD
    //lcd.print("s_I: ");
    //lcd.print(speed_Increment);

  lcd.setCursor(0,1);  
  lcd.print(LDR3);
  lcd.print("|");
  lcd.print(LDR4);
  lcd.print("|");
  lcd.print(LDR5);
  lcd.setCursor(0,1);
  */
/*  // Serial Print IR readings
Serial.print("LDR1: ");
Serial.print(LDR1);
Serial.print(" LDR2: ");
Serial.print(LDR2);
Serial.print(" LDR3: ");
Serial.print(LDR3);
Serial.print(" LDR4: ");
Serial.print(LDR4);
Serial.print(" LDR5: ");
Serial.print(LDR5);

Serial.print(" LDRC1: ");
Serial.print(LDRC1);
Serial.print(" LDRC2: ");
Serial.print(LDRC2);
Serial.print(" LDRC3: ");
Serial.println(LDRC3);
*/
  return;
}


void ultrasonic()
{
  if ( (time - uS_time) > 29 )
  {
   // Serial.println(time - uS_start_time);
  uS_time = millis();
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int uS_internal = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  /*unsigned double distance = uS * 100 / 578;
  if (0 >= (distance - offset) )
  {
      Serial.print(distance);
  }
  else 
  {
    Serial.print(distance - offset); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  }
  Serial.println("mm");*/
  if (uS_internal > 0) // filter out 0s
  {
    uS = uS_internal / US_ROUNDTRIP_CM;
    Serial.print(uS); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm ");
  }
  //Serial.print(uS);
  ///Serial.println(" microseconds");
  }
}

int uS_logic()
{
  ultrasonic();
  
  uS_3 = uS_2;
  uS_2 = uS_1;
  uS_1 = uS;

  Serial.print(" uS_state ");
  Serial.println(uS_state);
    
  Serial.print(" uS_measurements ");
  Serial.print(uS_1);
  Serial.print("  ");
  Serial.print(uS_2);
  Serial.print("  ");
  Serial.println(uS_3);
  
  // go forward slowly, unless need to turn as specified in uS_state 4
 // follow_line();
  variable_speed_follow_line(slowSpeed_L, slowSpeed_R); 
  
  if( (uS_1 < first_leg) && (uS_2 < first_leg) && (uS_3 < first_leg) && (0 == uS_state) )
  {
    uS_state = 1;
      Serial.print(" uS_state ");
    Serial.println(uS_state);
  }

  else if( (uS_1 > first_leg) && /*(uS_2 > first_leg) && (uS_3 > first_leg) &&*/ (1 == uS_state) )
  {
    uS_state = 2;
    Serial.print(" uS_state ");
    Serial.println(uS_state);
  }
  
  else if( (uS_1 < mid_leg) && (uS_2 < mid_leg) && /*(uS_3 < mid_leg) &&*/ (2 == uS_state) )
  {
    uS_state = 3;
    Serial.print(" uS_state ");
    Serial.print(uS_state);
  }
  
  else if( (uS_1 > first_leg) && /*(uS_2 > first_leg) && (uS_3 > first_leg) &&*/ (3 == uS_state) )
  {
    uS_state = 4;
    turn_to_face_hopper(); // turns currently incorporate delays, 
    // so in general, we will only be going through them once
    
    Serial.print(" uS_state ");
    Serial.print(uS_state);
    uS_state = 0; // reset uS_state
    return 0;
  }
  return 1;
}

int uS_logic_corner()
{
  ultrasonic_front();

  uS_6f = uS_5f;
  uS_5f = uS_4f;
  uS_4f = uS_3f;
  uS_3f = uS_2f;
  uS_2f = uS_1f;
  uS_1f = uS_front;
  Serial.print(" uS_state ");
  Serial.println(uS_state);
    
  Serial.print(" uS_f measurements: ");
  Serial.print(uS_1f);
  Serial.print("  ");
  Serial.print(uS_2f);
  Serial.print("  ");
  Serial.println(uS_3f);
      
  if ( (0 == uS_state) && (uS_1f < first_leg_corner) && (uS_2f < first_leg_corner) && (uS_3f < first_leg_corner) )
  { // in position, so start turning left
  
    if ( ( uS_6f > (uS_1f + 3) ) && (uS_5f > (uS_2f + 3)) && (uS_3f >= uS_1f) )
    { // signifies that uS readings have gone down, so should stop turning left
      stop_motors();
      uS_state = 1;
    }
    else if ( (uS_6f <= uS_1f) && (uS_5f <= uS_2f) && (uS_3f <= uS_1f) )
    { // turn left slowly
      turn_left_no_delay();
    }
  }
  
  else if (1 == uS_state)
  {
    if ( (uS_1f < 13) && (uS_2f < 13) && (uS_3f < 13) )
    { // stop going forward when less than 13 cm to go
      stop_motors();
      uS_state = 2;
    }
    else if ( (uS_1f > 13) && (uS_2f > 13) && (uS_3f > 13) )
    { // keep going forward
    Serial.println("going forward");
      analogWrite(pin_speed_L, slowSpeed_L); 
      analogWrite(pin_speed_R, slowSpeed_R);
    }
  }
  
  else if ( 2 == uS_state)
  {
    return 0; // this signifies completion
  }
  return 1; // means keep going
}


int ultrasonic_front()
{

  if ( (time - uS_front_time) > 29 )
  {
 // Serial.print("time between pings: ");
 // Serial.println(time - uS_front_time);
  
  uS_front_time = millis();
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int uS_front_internal = sonar2.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  /*unsigned double distance = uS * 100 / 578;
  if (0 >= (distance - offset) )
  {
      Serial.print(distance);
  }
  else 
  {
    Serial.print(distance - offset); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  }
  Serial.println("mm");*/
  if (uS_front_internal > 0) // filter out 0s
  {
    uS_front = uS_front_internal / US_ROUNDTRIP_CM;
    Serial.print(uS_front); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm ");
  }
  //Serial.print(uS);
  ///Serial.println(" microseconds");
  } // end of if statement which only runs every 29 ms
  return uS_front;
}
