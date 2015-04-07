

int speed_L = 4, speed_R = 11, direction_L1 = 5, direction_L2 = 6, direction_R1 = 12, direction_R2 = 13;

void setup()
{
  pinMode(speed_L, OUTPUT);
  pinMode(speed_R, OUTPUT);
  pinMode(direction_L1, OUTPUT);
  pinMode(direction_L2, OUTPUT);
  pinMode(direction_R1, OUTPUT);
  pinMode(direction_R2, OUTPUT);
  digitalWrite(direction_L1, HIGH);
  digitalWrite(direction_L2, LOW);
  digitalWrite(direction_R1, HIGH);
  digitalWrite(direction_R2, LOW);
}

void loop()
{
      analogWrite(speed_L,190);
      analogWrite(speed_R, 0);
}
