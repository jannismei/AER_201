// slight delay in hopper_exit to change motor direction
// delays in arm_up, arm_down, lift_ball

int hopper_enter () {
  // make both motors same speed
  Serial.println("hopper_enter");
  forwards_direction();
 delay(50);
 analogWrite(pin_speed_L,195);   
 analogWrite(pin_speed_R,145); // don't know how long this takes, but can't write delay into here
 // if writing delay here, then will not be able to process anything else
 return 0;
}

int hopper_exit()
{
 Serial.println("hopper_exit");
  backwards_direction();
  analogWrite(pin_speed_L,0);   
  analogWrite(pin_speed_R,0);
  delay(50);
 analogWrite(pin_speed_L,245);   
 analogWrite(pin_speed_R,195); 
  // don't know how long this takes, but can't write delay into here
   // if writing delay here, then will not be able to process anything else
 return 0;   
}

int lift_ball()
{
    digitalWrite(pin_direction_pulley1, HIGH);
    digitalWrite(pin_direction_pulley2, LOW); // maybe need to write something else?
    digitalWrite(pin_speed_pulley,HIGH);
    delay(750);
    analogWrite(pin_speed_pulley,0);
    return 0;
 
 
 return 0; 
}

int arm_up()
{
    digitalWrite(pin_direction_pulley1, HIGH); // may need to add another direction pin
    digitalWrite(pin_direction_pulley2, LOW);
    digitalWrite(pin_speed_pulley,HIGH);
    delay(1500);
    analogWrite(pin_speed_pulley,0);
    return 0;
}

int drop_arm() /// may need to check this
{
    digitalWrite(pin_direction_pulley1, LOW);
    digitalWrite(pin_direction_pulley2, HIGH);
    sensor = digitalRead(pin_sensor);
      if (1 == sensor )
    {
      analogWrite(pin_speed_pulley, 0);
      delay(5000);
      mode = 2;
      if (1 == switch_up)
      {
        mode = 3; 
      }
    }
    else if (0 == sensor)
    {
      analogWrite(pin_speed_pulley,100); 
      delay(1500); // take out once sensor is implemented
    }
    
    return 0;
}
