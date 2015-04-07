// serial 9600
// if using sensor, take out delay(1500) in down
// mode = 2 means up, switch = 1 means half, switch = 0 means full

int pin_speed_pulley = 22, pin_direction_pulley1 = 24, pin_direction_pulley2 = 26;
int pin_sensor = 30, sensor, mode, switch_up;

void setup() 
{
    pinMode(pin_speed_pulley, OUTPUT);
    pinMode(pin_direction_pulley1, OUTPUT);
    pinMode(pin_direction_pulley2, OUTPUT);
    digitalWrite(pin_direction_pulley1, HIGH);
    digitalWrite(pin_direction_pulley2, LOW);
    mode = 2; // mode = 2 means up, switch = 1 means half, switch = 0 means full
    switch_up = 1;
    Serial.begin(9600);
}

void loop()
{
  // for actual use
  move_up_half();
  
  delay(10000);
  move_up_half();
  delay(1000);
  move_down();
  
// for demo
 /* if ( 1 == mode )
  {
      Serial.println("down");
      move_down();
      mode = 2; // mode = 2 means up, switch = 1 means half, switch = 0 means full
      // mode = 1 means down
      
  }
  else if ( (2 == mode) && (1 == switch_up) )
  {
     Serial.println("half_up");
     move_up_half();
     mode = 1;
     switch_up = 0;
  }
  else if (2 == mode)
  {
    Serial.println("up");
    move_up();
    mode = 1;
    switch_up = 1;
  }
  Serial.println("end of loop"); */
}

int move_down()
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
      analogWrite(pin_speed_pulley,155); 
      delay(1500); // take out once sensor is implemented
    }
    
    return 0;
}

int move_up()
{
    digitalWrite(pin_direction_pulley1, HIGH);
    digitalWrite(pin_direction_pulley2, LOW);
    analogWrite(pin_speed_pulley,155);
    delay(1500);
    analogWrite(pin_speed_pulley,0);
    return 0;
}

int move_up_half()
{
    digitalWrite(pin_direction_pulley1, HIGH);
    digitalWrite(pin_direction_pulley2, LOW);
    analogWrite(pin_speed_pulley,155);
    delay(750);
    analogWrite(pin_speed_pulley,0);
    return 0;
  
}
