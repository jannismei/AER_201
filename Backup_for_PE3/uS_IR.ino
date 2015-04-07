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
void uS_logic()
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
    Serial.print(uS_3);
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
    turn_to_face_hopper();
    Serial.print(" uS_state ");
    Serial.print(uS_state);
  }
  return;
}

int ultrasonic_front()
{
  if ( (time - uS_front_time) > 29 )
  {
   // Serial.println(time - uS_start_time);
  uS_front_time = millis();
  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  int uS_front_internal = sonar.ping(); // Send ping, get ping time in microseconds (uS).
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
