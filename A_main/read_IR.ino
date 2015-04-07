/* This code reads the IR sensors

*/
void read_IR_sensors()
{
  LDR1 = analogRead(0); // read the 5 photosensors
  LDR2 = analogRead(1);
  LDR3 = analogRead(2);
  LDR4 = analogRead(3);
  LDR5 = analogRead(4);
  
  // Everything below here is printing onto serial monitor or LCD
  
  // print sensor readings onto lcd
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(LDR1);
  lcd.print("|");
  lcd.print(LDR2);

  // print speed_Increment debugging
    //lcd.print("s_I: ");
    //lcd.print(speed_Increment);

  lcd.setCursor(0,1);  
  lcd.print(LDR3);
  lcd.print("|");
  lcd.print(LDR4);
  lcd.print("|");
  lcd.print(LDR5);
  lcd.setCursor(0,1);
  /*
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
*/
  return;
}
