// all have delays: get_ball(), hopper_enter(), hopper_exitR(), hopper_exitL(), back_out(), arm_up(), drop_arm(),

// slight delay in hopper_exit to change motor direction
// delays in arm_up, arm_down, lift_ball


void get_ball() // gotta subtract 1 from the hopper location in the grid
{
/* This code runs after the robot is in the hopper,
  and a ball is in the shovel. This code first drops the arm
  to the lowest elevation, then shimmies out, and finally backs out
*/
  drop_arm();
  delay(1000);
  hopper_exitR();

  lift_ball();
  delay(1000);
  back_out();
  delay(1000);
  hopper_exitL();
  delay(1000);
  back_out();
}



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

int hopper_exitR()
{
 Serial.println("hopper_exitR");
  backwards_direction();
  stop_motors();
  delay(50);
 analogWrite(pin_speed_L,0);   // stronger bristles need 200 speed at first, for 400, and 120 for later
 analogWrite(pin_speed_R,200); 
delay(400);
 analogWrite(pin_speed_L,0);   
 analogWrite(pin_speed_R,120); 
 delay(600);
  stop_motors();
  // don't know how long this takes, but can't write delay into here
   // if writing delay here, then will not be able to process anything else
 return 0;   
}

int hopper_exitL()
{
 Serial.println(" hopper_exitL ");
  backwards_direction();
  stop_motors();
  delay(50);
 analogWrite(pin_speed_L,140);   
 analogWrite(pin_speed_R,0); 
 delay(400);
  stop_motors();
  // don't know how long this takes, but can't write delay into here
   // if writing delay here, then will not be able to process anything else
 return 0;   
}


void back_out()
{
   Serial.println("hopper_exit");
   backwards_direction(); 
   
  analogWrite(pin_speed_L,160);   
 analogWrite(pin_speed_R,120); 
 delay(800);
  analogWrite(pin_speed_L,0);   
  analogWrite(pin_speed_R,0);
}

int lift_ball()
{
    digitalWrite(pin_direction_pulley1, HIGH);
    digitalWrite(pin_direction_pulley2, LOW); // maybe need to write something else?
    analogWrite(pin_speed_pulley,200);
    
    Serial.println(" lift barely ");
    delay(300);
    analogWrite(pin_speed_pulley,0);
    return 0;
 
 
 return 0; 
}

int arm_up()
{
    digitalWrite(pin_direction_pulley1, LOW); // may need to add another direction pin
    digitalWrite(pin_direction_pulley2, HIGH);
    arm_high = digitalRead(pin_pulley_top); 
    Serial.print("pin pulley up reading " );
    Serial.print(arm_high);
   while (arm_high == 0){
     
      arm_low = digitalRead(arm_low_pin);
      arm_high = digitalRead(arm_high_pin);
      digitalWrite(arm_D1, HIGH);
      digitalWrite(arm_D2, LOW);
      analogWrite(pin_speed_arm, 240);
      Serial.print(" going to the otp Arm High Pin:");
      Serial.print(arm_high);
      Serial.print("\n");
    }
    
    analogWrite(pin_speed_arm,0);
}

int drop_arm() /// may need to check this
{
    digitalWrite(pin_direction_pulley1, HIGH);
    digitalWrite(pin_direction_pulley2, LOW);
    arm_low = digitalRead(pin_pulley_bottom);
    
    while (arm_low == 0){
      arm_low = digitalRead(arm_low_pin);
      arm_high = digitalRead(arm_high_pin);
      
      
      digitalWrite(arm_D1, LOW);
      digitalWrite(arm_D2, HIGH);
      analogWrite(pin_speed_arm, 100);
      Serial.print(" dropping Arm Low Pin:");
      Serial.print(arm_low);
      Serial.print("\n");
    }
    
    analogWrite(pin_speed_arm, 0);
    return 0;
}
