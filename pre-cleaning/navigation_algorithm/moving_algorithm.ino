int moving_algorithm()
{
  
    /* when integrated with main code, will want to 
    use while loop. while(num_lines_to_go != 0 and while num_turns_to_go != 0)
    
    if (1 == sensing_passing_line() )
    {
       num_lines_to_go = num_lines_to_go - 1; 
    }
    */
   for (num_lines_to_pass; num_lines_to_pass >= 0; num_lines_to_pass = num_lines_to_pass - 1)
   {
     Serial.println("this many lines left to go");
     Serial.println(num_lines_to_pass);
     delay(1000);
   }
   return 0;
}
