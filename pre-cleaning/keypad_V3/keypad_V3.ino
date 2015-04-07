#include <Keypad.h>
int grid[10][11] = {0}; // [10] cols, [11] rows
int col_A, row_A, col_B, row_B;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 5, 4, 3, 2 }; 
// Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.
byte colPins[COLS] = { 9, 8, 7, 6 }; 
// keypad pin 1 to arduino pin 9, keypad pin 2 to arduino pin 8, ... keypad pin 8 to arduino pin 2

char orientation_A, orientation_B;


void setup()
{
  Serial.begin(115200);
  input_key();
}



void loop()
{
  Serial.println("now delay 1000");
  delay(1000);
  Serial.println("now delay 200000");
  delay(200000);
  
  
}
