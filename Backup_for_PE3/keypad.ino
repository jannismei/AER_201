// input_key()


/*  
  should call this in setup, may need constants and stuff to be defined earlier.
  // A Function will break from loop, B function will return function.
 */
 
// keypad pin 1 to arduino pin 9, keypad pin 2 to arduino pin 8, ... keypad pin 8 to arduino pin 2

#include <Keypad.h>
//const byte ROWS = 4; // Four rows
//const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
//byte rowPins[ROWS] = { 47, 49, 51, 53 }; 
// Connect keypad COL0, COL1, COL2, and COL3 to these Arduino pins.
//byte colPins[COLS] = { 39,41, 43, 45 }; 
// keypad pin 1 to arduino pin 9, keypad pin 2 to arduino pin 8, ... keypad pin 8 to arduino pin 2

int input_hopper_1, input_hopper_2, key_flag = 1;


// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void input_key() /* need a while loop here (maybe do {} while (0 != flag) )
*/
{
Serial.println("\nInput hopper commands and coordinates now");

do
{
  char key = kpd.getKey();
  

  if(key)  // Check for a valid key.
  {
      while (1 <= input_hopper_1) 
      // input coordinates of hopper 1
      {
        key = kpd.getKey();
        if(key && (2 == input_hopper_1) )
        {
        input_hopper_1 = 1; // gets row
        //Serial.print("input_hopper_1: ");
        //Serial.println(input_hopper_1);
        row_A = key - '0'; // for some reason, only the second press gets stored here
        
        
        Serial.println(row_A);
        break; // exits function
        }
        else if(key && (1 == input_hopper_1) )
        {
        input_hopper_1 = 0;
        //Serial.print("input_hopper_1: ");
        //Serial.println(input_hopper_1);
        col_A = key - '0'; // for some reason, only the second press gets stored here
        Serial.print("\ncol_A is ");
        
        Serial.println(col_A);
        
        grid[col_A][row_A] = 7;
        print_grid();
        break; // exits function
        }
       } // closes while loop
      
      while (1 <= input_hopper_2)
      {// input coordinates of hopper 2
        key = kpd.getKey();
        if(key && (2 == input_hopper_2) )
        {
        input_hopper_2 = 1; // gets row
        Serial.print("input_hopper_2: ");
        //Serial.println(input_hopper_2);
        row_B = key - '0'; // for some reason, only the second press gets stored here
        Serial.print("\nrow_B is ");
        
        Serial.println(row_B);
        break; // exits function
        }
        else if(key && (1 == input_hopper_2) )
        {
        input_hopper_2 = 0;
        //Serial.print("input_hopper_2: ");
        //Serial.println(input_hopper_2);
        col_B = key - '0'; // for some reason, only the second press gets stored here
        Serial.print("\ncol_B is ");
        
        Serial.println(col_B);
        grid[col_B][row_B] = 7;
        print_grid();
        //key_flag = 0;
        return; // exits function
        }
       } // closes while loop
       
      if ('A' == key)
      {
        Serial.println(key);
        input_hopper_1 = 2;
       Serial.print("Input_hopper_1 row coordinate, then column coordinate");
       // Serial.println(input_hopper_1);
      }
      else if ('B' == key)
      {
        Serial.println(key);
        input_hopper_2 = 2;
        Serial.print("Input_hopper_2 row coordinate, then column coordinate");
        //Serial.println(input_hopper_2);
      }
      else
        {
          Serial.println(key);
        }
  } //closes if(key)
  
} while (0 != key_flag);
}


