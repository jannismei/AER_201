// no delays: follow_line(), variable_speed_follow_line(), reverse_follow_line()


void follow_line()
{
  read_IR_sensors();
  angle = LDR1 - LDR2; // calculating for differential function
  L_R_POS = LDR3 - LDR5;
  speed_Increment = angle/20 + L_R_POS/30;
  forwards_direction();
/* Line-following here. Wheels will go straight at base speed on default. If slightly off black line, will
adjust power to motors relative to the difference between sensor inputs.
Changes based on sensor inputs only occur when difference between LDRs pass the threshold.
Power to motors is cappe at maximum and floored at minimum, as defined at top of file.
*/

/*  Serial.println("forward: speed_increment: ");
  Serial.println(speed_Increment);*/
  if  ( ~( ( LDR1 + threshold < LDR3) && (LDR2 + threshold < LDR5) ) || ~( (LDR3 + threshold  < LDR1 ) && (LDR5 + threshold  < LDR2) ) )
  {
   //   lcd.clear();
       if ( 0 == speed_Increment )
       {
          left = startSpeed_L;
          right = startSpeed_R; 
       }
 
       if ( left < max_speed && (speed_Increment > 0) )
       {
          left = startSpeed_L + speed_Increment/2; // change relative to base speed
          //lcd.print("LV < Max");// turn right
       }
       if ( right > min_speed && (speed_Increment > 0) )
       {
          right = startSpeed_R - speed_Increment/2;
          //lcd.print("RV > min"); // turn right
       }
  
  // if LDR1 is less than the centre sensor + threshold turn left

    //    lcd.clear();
        if (left > min_speed && (speed_Increment < 0) )
        {
          left = startSpeed_L + speed_Increment/2; // change relative to previous speed
      //    lcd.print("LV > min"); // turn left
        }
        if (right < max_speed && (speed_Increment < 0) )
        {
          right = startSpeed_R - speed_Increment/2;
      //    lcd.print("RV < max "); // turn right
        }
  }
  // send the speed values to the motors
    analogWrite(pin_speed_L,left);
    analogWrite(pin_speed_R,right);

    return;
}


void variable_speed_follow_line(unsigned int speed_L, unsigned int speed_R)
{
  read_IR_sensors();
  angle = LDR1 - LDR2; // calculating for differential function
  L_R_POS = LDR3 - LDR5;
  speed_Increment = angle/20 + L_R_POS/30;
  forwards_direction();
/* Line-following here. Wheels will go straight at base speed on default. If slightly off black line, will
adjust power to motors relative to the difference between sensor inputs.
Changes based on sensor inputs only occur when difference between LDRs pass the threshold.
Power to motors is cappe at maximum and floored at minimum, as defined at top of file.
*/

/*  Serial.println("forward: speed_increment: ");
  Serial.println(speed_Increment);*/
  if  ( ~( ( LDR1 + threshold < LDR3) && (LDR2 + threshold < LDR5) ) || ~( (LDR3 + threshold  < LDR1 ) && (LDR5 + threshold  < LDR2) ) )
  {
   //   lcd.clear();
       if ( 0 == speed_Increment )
       {
          left = speed_L;
          right = speed_R; 
       }
 
       if ( left < max_speed && (speed_Increment > 0) )
       {
          left = speed_L + speed_Increment/2; // change relative to base speed
          //lcd.print("LV < Max");// turn right
       }
       if ( right > min_speed && (speed_Increment > 0) )
       {
          right = speed_R - speed_Increment/2;
          //lcd.print("RV > min"); // turn right
       }
  
  // if LDR1 is less than the centre sensor + threshold turn left

    //    lcd.clear();
        if (left > min_speed && (speed_Increment < 0) )
        {
          left = speed_L + speed_Increment/2; // change relative to previous speed
      //    lcd.print("LV > min"); // turn left
        }
        if (right < max_speed && (speed_Increment < 0) )
        {
          right = speed_R - speed_Increment/2;
      //    lcd.print("RV < max "); // turn right
        }
  }
  // send the speed values to the motors
    analogWrite(pin_speed_L,left);
    analogWrite(pin_speed_R,right);

    return;
}



void reverse_follow_line()
{
  backwards_direction();

  /* Line-following here. Wheels will go straight at base speed on default. If slightly off black line, will
adjust power to motors relative to the difference between sensor inputs.
Changes based on sensor inputs only occur when difference between LDRs pass the threshold.
Power to motors is cappe at maximum and floored at minimum, as defined at top of file.
*/
  int L_R_POS = LDR1 - LDR2; // calculating for differential function
  int angle = LDR3 - LDR5 ;
  int speed_Increment = angle/20 + L_R_POS/30;
  Serial.print("reverse: speed_increment: ");
  Serial.println(speed_Increment);
  Serial.print("angle: ");
    Serial.println(angle);/*
  if  ( ~( ( LDR1 + threshold < LDR3) && (LDR2 + threshold < LDR5) ) || ~( (LDR3 + threshold  < LDR1 ) && (LDR5 + threshold  < LDR2) ) )
  {
   
   //   lcd.clear();
       if ( 0 == speed_Increment )
       {
          left = startSpeed_L;
          right = startSpeed_R; 
         // Serial.println("Reverse, speed_Increment = 0");
       }
 
       if ( left < max_speed && (speed_Increment > 0) )
       {
          left = startSpeed_L + speed_Increment/2; // change relative to base speed
          //lcd.print("LV < Max"); // t
          Serial.print("Reverse, left motor go faster than right");
       }
       if ( right > min_speed && (speed_Increment > 0) )
       {
          right = startSpeed_R - speed_Increment/2;
          Serial.print("Reverse, left motor go faster than right");
          //lcd.print("RV > min");
       }
  
  // if LDR1 is less than the centre sensor + threshold turn left

    //    lcd.clear();
        if (left > min_speed && (speed_Increment < 0) )
        {
          left = startSpeed_L + speed_Increment/2; // change relative to previous speed
      //    lcd.print("LV > min");
          Serial.print("Reverse, right  motor go faster than left");
        }
        if (right < max_speed && (speed_Increment < 0) )
        {
          right = startSpeed_R - speed_Increment/2;
      //    lcd.print("RV < max ");
          Serial.print("Reverse, right  motor go faster than left");
        }
  }*/
  // send the speed values to the motors
    analogWrite(pin_speed_L,left);
    analogWrite(pin_speed_R,right);

    return;
}
