unsigned long time, time2, time3, start_time;

void setup(){
  Serial.begin(115200);
  start_time = millis();
}
void loop(){
  
  time3 = time2;
  time2 = time;
  time = millis();
  if ( (time - start_time) > 998)
  {
  start_time = millis();
    Serial.print("Time: "); 
     //prints time since program started
  Serial.println(time);
  
  }
  
}
