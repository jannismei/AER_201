
int grid[10][11] = {0};
int col_S, row_S, col_T, row_T, num_rows_to_pass, num_cols_to_pass;


void setup()
{
  
  grid[0][0] = 4; // set the # of balls in the corner hoppers
  grid[8][0] = 4; // corner hoppers have 4 balls each
  grid[5][3] = 7;
  col_S = 1; // testing cols and rows
  col_T = 1;
  row_S = 5;
  row_T = 9;
  Serial.begin(4800);
  Serial.println("Entering Setup\n");
}

void loop()
{
   for (num_rows_to_pass; num_rows_to_pass >=0; num_rows_to_pass - 1)
   {
     Serial.println("this many rows left to go");
     Serial.println(num_rows_to_pass);
   }
}
