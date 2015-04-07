  // grid is bigger than it needs to be (8x9)
/* this means that if we accidentally rewrite beyond the bounds,
there will be no effect on the grid */ 

int print_grid()
{

  Serial.print("\n");
  Serial.print("grid vals \n");
//  Serial.print(grid);
//  Serial.print(grid[0][1]);
//  Serial.print(grid[0][0]);
//  Serial.print(grid[1][2]);
  Serial.print("\n");  
  for (int j = 9; j >=0; j--)
  {
    Serial.print(" j ");
    Serial.print(j);
    Serial.print(" ");
    for (int i = 0; i <= 8; i ++)
    {
      Serial.print(grid[i][j]);
      Serial.print("|");
    }
    Serial.print("\n");
  }
  
}
