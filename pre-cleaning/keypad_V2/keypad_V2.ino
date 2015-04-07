/*  Keypadtest
 *
 *  Demonstrate the simplest use of the  keypad library.
 *
 *  The first step is to connect your keypad to the
 *  Arduino  using the pin numbers listed below in
 *  rowPins[] and colPins[]. If you want to use different
 *  pins then  you  can  change  the  numbers below to
 *  match your setup.
 *
 */
#include <Keypad.h>
int grid[10][11] = {'\0'}; // [10] cols, [11] rows
int col_A, row_A, col_B, row_B;

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 5, 4, 3, 2 }; 
// Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.
byte colPins[COLS] = { 9, 8, 7, 6 }; 
// keypad pin 1 to arduino pin 9, keypad pin 2 to arduino pin 8, ... keypad pin 8 to arduino pin 2

int input_hopper_1, input_hopper_2, key_flag;
char orientation_A, orientation_B;

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13

void setup()
{
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin, HIGH);
  Serial.begin(115200);
  grid[0][0] = 4;
  grid[8][0] = 4;
}

void loop()
{
  char key = kpd.getKey();
  

  if(key)  // Check for a valid key.
  {
      while (1 <= input_hopper_1) 
      // input coordinates of hopper 1
      {
        key = kpd.getKey();
        if(key && (3 == input_hopper_1) )
        {
          input_hopper_1 = 2; // gets row
          //Serial.print("input_hopper_1: ");
          //Serial.println(input_hopper_1);
          row_A = key - '0'; // for some reason, only the second press gets stored here
          Serial.println(row_A);
          break; // exits function
        }
        else if(key && (2 == input_hopper_1) )
        {
          input_hopper_1 = 1;
          //Serial.print("input_hopper_1: ");
          //Serial.println(input_hopper_1);
          col_A = key - '0'; // for some reason, only the second press gets stored here
          Serial.print("\ncol_A is ");
          Serial.println(col_A);
          grid[col_A][row_A] = 7;
          print_grid();
          break; // exits function
        }
        else if(key && (1 == input_hopper_1) )
        {
          input_hopper_1 = 0;
          orientation_A = key;
          Serial.print("\nOrientation_A is ");
          Serial.println(orientation_A);
          break;
        }
       } // closes while loop
      
      while (1 <= input_hopper_2)
      {// input coordinates of hopper 2
        key = kpd.getKey();
        if(key && (3 == input_hopper_2) )
        {
          input_hopper_2 = 2; // gets row
          Serial.print("input_hopper_2: ");
          //Serial.println(input_hopper_2);
          row_B = key - '0'; // for some reason, only the second press gets stored here
          Serial.print("\nrow_B is ");
          Serial.println(row_B);
          break; // exits function
        }
        else if(key && (2 == input_hopper_2) )
        {
          input_hopper_2 = 1;
          //Serial.print("input_hopper_2: ");
          //Serial.println(input_hopper_2);
          col_B = key - '0'; // for some reason, only the second press gets stored here
          Serial.print("\ncol_B is ");
          Serial.println(col_B);
          grid[col_B][row_B] = 7;
          print_grid();
          break; // exits function
        }
        else if(key && (1 == input_hopper_2) )
        {
          input_hopper_2 = 1;
          orientation_B = key;
          Serial.print("\nOrientation_B is ");
          Serial.println(orientation_B);
          key_flag = 0;
          return; // exits function
        }
       } // closes while loop
       
      if ('A' == key)
      {
        Serial.println(key);
        input_hopper_1 = 3;
        Serial.print("input_hopper_1: ");
        Serial.println(input_hopper_1);
      }
      else if ('B' == key)
      {
        Serial.println(key);
        input_hopper_2 = 3;
        Serial.print("input_hopper_2: ");
        Serial.println(input_hopper_2);
      }
      else
        {
          Serial.println(key);
        }
  } //closes if(key)
}


