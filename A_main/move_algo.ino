// got rid of delay, but still have long while loop that includes follow line and read ir sensors, but nothing else

int moving_algorithm()
{
  
    /* when integrated with main code, will want to 
    use while loop. while(num_lines_to_go != 0 and while num_turns_to_go != 0)
    
    if (1 == sensing_passing_line() )
    {
       num_lines_to_go = num_lines_to_go - 1; 
    }
    */
   while( (0 != num_lines_to_pass) )
   {
     read_IR_sensors();
     follow_line();
     if( 1 == sensing_passing_line() )
     {
     num_lines_to_pass = num_lines_to_pass - 1;
     Serial.println("this many lines left to go");
     Serial.println(num_lines_to_pass);
     }
   if (1 == num_lines_to_pass)
   {
    startSpeed_L = 110;
    startSpeed_R = 85;
   }
   else if ( num_lines_to_pass > 1)
   {
    startSpeed_L = 160;
    startSpeed_R = 120;
   }

//     delay(10); // is this really needed?
   }
   return 0;
}
